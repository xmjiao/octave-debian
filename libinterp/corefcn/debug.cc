/*

Copyright (C) 2001-2017 Ben Sapp
Copyright (C) 2007-2009 John Swensen

This file is part of Octave.

Octave is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

Octave is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with Octave; see the file COPYING.  If not, see
<http://www.gnu.org/licenses/>.

*/
#if defined (HAVE_CONFIG_H)
#  include "config.h"
#endif

#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <string>

#include "file-stat.h"
#include "singleton-cleanup.h"

#include "call-stack.h"
#include "defun.h"
#include "error.h"
#include "file-ops.h"
#include "help.h"
#include "input.h"
#include "pager.h"
#include "octave-link.h"
#include "ovl.h"
#include "utils.h"
#include "parse.h"
#include "symtab.h"
#include "errwarn.h"
#include "octave-preserve-stream-state.h"
#include "ov.h"
#include "ov-usr-fcn.h"
#include "ov-fcn.h"
#include "ov-struct.h"
#include "pt-pr-code.h"
#include "pt-bp.h"
#include "pt-eval.h"
#include "pt-exp.h"
#include "pt-stmt.h"
#include "sighandlers.h"
#include "interpreter.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"

#include "debug.h"

// Initialize the singleton object
bp_table *bp_table::instance = 0;

std::set<std::string> bp_table::errors_that_stop;
std::set<std::string> bp_table::caught_that_stop;
std::set<std::string> bp_table::warnings_that_stop;

// Read entire file called fname and return the contents as a string
static std::string
snarf_file (const std::string& fname)
{
  std::string retval;

  octave::sys::file_stat fs (fname);

  if (fs)
    {
      size_t sz = fs.size ();

      std::ifstream file (fname.c_str (), std::ios::in | std::ios::binary);

      if (file)
        {
          std::string buf (sz+1, 0);

          file.read (&buf[0], sz+1);

          if (! file.eof ())
            error ("error reading file %s", fname.c_str ());

          // Expected to read the entire file.
          retval = buf;
        }
    }

  return retval;
}

static std::deque<size_t>
get_line_offsets (const std::string& buf)
{
  // FIXME: This could maybe be smarter.  Is deque the right thing to use here?

  std::deque<size_t> offsets;

  offsets.push_back (0);

  size_t len = buf.length ();

  for (size_t i = 0; i < len; i++)
    {
      char c = buf[i];

      if (c == '\r' && ++i < len)
        {
          c = buf[i];

          if (c == '\n')
            offsets.push_back (i+1);
          else
            offsets.push_back (i);
        }
      else if (c == '\n')
        offsets.push_back (i+1);
    }

  offsets.push_back (len);

  return offsets;
}

std::string
get_file_line (const std::string& fname, size_t line)
{
  std::string retval;

  static std::string last_fname;

  static std::string buf;

  static std::deque<size_t> offsets;

  if (fname != last_fname)
    {
      buf = snarf_file (fname);

      offsets = get_line_offsets (buf);
    }

  if (line > 0)
    line--;

  if (line < offsets.size () - 1)
    {
      size_t bol = offsets[line];
      size_t eol = offsets[line+1];

      while (eol > 0 && eol > bol && (buf[eol-1] == '\n' || buf[eol-1] == '\r'))
        eol--;

      retval = buf.substr (bol, eol - bol);
    }

  return retval;
}

// Return a pointer to the user-defined function FNAME.  If FNAME is
// empty, search backward for the first user-defined function in the
// current call stack.

static octave_user_code *
get_user_code (const std::string& fname = "")
{
  octave_user_code *dbg_fcn = 0;

  if (fname.empty ())
    dbg_fcn = octave_call_stack::debug_user_code ();
  else
    {
      std::string name = fname;

      if (octave::sys::file_ops::dir_sep_char () != '/' && name[0] == '@')
        {
          int len = name.length () - 1;         // -1: can't have trailing '/'
          for (int i = 2; i < len; i++)         //  2: can't have @/method
            if (name[i] == '/')
              name[i] = octave::sys::file_ops::dir_sep_char ();
        }

      size_t name_len = name.length ();

      if (! name.empty () && name_len > 2 && name.substr (name_len-2) == ".m")
        name = name.substr (0, name_len-2);

      octave_value fcn = symbol_table::find_function (name);

      if (fcn.is_defined () && fcn.is_user_code ())
        dbg_fcn = fcn.user_code_value ();
    }

  return dbg_fcn;
}

#if defined (DBSTOP_NANINF)
#  include "sigfpe.cc"
#endif

enum
dbstop_args {dbstop_in, dbstop_at, dbstop_if, dbstop_none};

// Parse parameters (args) of dbstop and dbclear commands.
// For dbstop, who=="dbstop"; for dbclear, who=="dbclear".
// The syntax is: dbstop [[in] symbol] [[at] line [line [...]]] [if condition]
// where the form of condition depends on whether or not a file or line has
// been seen.
// Also execute "if [error|warning|interrupt|naninf]" clauses.
void
parse_dbfunction_params (const char *who, const octave_value_list& args,
                         std::string& symbol_name, bp_table::intmap& lines,
                         std::string& cond)
{
  int nargin = args.length ();
  int list_idx = 0;
  symbol_name = "";
  lines = bp_table::intmap ();

  if (nargin == 0 || ! args(0).is_string ())
    print_usage (who);

  // elements already processed
  bool seen_in = false, seen_at = false, seen_if = false;
  int pos = 0;
  dbstop_args token = dbstop_none;
  while (pos < nargin)
    {
      // allow "in" and "at" to be implicit
      if (args(pos).is_string ())
        {
          std::string arg = args(pos).string_value ();
          if (arg == "in")
            {
              token = dbstop_in;
              pos++;
            }
          else if (arg == "at")
            {
              token = dbstop_at;
              pos++;
            }
          else if (arg == "if")
            {
              token = dbstop_if;
              pos++;
            }
          else if (atoi (args(pos).string_value ().c_str ()) > 0)
            token = dbstop_at;
          else
            token = dbstop_in;
        }
      else
        token = dbstop_at;

      if (pos >= nargin)
        error ("%s: '%s' missing argument", who,
               ( token == dbstop_in ? "in" :
                (token == dbstop_at ? "at" : "if")));

      // process the actual arguments
      switch (token)
        {
        case dbstop_in:
          symbol_name = args(pos).string_value ();
          if (seen_in)
            error ("%s: Too many function names specified -- %s",
                   who, symbol_name.c_str ());
          else if (seen_at || seen_if)
            error ("%s: function name must come before line number and 'if'",
                   who);
          seen_in = true;
          pos++;
          break;

        case dbstop_at:
          if (seen_at)
            error ("%s: Only one 'at' clause is allowed -- %s",
                   who, args(pos).string_value ().c_str ());
          else if (seen_if)
            error ("%s: line number must come before 'if' clause\n");
          seen_at = true;

          if (! seen_in)
            {
              // It was a line number.  Get function name from debugger.
              if (Vdebugging)
                symbol_name = get_user_code ()->profiler_name ();
              else
                error ("%s: function name must come before line number "
                       "and 'if'", who);
              seen_in = true;
            }
          else if (seen_if)
            error ("%s: line number must come before 'if' clause\n");

          // Read a list of line numbers (or arrays thereof)
          for ( ; pos < nargin; pos++)
            {
              if (args(pos).is_string ())
                {
                  int line = atoi (args(pos).string_value ().c_str ());

                  if (line > 0)
                    lines[list_idx++] = line;
                  else
                    break;        // may be "if"
                }
              else if (args(pos).is_numeric_type ())
                {
                  const NDArray arg = args(pos).array_value ();

                  for (octave_idx_type j = 0; j < arg.numel (); j++)
                    lines[list_idx++] = static_cast<int> (arg.elem (j));
                }
              else
                error ("%s: Invalid argument type %s",
                       args(pos).type_name ().c_str ());
            }
          break;

        case dbstop_if:
          if (seen_in)    // conditional breakpoint
            {
              cond = "";  // remaining arguments form condition
              for (; pos < nargin; pos++)
                {
                  if (args(pos).is_string ())
                    cond = cond + " " + args(pos).string_value ();
                  else
                    error ("%s: arguments to 'if' must all be strings", who);
                }

              cond = cond.substr (1);   // omit initial space
            }
          else    // stop on event (error, warning, interrupt, NaN/inf)
            {
              std::string condition = args(pos).string_value ();
              int on_off = ! strcmp(who, "dbstop");

              // list of error/warning IDs to update
              std::set<std::string> *id_list = NULL;
              bool *stop_flag = NULL;         // Vdebug_on_... flag

              if (condition == "error")
                {
                  id_list = &bp_table::errors_that_stop;
                  stop_flag = &Vdebug_on_error;
                }
              else if (condition == "warning")
                {
                  id_list = &bp_table::warnings_that_stop;
                  stop_flag = &Vdebug_on_warning;
                }
              else if (condition == "caught" && nargin > pos+1
                       && args(pos+1).string_value () == "error")
                {
                  id_list = &bp_table::caught_that_stop;
                  stop_flag = &Vdebug_on_caught;
                  pos++;
                }
              else if (condition == "interrupt")
                {
                  octave::Vdebug_on_interrupt = on_off;
                }
              else if (condition == "naninf")
#if defined (DBSTOP_NANINF)
                {
                  Vdebug_on_naninf = on_off;
                  enable_fpe (on_off);
                }
#else
                warning ("%s: condition '%s' not yet supported",
                         who, condition.c_str ());
#endif
              else
                error ("%s: invalid condition %s",
                       who, condition.c_str ());

              // process ID list for "dbstop if error <error_ID>" etc
              if (id_list != NULL)
                {
                  pos++;
                  if (pos < nargin)       // only affect a single error ID
                    {
                      if (! args(pos).is_string () || nargin > pos+1)
                        error ("%s: ID must be a single string", who);
                      else if (on_off == 1)
                        {
                          id_list->insert (args(pos).string_value ());
                          *stop_flag = 1;
                        }
                      else
                        {
                          id_list->erase (args(pos).string_value ());
                          if (id_list->empty ())
                            *stop_flag = 0;
                        }
                    }
                  else   // unqualified.  Turn all on or off
                    {
                      id_list->clear ();
                      *stop_flag = on_off;
                      if (stop_flag == &Vdebug_on_error)
                        {
                          // Matlab stops on both.
                          octave::Vdebug_on_interrupt = on_off;
                        }
                    }
                }

              pos = nargin;
            }
          break;

        default:      // dbstop_none should never occur
          break;
        }
    }
}

/*
%!test
%! dbclear all;   # Clear out breakpoints before test
%! dbstop help;
%! dbstop in ls;
%! dbstop help at 100;
%! dbstop in ls 100;
%! dbstop help 201 if a==5;
%! dbstop if error Octave:undefined-function;
%! s = dbstatus;
%! dbclear all;
%! assert ({s.bkpt(:).name}, {"help", "help", "help>do_contents", "ls", "ls"});
%! assert ([s.bkpt(:).line], [48, 100, 201, 58, 100]);
%! assert (s.errs, {"Octave:undefined-function"});
*/

// Return true if there is a valid breakpoint table, false otherwise.
// If no table exists, one is created; false is only returned if this fails.
bool
bp_table::instance_ok (void)
{
  if (! instance)
    {
      instance = new bp_table ();

      if (instance)
        singleton_cleanup_list::add (cleanup_instance);
    }

  if (! instance)
    error ("unable to create breakpoint table!");

  return true;
}

// Clear all reasons to stop, other than breakpoints
void
bp_table::dbclear_all_signals (void)
{
  Vdebug_on_error = false;
  bp_table::errors_that_stop.clear ();

  Vdebug_on_caught = false;
  bp_table::caught_that_stop.clear ();

  Vdebug_on_warning = false;
  bp_table::warnings_that_stop.clear ();

  octave::Vdebug_on_interrupt = false;
}

// Process the "warn", "errs", "caught" and "intr" fields for a call of
// "dbstop (p)".
void
bp_table::dbstop_process_map_args (const octave_map& mv)
{
  // process errs
  // why so many levels of indirection needed?
  bool fail = false;
  Cell U = mv.contents ("errs");
  if (U.numel () != 1)
    fail = (U.numel () > 1);
  else
    {
      Array<octave_value> W = U.index (static_cast<octave_idx_type> (0));
      if (W.is_empty () || W(0).is_empty () == 0)
        Vdebug_on_error = 1;    // like "dbstop if error" with no identifier
      else if (! W(0).is_cell ())
        fail = true;
      else
        {
          Cell V = W(0).cell_value ();
          for (int i = 0; i < V.numel (); i++)
            {
              errors_that_stop.insert (V(i).string_value ());
              Vdebug_on_error = 1;
            }
        }
    }
  if (fail)
    error ("dbstop: invalid 'errs' field");

  // process caught
  // why so many levels of indirection needed?
  fail = false;
  U = mv.contents ("caught");
  if (U.numel () != 1)
    fail = (U.numel () > 1);
  else
    {
      Array<octave_value> W = U.index (static_cast<octave_idx_type> (0));
      if (W.is_empty () || W(0).is_empty ())
        Vdebug_on_caught = 1;    // like "dbstop if caught error" with no ID
      else if (! W(0).is_cell ())
        fail = true;
      else
        {
          Cell V = W(0).cell_value ();
          for (int i = 0; i < V.numel (); i++)
            {
              caught_that_stop.insert (V(i).string_value ());
              Vdebug_on_caught = 1;
            }
        }
    }
  if (fail)
    error ("dbstop: invalid 'caught' field");

  // process warn
  // why so many levels of indirection needed?
  fail = false;
  U = mv.contents ("warn");
  if (U.numel () != 1)
    fail = (U.numel () > 1);
  else
    {
      Array<octave_value> W = U.index (static_cast<octave_idx_type> (0));
      if (W.is_empty () || W(0).is_empty ())
        Vdebug_on_warning = 1;    // like "dbstop if warning" with no identifier
      else if (! W(0).is_cell ())
        fail = true;
      else
        {
          Cell V = W(0).cell_value ();
          for (int i = 0; i < V.numel (); i++)
            {
              warnings_that_stop.insert (V(i).string_value ());
              Vdebug_on_warning = 1;
            }
        }
    }
  if (fail)
    error ("dbstop: invalid 'warn' field");

  // process interrupt
  if (mv.isfield ("intr"))
    octave::Vdebug_on_interrupt = 1;
}

// Insert a breakpoint in function fcn at line within file fname,
// to stop only when condition is true.
// Record in bp_set that fname contains a breakpoint.
bool
bp_table::do_add_breakpoint_1 (octave_user_code *fcn,
                               const std::string& fname,
                               const bp_table::intmap& line,
                               const std::string& condition,
                               bp_table::intmap& retval)
{
  bool found = false;

  tree_statement_list *cmds = fcn->body ();

  std::string file = fcn->fcn_file_name ();

  if (cmds)
    {
      retval = cmds->add_breakpoint (file, line, condition);

      for (auto& idx_line_p : retval)
        {
          if (idx_line_p.second != 0)
            {
              // Normalize to store only the file name.
              // Otherwise, there can be an entry for both file>subfunction and
              // file, which causes a crash on dbclear all
              const char *s = strchr (fname.c_str (), Vfilemarker);
              if (s)
                bp_set.insert (fname.substr (0, s - fname.c_str ()));
              else
                bp_set.insert (fname);
              found = true;
              break;
            }
        }
    }

  return found;
}

// Cursory check that cond is a valid condition to use for a breakpoint.
// Currently allows conditions with side-effects, like 'y+=10' and 'y++';
// it is odd that the former is not flagged by "is_assignment_expression".
// Throws an exception if not valid.
bool
bp_table::condition_valid (const std::string& cond)
{
  if (cond.length () > 0)
    {
      octave::parser parser (cond + " ;"); // ; to reject partial expr like "y=="
      parser.reset ();
      int parse_status = parser.run ();
      if (parse_status)
        error ("dbstop: Cannot parse condition '%s'", cond.c_str ());
      else
        {
          tree_statement *stmt = 0;
          if (! parser.stmt_list)
            error ("dbstop: "
                   "condition is not empty, but has nothing to evaluate");
          else
            {
              if (parser.stmt_list->length () == 1
                  && (stmt = parser.stmt_list->front ())
                  && stmt->is_expression ())
                {
                  tree_expression *expr = stmt->expression ();
                  if (expr->is_assignment_expression ())
                    error ("dbstop: condition cannot be an assignment.  "
                           "Did you mean '=='?");
                }
              else
                error ("dbstop: condition must be an expression");
            }
        }
    }
  return true;
}

// Return the sub/nested/main function of MAIN_FCN that contains
// line number LINENO of the source file.
// If END_LINE != 0, *END_LINE is set to last line of the returned function.
static octave_user_code*
find_fcn_by_line (octave_user_code *main_fcn, int lineno, int *end_line = 0)
{
  octave_user_code *retval = 0;
  octave_user_code *next_fcn = 0;  // 1st function starting after lineno

  // Find innermost nested (or parent) function containing lineno.
  int earliest_end = std::numeric_limits<int>::max ();

  std::map<std::string, octave_value> subfcns = main_fcn->subfunctions ();
  for (const auto& str_val_p : subfcns)
    {
      if (str_val_p.second.is_user_function ())
        {
          auto *dbg_subfcn = str_val_p.second.user_function_value ();

          // Check if lineno is within dbg_subfcn.
          // FIXME: we could break when beginning_line() > lineno,
          // but that makes the code "fragile"
          // if the order of walking subfcns changes,
          // for a minor speed improvement in non-critical code.
          if (dbg_subfcn->ending_line () < earliest_end
              && dbg_subfcn->ending_line () >= lineno
              && dbg_subfcn->beginning_line () <= lineno)
            {
              earliest_end = dbg_subfcn->ending_line ();
              retval = find_fcn_by_line (dbg_subfcn, lineno, &earliest_end);
            }

          // Find the first fcn starting after lineno.
          // This is used if line is not inside any function.
          if (dbg_subfcn->beginning_line () >= lineno && ! next_fcn)
            next_fcn = dbg_subfcn;
        }
    }

  // The breakpoint is either in the subfunction found above,
  // or in the main function, which we check now.
  if (main_fcn->is_user_function ())
    {
      int e = dynamic_cast<octave_user_function*> (main_fcn)->ending_line ();
      if (e >= lineno && e < earliest_end)
        retval = main_fcn;

      if (! retval)
        retval = next_fcn;
    }
  else  // main_fcn is a script.
    {
      if (! retval)
        retval = main_fcn;
    }

  if (end_line != 0 && earliest_end < *end_line)
    *end_line = earliest_end;

  return retval;
}

// Given file name fname, find the subfunction at line and create
// a breakpoint there.  Put the system into debug_mode.
bp_table::intmap
bp_table::do_add_breakpoint (const std::string& fname,
                             const bp_table::intmap& line,
                             const std::string& condition)
{
  octave_user_code *main_fcn = get_user_code (fname);

  if (! main_fcn)
    error ("add_breakpoint: unable to find function '%s'\n", fname.c_str ());

  condition_valid (condition);  // Throw error if condition not valid.

  intmap retval;

  octave_idx_type len = line.size ();

  for (int i = 0; i < len; i++)
    {
      const_intmap_iterator m = line.find (i);

      if (m != line.end ())
        {
          int lineno = m->second;

          octave_user_code *dbg_fcn = find_fcn_by_line (main_fcn, lineno);

          // We've found the right (sub)function.  Now insert the breakpoint.
          // We insert all breakpoints.
          // If multiple are in the same function, we insert multiple times.
          intmap ret_one;
          if (dbg_fcn
              && do_add_breakpoint_1 (dbg_fcn, fname, line, condition, ret_one))
            retval.insert (std::pair<int,int> (i, ret_one.find (i)->second));
        }
    }

  octave::tree_evaluator::debug_mode = bp_table::have_breakpoints ()
                                       || Vdebugging;

  return retval;
}

int
bp_table::do_remove_breakpoint_1 (octave_user_code *fcn,
                                  const std::string& fname,
                                  const bp_table::intmap& line)
{
  int retval = 0;

  std::string file = fcn->fcn_file_name ();

  tree_statement_list *cmds = fcn->body ();

  // FIXME: move the operation on cmds to the tree_statement_list class?

  if (cmds)
    {
      octave_value_list results = cmds->list_breakpoints ();

      if (results.length () > 0)
        {
          octave_idx_type len = line.size ();

          for (int i = 0; i < len; i++)
            {
              const_intmap_iterator p = line.find (i);

              if (p != line.end ())
                {
                  int lineno = p->second;

                  cmds->delete_breakpoint (lineno);

                  if (! file.empty ())
                    octave_link::update_breakpoint (false, file, lineno);
                }
            }

          results = cmds->list_breakpoints ();

          bp_set_iterator it = bp_set.find (fname);
          if (results.empty () && it != bp_set.end ())
            bp_set.erase (it);
        }

      retval = results.length ();
    }

  return retval;
}

int
bp_table::do_remove_breakpoint (const std::string& fname,
                                const bp_table::intmap& line)
{
  int retval = 0;

  octave_idx_type len = line.size ();

  if (len == 0)
    {
      intmap results = remove_all_breakpoints_in_file (fname);
      retval = results.size ();
    }
  else
    {
      octave_user_code *dbg_fcn = get_user_code (fname);

      if (! dbg_fcn)
        error ("remove_breakpoint: unable to find function %s\n",
               fname.c_str ());

      retval = do_remove_breakpoint_1 (dbg_fcn, fname, line);

      // Search subfunctions in the order they appear in the file.

      const std::list<std::string> subfcn_names
        = dbg_fcn->subfunction_names ();

      std::map<std::string, octave_value> subfcns
        = dbg_fcn->subfunctions ();

      for (const auto& subf_nm : subfcn_names)
        {
          const auto q = subfcns.find (subf_nm);

          if (q != subfcns.end ())
            {
              octave_user_code *dbg_subfcn = q->second.user_code_value ();

              retval += do_remove_breakpoint_1 (dbg_subfcn, fname, line);
            }
        }
    }

  octave::tree_evaluator::debug_mode = bp_table::have_breakpoints ()
                                       || Vdebugging;

  return retval;
}

// Remove all breakpoints from a file, including those in subfunctions
bp_table::intmap
bp_table::do_remove_all_breakpoints_in_file (const std::string& fname,
                                             bool silent)
{
  intmap retval;

  octave_user_code *dbg_fcn = get_user_code (fname);

  if (dbg_fcn)
    {
      std::string file = dbg_fcn->fcn_file_name ();

      tree_statement_list *cmds = dbg_fcn->body ();

      if (cmds)
        {
          retval = cmds->remove_all_breakpoints (file);

          bp_set_iterator it = bp_set.find (fname);
          if (it != bp_set.end ())
            bp_set.erase (it);
        }
    }
  else if (! silent)
    error ("remove_all_breakpoint_in_file: "
           "unable to find function %s\n", fname.c_str ());

  octave::tree_evaluator::debug_mode = bp_table::have_breakpoints ()
                                       || Vdebugging;

  return retval;
}

void
bp_table::do_remove_all_breakpoints (void)
{
  // Odd loop structure required because delete will invalidate bp_set iterators
  for (const_bp_set_iterator it=bp_set.begin (), it_next=it;
       it != bp_set.end ();
       it=it_next)
    {
      ++it_next;
      remove_all_breakpoints_in_file (*it);
    }

  octave::tree_evaluator::debug_mode = bp_table::have_breakpoints ()
                                       || Vdebugging;
}

std::string
do_find_bkpt_list (octave_value_list slist, std::string match)
{
  std::string retval;

  for (int i = 0; i < slist.length (); i++)
    {
      if (slist(i).string_value () == match)
        {
          retval = slist(i).string_value ();
          break;
        }
    }

  return retval;
}

bp_table::fname_bp_map
bp_table::do_get_breakpoint_list (const octave_value_list& fname_list)
{
  fname_bp_map retval;

  // make copy since changes may invalidate iters of bp_set.
  std::set<std::string> tmp_bp_set = bp_set;

  for (auto& bp_fname : tmp_bp_set)
    {
      if (fname_list.empty ()
          || do_find_bkpt_list (fname_list, bp_fname) != "")
        {
          octave_user_code *f = get_user_code (bp_fname);

          if (f)
            {
              tree_statement_list *cmds = f->body ();

              // FIXME: move the operation on cmds to the
              //        tree_statement_list class?
              if (cmds)
                {
                  std::list<bp_type> bkpts = cmds->breakpoints_and_conds ();

                  if (! bkpts.empty ())
                    retval[bp_fname] = bkpts;
                }

              // look for breakpoints in subfunctions
              const std::list<std::string> subf_nm = f->subfunction_names ();

              std::map<std::string, octave_value> subf = f->subfunctions ();

              for (const auto& subfcn_nm : subf_nm)
                {
                  const auto q = subf.find (subfcn_nm);

                  if (q != subf.end ())
                    {
                      octave_user_code *ff = q->second.user_code_value ();

                      cmds = ff->body ();
                      if (cmds)
                        {
                          std::list<bp_type> bkpts
                            = cmds->breakpoints_and_conds ();

                          if (! bkpts.empty ())
                            retval[bp_fname + Vfilemarker + ff->name ()] = bkpts;
                        }
                    }
                }
            }
        }
    }

  return retval;
}

static octave_value
intmap_to_ov (const bp_table::intmap& line)
{
  int idx = 0;

  NDArray retval (dim_vector (1, line.size ()));

  for (size_t i = 0; i < line.size (); i++)
    {
      bp_table::const_intmap_iterator p = line.find (i);

      if (p != line.end ())
        {
          int lineno = p->second;
          retval(idx++) = lineno;
        }
    }

  retval.resize (dim_vector (1, idx));

  return retval;
}

DEFUN (dbstop, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbstop @var{func}
@deftypefnx {} {} dbstop @var{func} @var{line}
@deftypefnx {} {} dbstop @var{func} @var{line1} @var{line2} @dots{}
@deftypefnx {} {} dbstop @var{line1} @dots{}
@deftypefnx {} {} dbstop in @var{func}
@deftypefnx {} {} dbstop in @var{func} at @var{line}
@deftypefnx {} {} dbstop in @var{func} at @var{line} if "@var{condition}"
@deftypefnx {} {} dbstop if @var{event}
@deftypefnx {} {} dbstop if @var{event} @var{ID}
@deftypefnx {} {} dbstop (@var{bp_struct})
@deftypefnx {} {@var{rline} =} dbstop @dots{}

Set breakpoints for the built-in debugger.

@var{func} is the name of a function on the current @code{path}.  When
already in debug mode the @var{func} argument can be omitted and the current
function will be used.  Breakpoints at subfunctions are set with the scope
operator @samp{>}.  For example, If @file{file.m} has a subfunction
@code{func2}, then a breakpoint in @code{func2} can be specified by
@code{file>func2}.

@var{line} is the line number at which to break.  If @var{line} is not
specified, it defaults to the first executable line in the file
@file{func.m}.  Multiple lines can be specified in a single command; when
function syntax is used, the lines may also be passed as a single vector
argument (@code{[@var{line1}, @var{line2}, @dots{}]}).

@var{condition} is any Octave expression that can be evaluated in the code
context that exists at the breakpoint.  When the breakpoint is encountered,
@var{condition} will be evaluated, and execution will stop if
@var{condition} is true.  If @var{condition} cannot be evaluated, for
example because it refers to an undefined variable, an error will be thrown.
 Expressions with side effects (such as @code{y++ > 1}) will alter
variables, and should generally be avoided.  Conditions containing quotes
(@samp{"}, @samp{'}) or comment characters (@samp{#}, @samp{%}) must be
enclosed in quotes.  (This does not apply to conditions entered from the
editor's context menu.)  For example:

@example
dbstop in strread at 209 if 'any (format == "%f")'
@end example

The form specifying @var{event} does not cause a specific breakpoint at a
given function and line number.  Instead it causes debug mode to be entered
when certain unexpected events are encountered.  Possible values are

@table @code
@item error
Stop when an error is reported.  This is equivalent to specifying
both @code{debug_on_error (true)} and @code{debug_on_interrupt (true)}.

@item caught error
Stop when an error is caught by a try-catch block (not yet implemented).

@item interrupt
Stop when an interrupt (@kbd{Ctrl-C}) occurs.

@item naninf
Stop when code returns a non-finite value (not yet implemented).

@item warning
Stop when a warning is reported.  This is equivalent to specifying
@code{debug_on_warning (true)}.
@end table

The events @code{error}, @code{caught error}, and @code{warning} can all be
followed by a string specifying an error ID or warning ID@.  If that is
done, only errors with the specified ID will cause execution to stop.  To
stop on one of a set of IDs, multiple @code{dbstop} commands must be
issued.

Breakpoints and events can be removed using the @code{dbclear} command with
the same syntax.

It is possible to save all breakpoints and restore them at once by issuing
the commands @code{bp_state = dbstatus; @dots{}; dbstop (bp_state)}.

The optional output @var{rline} is the real line number where the breakpoint
was set.  This can differ from the specified line if the line is not
executable.  For example, if a breakpoint attempted on a blank line then
Octave will set the real breakpoint at the next executable line.

When a file is re-parsed, such as when it is modified outside the GUI,
all breakpoints within the file are cleared.

@seealso{dbclear, dbstatus, dbstep, debug_on_error, debug_on_warning, debug_on_interrupt}
@end deftypefn */)
{
  bp_table::intmap retmap;
  std::string symbol_name = "";  // stays empty for "dbstop if error" etc
  bp_table::intmap lines;
  std::string condition = "";
  octave_value retval;

  if (args.length() >= 1 && ! args(0).is_map ())
    {
      // explicit function / line / condition
      parse_dbfunction_params ("dbstop", args, symbol_name, lines, condition);

      if (lines.size () == 0)
        lines[0] = 1;

      if (symbol_name != "")
        {
          retmap = bp_table::add_breakpoint (symbol_name, lines, condition);
          retval = intmap_to_ov (retmap);
        }
    }
  else if (args.length () != 1)
    {
      print_usage ();
    }
  else  // structure of the form output by dbstatus
    {
      octave_map mv = args(0).map_value ();
      if (mv.isfield ("bkpt") || mv.isfield ("errs") || mv.isfield ("warn")
          || mv.isfield ("intr"))
        {
          bp_table::dbstop_process_map_args (mv);

          // Replace mv by "bkpt", to use the processing below.
          octave_value bkpt = mv.getfield ("bkpt");
          if (bkpt.is_empty ())
            mv = octave_map ();
          else
            {
              if (bkpt.is_cell () && bkpt.cell_value ().numel () > 0
                  && bkpt.cell_value () (0).is_map ())
                mv = bkpt.cell_value () (0).map_value ();
              else
                {
                  error ("dbstop: invalid 'bkpt' field");
                  mv = octave_map ();
                }
            }
        }
      if (mv.is_empty ())
        {
          // no changes requested.  Occurs if "errs" non-empty but "bkpt" empty
        }
      else if (! mv.isfield ("name") || ! mv.isfield ("line"))
        {
          error ("dbstop: Cell array must contain fields 'name' and 'line'");
          retval = octave_value (0);
        }
      else
        {
          bool use_cond = mv.isfield ("cond");
          Cell name = mv.getfield ("name");
          Cell line = mv.getfield ("line");
          Cell cond = (use_cond ? mv.getfield ("cond") : Cell ());
          std::string unconditional = "";
          for (octave_idx_type i = 0; i < line.numel (); i++)
            {
              lines [0] = line(i).double_value ();
              bp_table::add_breakpoint (name(i).string_value (), lines,
                                        use_cond ? cond(i).string_value ()
                                                 : unconditional );
            }
          retval = octave_value (line.numel ());
        }
    }

  return retval;
}

DEFUN (dbclear, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbclear @var{func}
@deftypefnx {} {} dbclear @var{func} @var{line}
@deftypefnx {} {} dbclear @var{func} @var{line1} @var{line2} @dots{}
@deftypefnx {} {} dbclear @var{line} @dots{}
@deftypefnx {} {} dbclear all
@deftypefnx {} {} dbclear in @var{func}
@deftypefnx {} {} dbclear in @var{func} at @var{line}
@deftypefnx {} {} dbclear if @var{event}
@deftypefnx {} {} dbclear ("@var{func}")
@deftypefnx {} {} dbclear ("@var{func}", @var{line})
@deftypefnx {} {} dbclear ("@var{func}", @var{line1}, @var{line2}, @dots{})
@deftypefnx {} {} dbclear ("@var{func}", @var{line1}, @dots{})
@deftypefnx {} {} dbclear (@var{line}, @dots{})
@deftypefnx {} {} dbclear ("all")
Delete a breakpoint at line number @var{line} in the function @var{func}.

Arguments are

@table @var
@item func
Function name as a string variable.  When already in debug mode this
argument can be omitted and the current function will be used.

@item line
Line number from which to remove a breakpoint.  Multiple lines may be given
as separate arguments or as a vector.

@item event
An event such as @code{error}, @code{interrupt}, or @code{warning}
(@pxref{XREFdbstop,,dbstop} for details).
@end table

When called without a line number specification all breakpoints in the named
function are cleared.

If the requested line is not a breakpoint no action is performed.

The special keyword @qcode{"all"} will clear all breakpoints from all
files.
@seealso{dbstop, dbstatus, dbwhere}
@end deftypefn */)
{
  std::string symbol_name = "";  // stays empty for "dbclear if error" etc
  bp_table::intmap lines;
  std::string dummy;             // "if" condition -- only used for dbstop

  int nargin = args.length ();

  parse_dbfunction_params ("dbclear", args, symbol_name, lines, dummy);

  if (nargin == 1 && symbol_name == "all")
    {
      bp_table::remove_all_breakpoints ();
      bp_table::dbclear_all_signals ();
    }
  else
    {
      if (symbol_name != "")
        bp_table::remove_breakpoint (symbol_name, lines);
    }

  return ovl ();
}

// Report the status of "dbstop if error ..." and "dbstop if warning ..."
// If to_screen is true, the output goes to octave_stdout; otherwise it is
// returned.
// If dbstop if error is true but no explicit IDs are specified, the return
// value will have an empty field called "errs".  If IDs are specified, the
// "errs" field will have a row per ID.  If dbstop if error is false, there
// is no "errs" field.  The "warn" field is set similarly by dbstop if warning
octave_map
bp_table::stop_on_err_warn_status (bool to_screen)
{
  octave_map retval;

  // print dbstop if error information
  if (Vdebug_on_error)
    {
      if (errors_that_stop.empty ())
        {
          if (to_screen)
            octave_stdout << "stop if error\n";
          else
            retval.assign ("errs", octave_value(""));
        }
      else
        {
          Cell errs (dim_vector (bp_table::errors_that_stop.size (), 1));
          int i = 0;

          for (const auto& e : errors_that_stop)
            {
              if (to_screen)
                octave_stdout << "stop if error " << e << "\n";
              else
                errs(i++) = e;
            }
          if (! to_screen)
            retval.assign ("errs", octave_value (errs));
        }
    }

  // print dbstop if caught error information
  if (Vdebug_on_caught)
    {
      if (caught_that_stop.empty ())
        {
          if (to_screen)
            octave_stdout << "stop if caught error\n";
          else
            retval.assign ("caught", octave_value(""));
        }
      else
        {
          Cell errs (dim_vector (caught_that_stop.size (), 1));
          int i = 0;

          for (const auto& e : caught_that_stop)
            {
              if (to_screen)
                octave_stdout << "stop if caught error " << e << "\n";
              else
                errs(i++) = e;
            }
          if (! to_screen)
            retval.assign ("caught", octave_value (errs));
        }
    }

  // print dbstop if warning information
  if (Vdebug_on_warning)
    {
      if (warnings_that_stop.empty ())
        {
          if (to_screen)
            octave_stdout << "stop if warning\n";
          else
            retval.assign ("warn", octave_value(""));
        }
      else
        {
          Cell warn (dim_vector (warnings_that_stop.size (), 1));
          int i = 0;

          for (const auto& w : warnings_that_stop)
            {
              if (to_screen)
                octave_stdout << "stop if warning " << w << "\n";
              else
                warn(i++) = w;
            }
          if (! to_screen)
            retval.assign ("warn", octave_value (warn));
        }
    }

  // print dbstop if interrupt information
  if (octave::Vdebug_on_interrupt)
    {
      if (to_screen)
        octave_stdout << "stop if interrupt\n";
      else
        retval.assign ("intr", octave_value ());
    }

  return retval;
}

DEFUN (dbstatus, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbstatus
@deftypefnx {} {} dbstatus @var{func}
@deftypefnx {} {@var{bp_list} =} dbstatus @dots{}
Report the location of active breakpoints.

When called with no input or output arguments, print the list of all
functions with breakpoints and the line numbers where those breakpoints are
set.

If a function name @var{func} is specified then only report breakpoints
for the named function and its subfunctions.

The optional return argument @var{bp_list} is a struct array with the
following fields.

@table @asis
@item name
The name of the function with a breakpoint.  A subfunction, say @code{func2}
within an m-file, say @file{file.m}, is specified as @code{file>func2}.

@item file
The name of the m-file where the function code is located.

@item line
The line number with the breakpoint.

@item cond
The condition that must be satisfied for the breakpoint to be active, or
the empty string for unconditional breakpoints.
@end table

@c Note: When @code{dbstatus} is called from the debug prompt within a function,
@c the list of breakpoints is automatically trimmed to the breakpoints in the
@c current function.
If @code{dbstop if error} is true but no explicit IDs are specified, the
return value will have an empty field called @qcode{"errs"}.  If IDs are
specified, the @code{errs} field will have one row per ID@.  If
@code{dbstop if error} is false, there is no @qcode{"errs"} field.
The @qcode{"warn"} field is set similarly by @code{dbstop if warning}.

@seealso{dbstop, dbclear, dbwhere, dblist, dbstack}
@end deftypefn */)
{
  int nargin = args.length ();

  if (nargin != 0 && nargin != 1)
    error ("dbstatus: only zero or one arguments accepted\n");

  octave_value_list fcn_list;
  bp_table::fname_bp_map bp_list;
  std::string symbol_name;

  if (nargin == 1)
    {
      if (! args(0).is_string ())
        err_wrong_type_arg ("dbstatus", args(0));

      symbol_name = args(0).string_value ();
      fcn_list(0) = symbol_name;
      bp_list = bp_table::get_breakpoint_list (fcn_list);
    }
  else
    {
/*
      if (Vdebugging)
        {
          octave_user_code *dbg_fcn = get_user_code ();
          if (dbg_fcn)
            {
              symbol_name = dbg_fcn->name ();
              fcn_list(0) = symbol_name;
            }
        }
*/

      bp_list = bp_table::get_breakpoint_list (fcn_list);
    }

  if (nargout == 0)
    {
      // Print out the breakpoint information.

      for (auto& fnm_bp_p: bp_list)
        {
          std::list<bp_type> m = fnm_bp_p.second;

          // print unconditional breakpoints, if any, on a single line

          // first, check to see if there are any
          int have_unconditional = 0;
          for (const auto& bp : m)
            {
              if (bp.cond == "")
                {
                  if (have_unconditional++)
                    break;                   // stop once we know its plural
                }
            }
          // If we actually have some, print line numbers only
          if (have_unconditional)
            {
              const char *_s_ = (have_unconditional > 1) ? "s" : "";
              octave_stdout << "breakpoint" << _s_ <<" in " << fnm_bp_p.first
                            << " at line" << _s_ << " ";

              for (const auto& bp : m)
                {
                  if (bp.cond == "")
                    octave_stdout << bp.line << " ";
                }
              octave_stdout << std::endl;
            }

          // print conditional breakpoints, one per line, with conditions
          for (const auto& bp : m)
            {
              if (bp.cond != "")
                octave_stdout << "breakpoint in " << fnm_bp_p.first
                              << " at line " << bp.line
                              << " if " << bp.cond << "\n";
            }
        }

      bp_table::stop_on_err_warn_status (true);

      return ovl ();
    }
  else
    {
      // Fill in an array for return.
      int i = 0;
      octave_map retmap;
      octave_value retval;

      // count the number of breakpoints in all files
      int count = 0;
      for (const auto& fnm_bp_p : bp_list)
        count += fnm_bp_p.second.size ();

      Cell names (dim_vector (count, 1));
      Cell file  (dim_vector (count, 1));
      Cell line  (dim_vector (count, 1));
      Cell cond  (dim_vector (count, 1));

      for (const auto& fnm_bp_p : bp_list)
        {
          std::string filename = fnm_bp_p.first;
          const char *sub_fun = strchr (filename.c_str (), Vfilemarker);
          if (sub_fun)
            filename = filename.substr(0, sub_fun - filename.c_str ());
          octave_value path_name;
          path_name = octave::sys::canonicalize_file_name (do_which (filename));

          for (const auto& bp : fnm_bp_p.second)
            {
              names(i) = fnm_bp_p.first;
              file(i) = path_name;
              line(i) = octave_value (bp.line);
              cond(i) = octave_value (bp.cond);
              i++;
            }
        }

      retmap.assign ("name", names);
      retmap.assign ("file", file);
      retmap.assign ("line", line);
      retmap.assign ("cond", cond);

      octave_map ew = bp_table::stop_on_err_warn_status (false);
      if (ew.is_empty ())
        {
          retval = octave_value (retmap);
        }
      else
        {
          octave_map outer (dim_vector (3,1));
          outer.assign ("bkpt", Cell (retmap));
          for (octave_map::const_iterator f = ew.begin (); f != ew.end (); f++)
            outer.setfield (f->first, ew.contents (f));

          retval = octave_value (outer);
        }

      return retval;
    }
}

/*
%!test
%! dbclear all;   # Clear out breakpoints before test
%! dbstop @ftp/dir;
%! dbstop @audioplayer/set 70;
%! dbstop quantile>__quantile__;
%! dbstop ls;
%! s = dbstatus;
%! dbclear all;
%! assert (s(1).name, "@audioplayer/set>setproperty");
%! assert (s(2).name, "@ftp/dir");
%! assert (s(3).name, "ls");
%! assert (s(4).name, "quantile>__quantile__");
%! assert (s(2).file(end-10:end), [filesep "@ftp" filesep "dir.m"]);
*/

DEFUN (dbwhere, , ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} dbwhere
In debugging mode, report the current file and line number where execution
is stopped.
@seealso{dbstack, dblist, dbstatus, dbcont, dbstep, dbup, dbdown}
@end deftypefn */)
{
  octave_user_code *dbg_fcn = get_user_code ();

  if (! dbg_fcn)
    {
      octave_stdout << "stopped at top level" << std::endl;
      return ovl ();
    }

  octave_stdout << "stopped in " << dbg_fcn->name () << " at ";

  int l = octave_call_stack::debug_user_code_line ();

  if (l > 0)
    {
      octave_stdout << "line " << l;

      std::string file_name = dbg_fcn->fcn_file_name ();

      if (! file_name.empty ())
        {
          octave_stdout << " [" << file_name << "]" << std::endl;

          std::string line = get_file_line (file_name, l);

          if (! line.empty ())
            octave_stdout << l << ": " << line << std::endl;
        }
      else
        octave_stdout << std::endl;
    }
  else
    octave_stdout << "<unknown line>" << std::endl;

  return ovl ();
}

void
do_dbtype (std::ostream& os, const std::string& name, int start, int end)
{
  std::string ff = fcn_file_in_path (name);

  if (ff.empty ())
    os << "dbtype: unknown function " << name << "\n";
  else
    {
      std::ifstream fs (ff.c_str (), std::ios::in);

      if (! fs)
        os << "dbtype: unable to open '" << ff << "' for reading!\n";
      else
        {
          int line = 1;
          std::string text;

          while (std::getline (fs, text) && line <= end)
            {
              if (line >= start)
                os << line << "\t" << text << "\n";

              line++;
            }
        }
    }

  os.flush ();
}

DEFUN (dbtype, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbtype
@deftypefnx {} {} dbtype @var{lineno}
@deftypefnx {} {} dbtype @var{startl:endl}
@deftypefnx {} {} dbtype @var{startl:end}
@deftypefnx {} {} dbtype @var{func}
@deftypefnx {} {} dbtype @var{func} @var{lineno}
@deftypefnx {} {} dbtype @var{func} @var{startl:endl}
@deftypefnx {} {} dbtype @var{func} @var{startl:end}
Display a script file with line numbers.

When called with no arguments in debugging mode, display the script file
currently being debugged.

An optional range specification can be used to list only a portion of the
file.  The special keyword @qcode{"end"} is a valid line number
specification for the last line of the file.

When called with the name of a function, list that script file with line
numbers.
@seealso{dblist, dbwhere, dbstatus, dbstop}
@end deftypefn */)
{
  octave_user_code *dbg_fcn;

  string_vector argv = args.make_argv ("dbtype");

  switch (args.length ())
    {
    case 0:  // dbtype
      dbg_fcn = get_user_code ();

      if (! dbg_fcn)
        error ("dbtype: must be inside a user function to give no arguments to dbtype\n");

      do_dbtype (octave_stdout, dbg_fcn->fcn_file_name (),
                 0, std::numeric_limits<int>::max ());

      break;

    case 1:  // (dbtype start:end) || (dbtype func) || (dbtype lineno)
      {
        std::string arg = argv[1];

        size_t ind = arg.find (':');

        if (ind != std::string::npos)  // (dbtype start:end)
          {
            dbg_fcn = get_user_code ();

            if (dbg_fcn)
              {
                std::string start_str = arg.substr (0, ind);
                std::string end_str = arg.substr (ind + 1);

                int start, end;
                start = atoi (start_str.c_str ());
                if (end_str == "end")
                  end = std::numeric_limits<int>::max ();
                else
                  end = atoi (end_str.c_str ());

                if (std::min (start, end) <= 0)
                  error ("dbtype: start and end lines must be >= 1\n");

                if (start > end)
                  error ("dbtype: start line must be less than end line\n");

                do_dbtype (octave_stdout, dbg_fcn->fcn_file_name (),
                           start, end);
              }
          }
        else  // (dbtype func) || (dbtype lineno)
          {
            int line = atoi (arg.c_str ());

            if (line == 0)  // (dbtype func)
              {
                dbg_fcn = get_user_code (arg);

                if (! dbg_fcn)
                  error ("dbtype: function <%s> not found\n", arg.c_str ());

                do_dbtype (octave_stdout, dbg_fcn->fcn_file_name (),
                           0, std::numeric_limits<int>::max ());
              }
            else  // (dbtype lineno)
              {
                if (line <= 0)
                  error ("dbtype: start and end lines must be >= 1\n");

                dbg_fcn = get_user_code ();

                if (dbg_fcn)
                  do_dbtype (octave_stdout, dbg_fcn->fcn_file_name (),
                             line, line);
              }
          }
      }
      break;

    case 2:  // (dbtype func start:end) || (dbtype func start)
      {
        dbg_fcn = get_user_code (argv[1]);

        if (! dbg_fcn)
          error ("dbtype: function <%s> not found\n", argv[1].c_str ());

        std::string arg = argv[2];
        int start, end;
        size_t ind = arg.find (':');

        if (ind != std::string::npos)
          {
            std::string start_str = arg.substr (0, ind);
            std::string end_str = arg.substr (ind + 1);

            start = atoi (start_str.c_str ());
            if (end_str == "end")
              end = std::numeric_limits<int>::max ();
            else
              end = atoi (end_str.c_str ());
          }
        else
          {
            start = atoi (arg.c_str ());
            end = start;
          }

        if (std::min (start, end) <= 0)
          error ("dbtype: start and end lines must be >= 1\n");

        if (start > end)
          error ("dbtype: start line must be less than end line\n");

        do_dbtype (octave_stdout, dbg_fcn->fcn_file_name (), start, end);
      }
      break;

    default:
      error ("dbtype: expecting zero, one, or two arguments\n");
    }

  return ovl ();
}

DEFUN (dblist, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dblist
@deftypefnx {} {} dblist @var{n}
In debugging mode, list @var{n} lines of the function being debugged
centered around the current line to be executed.

If unspecified @var{n} defaults to 10 (+/- 5 lines)
@seealso{dbwhere, dbtype, dbstack}
@end deftypefn */)
{
  int n = 10;

  if (args.length () == 1)
    {
      octave_value arg = args(0);

      if (arg.is_string ())
        {
          std::string s_arg = arg.string_value ();

          n = atoi (s_arg.c_str ());
        }
      else
        n = args(0).int_value ();

      if (n < 0)
        error ("dblist: N must be a non-negative integer");
    }

  octave_user_code *dbg_fcn = get_user_code ();

  if (! dbg_fcn)
    error ("dblist: must be inside a user function to use dblist\n");

  bool have_file = true;

  std::string name = dbg_fcn->fcn_file_name ();

  if (name.empty ())
    {
      have_file = false;
      name = dbg_fcn->name ();
    }

  int l = octave_call_stack::debug_user_code_line ();

  if (l > 0)
    {
      if (have_file)
        {
          int l_min = std::max (l - n/2, 0);
          int l_max = l + n/2;
          do_dbtype (octave_stdout, name, l_min, l-1);

          std::string line = get_file_line (name, l);
          if (! line.empty ())
            octave_stdout << l << "-->\t" << line << std::endl;

          do_dbtype (octave_stdout, name, l+1, l_max);
        }
    }
  else
    {
      octave_stdout << "dblist: unable to determine source code line"
                    << std::endl;
    }

  return ovl ();
}

static octave_value_list
do_dbstack (const octave_value_list& args, int nargout, std::ostream& os)
{
  int nargin = args.length ();

  if (nargin > 2)
    print_usage ();

  octave_value_list retval;

  octave::unwind_protect frame;

  octave_idx_type curr_frame = -1;

  size_t nskip = 0;

  if (nargin == 1 || nargin == 2)
    {
      int n = 0;

      for (octave_idx_type i = 0; i < nargin; i++)
        {
          octave_value arg = args(i);

          if (arg.is_string ())
            {
              std::string s_arg = arg.string_value ();

              // Skip "-completenames", octave returns full names anyway.
              if (s_arg == "-completenames")
                continue;

              n = atoi (s_arg.c_str ());
            }
          else
            n = arg.int_value ();

          if (n <= 0)
            error ("dbstack: N must be a non-negative integer");
        }

      if (n > 0)
        nskip = n;
    }

  if (nargout == 0)
    {
      octave_map stk = octave_call_stack::backtrace (nskip, curr_frame);
      octave_idx_type nframes_to_display = stk.numel ();

      if (nframes_to_display > 0)
        {
          octave_preserve_stream_state stream_state (os);

          os << "stopped in:\n\n";

          Cell names = stk.contents ("name");
          Cell files = stk.contents ("file");
          Cell lines = stk.contents ("line");

          bool show_top_level = true;

          size_t max_name_len = 0;

          for (octave_idx_type i = 0; i < nframes_to_display; i++)
            {
              std::string name = names(i).string_value ();

              max_name_len = std::max (name.length (), max_name_len);
            }

          for (octave_idx_type i = 0; i < nframes_to_display; i++)
            {
              std::string name = names(i).string_value ();
              std::string file = files(i).string_value ();
              int line = lines(i).int_value ();

              if (show_top_level && i == curr_frame)
                show_top_level = false;

              os << (i == curr_frame ? "  --> " : "      ")
                 << std::setw (max_name_len) << name
                 << " at line " << line
                 << " [" << file << "]"
                 << std::endl;
            }

          if (show_top_level)
            os << "  --> top level" << std::endl;
        }
    }
  else
    {
      octave_map stk = octave_call_stack::backtrace (nskip, curr_frame, false);

      retval = ovl (stk, curr_frame < 0 ? 1 : curr_frame + 1);
    }

  return retval;
}

// A function that can be easily called from a debugger print the Octave stack.
// This can be useful for finding what line of code the interpreter is
// currently executing when the debugger is stopped in some C++ function,
// for example.

void
show_octave_dbstack (void)
{
  do_dbstack (octave_value_list (), 0, std::cerr);
}

DEFUN (dbstack, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbstack
@deftypefnx {} {} dbstack @var{n}
@deftypefnx {} {} dbstack @var{-completenames}
@deftypefnx {} {[@var{stack}, @var{idx}] =} dbstack (@dots{})
Display or return current debugging function stack information.

With optional argument @var{n}, omit the @var{n} innermost stack frames.

Although accepted, the argument @var{-completenames} is silently ignored.
Octave always returns absolute filenames.

The arguments @var{n} and @var{-completenames} can be both specified in any
order.

The optional return argument @var{stack} is a struct array with the
following fields:

@table @asis
@item file
The name of the m-file where the function code is located.

@item name
The name of the function with a breakpoint.

@item line
The line number of an active breakpoint.

@item column
The column number of the line where the breakpoint begins.

@item scope
Undocumented.

@item context
Undocumented.
@end table

The return argument @var{idx} specifies which element of the @var{stack}
struct array is currently active.
@seealso{dbup, dbdown, dbwhere, dblist, dbstatus}
@end deftypefn */)
{
  return do_dbstack (args, nargout, octave_stdout);
}

static void
do_dbupdown (const octave_value_list& args, const std::string& who)
{
  int n = 1;

  if (args.length () == 1)
    {
      octave_value arg = args(0);

      if (arg.is_string ())
        {
          std::string s_arg = arg.string_value ();

          n = atoi (s_arg.c_str ());
        }
      else
        n = args(0).int_value ();
    }

  if (who == "dbup")
    n = -n;

  if (! octave_call_stack::goto_frame_relative (n, true))
    error ("%s: invalid stack frame", who.c_str ());
}

DEFUN (dbup, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbup
@deftypefnx {} {} dbup @var{n}
In debugging mode, move up the execution stack @var{n} frames.

If @var{n} is omitted, move up one frame.
@seealso{dbstack, dbdown}
@end deftypefn */)
{
  do_dbupdown (args, "dbup");

  return ovl ();
}

DEFUN (dbdown, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbdown
@deftypefnx {} {} dbdown @var{n}
In debugging mode, move down the execution stack @var{n} frames.

If @var{n} is omitted, move down one frame.
@seealso{dbstack, dbup}
@end deftypefn */)
{
  do_dbupdown (args, "dbdown");

  return ovl ();
}

DEFUN (dbstep, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} dbstep
@deftypefnx {} {} dbstep @var{n}
@deftypefnx {} {} dbstep in
@deftypefnx {} {} dbstep out
@deftypefnx {} {} dbnext @dots{}
In debugging mode, execute the next @var{n} lines of code.

If @var{n} is omitted, execute the next single line of code.  If the next
line of code is itself defined in terms of an m-file remain in the existing
function.

Using @code{dbstep in} will cause execution of the next line to step into
any m-files defined on the next line.

Using @code{dbstep out} will cause execution to continue until the current
function returns.

@code{dbnext} is an alias for @code{dbstep}.
@seealso{dbcont, dbquit}
@end deftypefn */)
{
  if (! Vdebugging)
    error ("dbstep: can only be called in debug mode");

  int nargin = args.length ();

  if (nargin > 1)
    print_usage ();

  if (nargin == 1)
    {
      std::string arg = args(0).xstring_value ("dbstep: input argument must be a string");

      if (arg == "in")
        {
          Vdebugging = false;
          Vtrack_line_num = true;

          octave::tree_evaluator::dbstep_flag = -1;
        }
      else if (arg == "out")
        {
          Vdebugging = false;
          Vtrack_line_num = true;

          octave::tree_evaluator::dbstep_flag = -2;
        }
      else
        {
          int n = atoi (arg.c_str ());

          if (n < 1)
            error ("dbstep: invalid argument");

          Vdebugging = false;
          Vtrack_line_num = true;

          octave::tree_evaluator::dbstep_flag = n;
        }
    }
  else
    {
      Vdebugging = false;
      Vtrack_line_num = true;

      octave::tree_evaluator::dbstep_flag = 1;
    }

  return ovl ();
}

DEFALIAS (dbnext, dbstep);

DEFUN (dbcont, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} dbcont
Leave command-line debugging mode and continue code execution normally.
@seealso{dbstep, dbquit}
@end deftypefn */)
{
  if (! Vdebugging)
    error ("dbcont: can only be called in debug mode");

  if (args.length () != 0)
    print_usage ();

  Vdebugging = false;
  Vtrack_line_num = true;

  octave::tree_evaluator::reset_debug_state ();

  return ovl ();
}

DEFUN (dbquit, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} dbquit
Quit debugging mode immediately without further code execution and return to
the Octave prompt.
@seealso{dbcont, dbstep}
@end deftypefn */)
{
  if (! Vdebugging)
    error ("dbquit: can only be called in debug mode");

  if (args.length () != 0)
    print_usage ();

  Vdebugging = false;

  octave::tree_evaluator::reset_debug_state ();

  octave_throw_interrupt_exception ();

  return ovl ();
}

DEFUN (isdebugmode, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} isdebugmode ()
Return true if in debugging mode, otherwise false.
@seealso{dbwhere, dbstack, dbstatus}
@end deftypefn */)
{
  if (args.length () != 0)
    print_usage ();

  return ovl (Vdebugging);
}

DEFUN (__db_next_breakpoint_quiet__, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {} __db_next_breakpoint_quiet__ ()
@deftypefnx {} {} __db_next_breakpoint_quiet__ (@var{flag})
Disable line info printing at the next breakpoint.

With a logical argument @var{flag}, set the state on or off.
@end deftypefn */)
{
  int nargin = args.length ();

  if (nargin > 1)
    print_usage ();

  bool state = true;

  if (nargin == 1)
    state = args(0).bool_value ();

  octave::tree_evaluator::quiet_breakpoint_flag = state;

  return ovl ();
}
