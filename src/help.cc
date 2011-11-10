/*

Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001,
              2002, 2003, 2004, 2005, 2006, 2007, 2008, 2009 John W. Eaton

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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifdef HAVE_UNISTD_H
#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#include <unistd.h>
#endif

#include "cmd-edit.h"
#include "file-ops.h"
#include "file-stat.h"
#include "oct-env.h"
#include "str-vec.h"

#include <defaults.h>
#include "defun.h"
#include "dirfns.h"
#include "error.h"
#include "gripes.h"
#include "help.h"
#include "input.h"
#include "load-path.h"
#include "oct-obj.h"
#include "ov-usr-fcn.h"
#include "pager.h"
#include "parse.h"
#include "pathsearch.h"
#include "procstream.h"
#include "pt-pr-code.h"
#include "sighandlers.h"
#include "symtab.h"
#include "syswait.h"
#include "toplev.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"
#include "version.h"
#include "quit.h"

// Name of the doc cache file specified on the command line.
// (--doc-cache-file file)
std::string Vdoc_cache_file;

// Name of the info file specified on command line.
// (--info-file file)
std::string Vinfo_file;

// Name of the info reader we'd like to use.
// (--info-program program)
std::string Vinfo_program;

// Name of the makeinfo program to run.
static std::string Vmakeinfo_program = "makeinfo";

// If TRUE, don't print additional help message in help and usage
// functions.
static bool Vsuppress_verbose_help_message = false;

#include <map>

typedef std::map<std::string, std::string> map_type;
typedef map_type::value_type pair_type;
typedef map_type::const_iterator map_iter;

template<typename T, std::size_t z>
std::size_t
size (T const (&)[z])
{
  return z;
}

// FIXME -- The descriptions could easily be in texinfo -- should they?
const static pair_type operators[] =
{
  pair_type ("!",
    "Logical not operator.  See also `~'.\n"),

  pair_type ("!=",
    "Logical not equals operator.  See also `~='.\n"),

  pair_type ("\"",
    "String delimiter.\n"),

  pair_type ("#",
    "Begin comment character.  See also `%'."),

  pair_type ("%",
    "Begin comment charcter.  See also `#'."),

  pair_type ("&",
    "Element by element logical and operator.  See also `&&'."),

  pair_type ("&&",
    "Logical and operator (with short-circuit evaluation).  See also `&'."),

  pair_type ("'",
    "Matrix transpose operator.  For complex matrices, computes the\n\
complex conjugate (Hermitian) transpose.  See also `.''\n\
\n\
The single quote character may also be used to delimit strings, but\n\
it is better to use the double quote character, since that is never\n\
ambiguous"),

  pair_type ("(",
    "Array index or function argument delimiter."),

  pair_type (")",
    "Array index or function argument delimiter."),

  pair_type ("*",
    "Multiplication operator.  See also `.*'"),

  pair_type ("**",
    "Power operator.  See also `^', `.**', and `.^'"),

  pair_type ("+",
    "Addition operator."),

  pair_type ("++",
    "Increment operator.  As in C, may be applied as a prefix or postfix\n\
operator."),

  pair_type (",",
    "Array index, function argument, or command separator."),

  pair_type ("-",
    "Subtraction or unary negation operator."),

  pair_type ("--",
    "Decrement operator.  As in C, may be applied as a prefix or postfix\n\
operator."),

  pair_type (".'",
    "Matrix transpose operator.  For complex matrices, computes the\n\
transpose, *not* the complex conjugate transpose.  See also `''."),

  pair_type (".*",
    "Element by element multiplication operator.  See also `*'."),

  pair_type (".**",
    "Element by element power operator.  See also `**', `^', and `.^'."),

  pair_type ("./",
    "Element by element division operator.  See also `/' and `\\'."),

  pair_type (".^",
    "Element by element power operator.  See also `**', `^', and `.^'."),

  pair_type ("/",
    "Right division.  See also `\\' and `./'."),

  pair_type (":",
    "Select entire rows or columns of matrices."),

  pair_type (";",
    "Array row or command separator.  See also `,'."),

  pair_type ("<",
    "Less than operator."),

  pair_type ("<=",
    "Less than or equals operator."),

  pair_type ("=",
    "Assignment operator."),

  pair_type ("==",
    "Equality test operator."),

  pair_type (">",
    "Greater than operator."),

  pair_type (">=",
    "Greater than or equals operator."),

  pair_type ("[",
    "Return list delimiter.  See also `]'."),

  pair_type ("\\",
    "Left division operator.  See also `/' and `./'."),

  pair_type ("]",
    "Return list delimiter.  See also `['."),

  pair_type ("^",
    "Power operator.  See also `**', `.^', and `.**.'"),

  pair_type ("|",
    "Element by element logical or operator.  See also `||'."),

  pair_type ("||",
    "Logical or operator (with short-circuit evaluation).  See also `|'."),

  pair_type ("~",
    "Logical not operator.  See also `!' and `~'."),

  pair_type ("~=",
    "Logical not equals operator.  See also `!='."),
};

const static pair_type keywords[] =
{
  pair_type ("break",
    "-*- texinfo -*-\n\
@deffn Keyword break\n\
Exit the innermost enclosing do, while or for loop.\n\
@seealso{do, while, for, continue}\n\
@end deffn"),

  pair_type ("case",
    "-*- texinfo -*-\n\
@deffn Keyword case @{@var{value}@}\n\
A case statement in an switch.  Octave cases are exclusive and do not\n\
fall-through as do C-language cases.  A switch statement must have at least\n\
one case.  See @code{switch} for an example.\n\
@seealso{switch}\n\
@end deffn"),

  pair_type ("catch",
    "-*- texinfo -*-\n\
@deffn Keyword catch\n\
Begin the cleanup part of a try-catch block.\n\
@seealso{try}\n\
@end deffn"),

  pair_type ("continue",
    "-*- texinfo -*-\n\
@deffn Keyword continue\n\
Jump to the end of the innermost enclosing do, while or for loop.\n\
@seealso{do, while, for, break}\n\
@end deffn"),

  pair_type ("do",
    "-*- texinfo -*-\n\
@deffn Keyword do\n\
Begin a do-until loop.  This differs from a do-while loop in that the\n\
body of the loop is executed at least once.\n\
@seealso{while}\n\
@end deffn"),

  pair_type ("else",
    "-*- texinfo -*-\n\
@deffn Keyword else\n\
Alternate action for an if block.  See @code{if} for an example.\n\
@seealso{if}\n\
@end deffn"),

  pair_type ("elseif",
    "-*- texinfo -*-\n\
@deffn Keyword elseif (@var{condition})\n\
Alternate conditional test for an if block.  See @code{if} for an example.\n\
@seealso{if}\n\
@end deffn"),

  pair_type ("end",
    "-*- texinfo -*-\n\
@deffn Keyword end\n\
Mark the end of any @code{for}, @code{if}, @code{do}, @code{while}, or @code{function} block.\n\
@seealso{for, if, do, while, function}\n\
@end deffn"),

  pair_type ("end_try_catch",
    "-*- texinfo -*-\n\
@deffn Keyword end_try_catch\n\
Mark the end of an @code{try-catch} block.\n\
@seealso{try, catch}\n\
@end deffn"), 

  pair_type ("end_unwind_protect",
    "-*- texinfo -*-\n\
@deffn Keyword end_unwind_protect\n\
Mark the end of an unwind_protect block.\n\
@seealso{unwind_protect}\n\
@end deffn"), 

  pair_type ("endfor",
    "-*- texinfo -*-\n\
@deffn Keyword endfor\n\
Mark the end of a for loop.  See @code{for} for an example.\n\
@seealso{for}\n\
@end deffn"),

  pair_type ("endfunction",
    "-*- texinfo -*-\n\
@deffn Keyword endfunction\n\
Mark the end of a function.\n\
@seealso{function}\n\
@end deffn"),

  pair_type ("endif",
    "-*- texinfo -*-\n\
@deffn Keyword endif\n\
Mark the end of an if block.  See @code{if} for an example.\n\
@seealso{if}\n\
@end deffn"),

  pair_type ("endswitch",
    "-*- texinfo -*-\n\
@deffn Keyword endswitch\n\
Mark the end of a switch block.  See @code{switch} for an example.\n\
@seealso{switch}\n\
@end deffn"),

  pair_type ("endwhile",
    "-*- texinfo -*-\n\
@deffn Keyword endwhile\n\
Mark the end of a while loop.  See @code{while} for an example.\n\
@seealso{do, while}\n\
@end deffn"),

  pair_type ("for",
    "-*- texinfo -*-\n\
@deffn Keyword for @var{i} = @var{range}\n\
Begin a for loop.\n\
@example\n\
@group\n\
for i = 1:10\n\
  i\n\
endfor\n\
@end group\n\
@end example\n\
@seealso{do, while}\n\
@end deffn"),

  pair_type ("function",
    "-*- texinfo -*-\n\
@deffn Keyword function @var{outputs} = function (@var{input}, @dots{})\n\
@deffnx Keyword function {} function (@var{input}, @dots{})\n\
@deffnx Keyword function @var{outputs} = function\n\
Begin a function body with @var{outputs} as results and @var{inputs} as\n\
parameters.\n\
@seealso{return}\n\
@end deffn"),

  pair_type ("global",
    "-*- texinfo -*-\n\
@deffn Keyword global\n\
Declare variables to have global scope.\n\
@example\n\
@group\n\
global @var{x};\n\
if isempty (@var{x})\n\
  x = 1;\n\
endif\n\
@end group\n\
@end example\n\
@seealso{persistent}\n\
@end deffn"),

  pair_type ("if",
    "-*- texinfo -*-\n\
@deffn Keyword if (@var{cond}) @dots{} endif\n\
@deffnx Keyword if (@var{cond}) @dots{} else @dots{} endif\n\
@deffnx Keyword if (@var{cond}) @dots{} elseif (@var{cond}) @dots{} endif\n\
@deffnx Keyword if (@var{cond}) @dots{} elseif (@var{cond}) @dots{} else @dots{} endif\n\
Begin an if block.\n\
@example\n\
@group\n\
x = 1;\n\
if (x == 1)\n\
  disp (\"one\");\n\
elseif (x == 2)\n\
  disp (\"two\");\n\
else\n\
  disp (\"not one or two\");\n\
endif\n\
@end group\n\
@end example\n\
@seealso{switch}\n\
@end deffn"),

  pair_type ("otherwise",
    "-*- texinfo -*-\n\
@deffn Keyword otherwise\n\
The default statement in a switch block (similar to else in an if block).\n\
@seealso{switch}\n\
@end deffn"),

  pair_type ("persistent",
    "-*- texinfo -*-\n\
@deffn Keyword persistent @var{var}\n\
Declare variables as persistent.  A variable that has been declared\n\
persistent within a function will retain its contents in memory between\n\
subsequent calls to the same function.  The difference between persistent\n\
variables and global variables is that persistent variables are local in \n\
scope to a particular function and are not visible elsewhere.\n\
@seealso{global}\n\
@end deffn"),

  pair_type ("replot",
    "-*- texinfo -*-\n\
@deffn Keyword replot\n\
Replot a graphic.\n\
@seealso{plot}\n\
@end deffn"),

  pair_type ("return",
    "-*- texinfo -*-\n\
@deffn Keyword return\n\
Return from a function.\n\
@seealso{function}\n\
@end deffn"),

  pair_type ("static",
    "-*- texinfo -*-\n\
@deffn Keyword static\n\
This function has been deprecated in favor of persistent.\n\
@seealso{persistent}\n\
@end deffn"),

  pair_type ("switch",
    "-*- texinfo -*-\n\
@deffn Keyword switch @var{statement}\n\
Begin a switch block.\n\
@example\n\
@group\n\
yesno = \"yes\"\n\
\n\
switch yesno\n\
  case @{\"Yes\" \"yes\" \"YES\" \"y\" \"Y\"@}\n\
    value = 1;\n\
  case @{\"No\" \"no\" \"NO\" \"n\" \"N\"@}\n\
    value = 0;\n\
  otherwise\n\
    error (\"invalid value\");\n\
endswitch\n\
@end group\n\
@end example\n\
@seealso{if, case, otherwise}\n\
@end deffn"),

  pair_type ("try",
    "-*- texinfo -*-\n\
@deffn Keyword try\n\
Begin a try-catch block.\n\
\n\
If an error occurs within a try block, then the catch code will be run and\n\
execution will proceed after the catch block (though it is often\n\
recommended to use the lasterr function to re-throw the error after cleanup\n\
is completed).\n\
@seealso{catch,unwind_protect}\n\
@end deffn"), 

  pair_type ("until",
    "-*- texinfo -*-\n\
@deffn Keyword until\n\
End a do-until loop.\n\
@seealso{do}\n\
@end deffn"),

  pair_type ("unwind_protect",
    "-*- texinfo -*-\n\
@deffn Keyword unwind_protect\n\
Begin an unwind_protect block.\n\
\n\
If an error occurs within the first part of an unwind_protect block\n\
the commands within the unwind_protect_cleanup block are executed before\n\
the error is thrown.  If an error is not thrown, then the\n\
unwind_protect_cleanup block is still executed (in other words, the\n\
unwind_protect_cleanup will be run with or without an error in the\n\
unwind_protect block).\n\
@seealso{unwind_protect_cleanup,try}\n\
@end deffn"), 

  pair_type ("unwind_protect_cleanup",
    "-*- texinfo -*-\n\
@deffn Keyword unwind_protect_cleanup\n\
Begin the cleanup section of an unwind_protect block.\n\
@seealso{unwind_protect}\n\
@end deffn"), 

  pair_type ("varargin",
    "-*- texinfo -*-\n\
@deffn Keyword varargin\n\
Pass an arbitrary number of arguments into a function.\n\
@seealso{varargout, nargin, nargout}\n\
@end deffn"),

  pair_type ("varargout",
    "-*- texinfo -*-\n\
@deffn Keyword varargout\n\
Pass an arbitrary number of arguments out of a function.\n\
@seealso{varargin, nargin, nargout}\n\
@end deffn"),

  pair_type ("while",
    "-*- texinfo -*-\n\
@deffn Keyword while\n\
Begin a while loop.\n\
@seealso{do}\n\
@end deffn"),
};

// Return a copy of the operator or keyword names.
static string_vector
names (const map_type& lst)
{
  string_vector retval (lst.size ());
  int j = 0;
  for (map_iter iter = lst.begin (); iter != lst.end (); iter ++)
    retval [j++] = iter->first;
  return retval;
}

const static map_type operators_map (operators, operators + size (operators));
const static map_type keywords_map (keywords, keywords + size (keywords));
const static string_vector keyword_names = names (keywords_map);

// FIXME -- It's not likely that this does the right thing now.

string_vector
make_name_list (void)
{
  const int key_len = keyword_names.length ();

  const string_vector bif = symbol_table::built_in_function_names ();
  const int bif_len = bif.length ();

  // FIXME -- is this really necessary here?
  const string_vector glb = symbol_table::global_variable_names ();
  const int glb_len = glb.length ();

  // FIXME -- is this really necessary here?
  const string_vector top = symbol_table::top_level_variable_names ();
  const int top_len = top.length ();

  string_vector lcl;
  if (! symbol_table::at_top_level ())
    lcl = symbol_table::variable_names ();
  const int lcl_len = lcl.length ();

  const string_vector ffl = load_path::fcn_names ();
  const int ffl_len = ffl.length ();

  const string_vector afl = autoloaded_functions ();
  const int afl_len = afl.length ();

  const int total_len = key_len + bif_len + glb_len + top_len + lcl_len
    + ffl_len + afl_len;

  string_vector list (total_len);

  // Put all the symbols in one big list.

  int j = 0;
  int i = 0;
  for (i = 0; i < key_len; i++)
    list[j++] = keyword_names[i];

  for (i = 0; i < bif_len; i++)
    list[j++] = bif[i];

  for (i = 0; i < glb_len; i++)
    list[j++] = glb[i];

  for (i = 0; i < top_len; i++)
    list[j++] = top[i];

  for (i = 0; i < lcl_len; i++)
    list[j++] = lcl[i];

  for (i = 0; i < ffl_len; i++)
    list[j++] = ffl[i];

  for (i = 0; i < afl_len; i++)
    list[j++] = afl[i];

  return list;
}

static bool
looks_like_html (const std::string& msg)
{
  const size_t p1 = msg.find ('\n');
  std::string t = msg.substr (0, p1);
  const size_t p2 = t.find ("<html"); // FIXME: this comparison should be case-insensitive
  
   return (p2 != std::string::npos);
}

static bool
looks_like_texinfo (const std::string& msg, size_t& p1)
{
  p1 = msg.find ('\n');

  std::string t = msg.substr (0, p1);

  if (p1 == std::string::npos)
    p1 = 0;

  size_t p2 = t.find ("-*- texinfo -*-");

  return (p2 != std::string::npos);
}

static bool
raw_help_from_symbol_table (const std::string& nm, std::string& h, 
			    std::string& w, bool& symbol_found)
{
  bool retval = false;

  octave_value val = symbol_table::find_function (nm);

  if (val.is_defined ())
    {
      octave_function *fcn = val.function_value ();

      if (fcn)
	{
	  symbol_found = true;

	  h = fcn->doc_string ();

          retval = true;

	  w = fcn->fcn_file_name ();

	  if (w.empty ())
            w = fcn->is_user_function ()
              ? "command-line function" : "built-in function";
	}
    }

  return retval;
}

static bool
raw_help_from_file (const std::string& nm, std::string& h, 
		    std::string& file, bool& symbol_found)
{
  bool retval = false;

  // FIXME -- this is a bit of a kluge...
  unwind_protect_bool (reading_script_file);
  reading_script_file = true;

  h = get_help_from_file (nm, symbol_found, file);

  unwind_protect::run ();

  if (h.length () > 0)
    retval = true;

  return retval;
}

static bool
raw_help_from_map (const std::string& nm, std::string& h, 
		   const map_type& map, bool& symbol_found)
{
  map_iter idx = map.find (nm);
  symbol_found = (idx != map.end ());
  h = (symbol_found) ? idx->second : "";
  return symbol_found;
}

std::string
raw_help (const std::string& nm, bool& symbol_found)
{
  std::string h;
  std::string w;
  std::string f;

  (raw_help_from_symbol_table (nm, h, w, symbol_found)
   || raw_help_from_file (nm, h, f, symbol_found)
   || raw_help_from_map (nm, h, operators_map, symbol_found)
   || raw_help_from_map (nm, h, keywords_map, symbol_found));

  return h;
}

static void
do_get_help_text (const std::string name, std::string& text,
		  std::string& format)
{
  bool symbol_found = false;
  text = raw_help (name, symbol_found);
  
  format = "Not found";
  if (symbol_found)
    {
      size_t idx = -1;
      if (text.empty ())
        {
          format = "Not documented";
        }
      else if (looks_like_texinfo (text, idx))
        {
          format = "texinfo";
          text.erase (0, idx);
        }
      else if (looks_like_html (text))
        {
          format = "html";
        }
      else
        {
          format = "plain text";
        }
    }
}

DEFUN (get_help_text, args, , "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{text}, @var{format}] =} get_help_text (@var{name})\n\
Returns the help text of a given function.\n\
\n\
This function returns the raw help text @var{text} and an indication of\n\
its format for the function @var{name}.  The format indication @var{format}\n\
is a string that can be either @t{\"texinfo\"}, @t{\"html\"}, or\n\
@t{\"plain text\"}.\n\
\n\
To convert the help text to other formats, use the @code{makeinfo} function.\n\
\n\
@seealso{makeinfo}\n\
@end deftypefn")
{
  octave_value_list retval;

  if (args.length () == 1)
    {
      const std::string name = args (0).string_value ();

      if (! error_state)
	{
	  std::string text;
	  std::string format;

	  do_get_help_text (name, text, format);
  
	  retval(1) = format;
	  retval(0) = text;
	}
      else
	error ("get_help_text: invalid input");
    }
  else
    print_usage ();

  return retval;
}

// Return a cell array of strings containing the names of all
// operators.

DEFUN (__operators__, , ,
  "-*- texinfo -*-\n\
@deftypefn {Function File} __operators__ ()\n\
Undocumented internal function.\n\
@end deftypefn")
{
  return octave_value (Cell (names (operators_map)));
}

// Return a cell array of strings containing the names of all
// keywords.

DEFUN (__keywords__, , ,
  "-*- texinfo -*-\n\
@deftypefn {Function File} __keywords__ ()\n\
Undocumented internal function.\n\
@end deftypefn")
{
  return octave_value (Cell (names (keywords_map)));
}

// Return a cell array of strings containing the names of all builtin
// functions.

DEFUN (__builtins__, , ,
  "-*- texinfo -*-\n\
@deftypefn {Function File} __builtins__ ()\n\
Undocumented internal function.\n\
@end deftypefn")
{
  const string_vector bif = symbol_table::built_in_function_names ();

  return octave_value (Cell (bif));
}

static std::string
do_which (const std::string& name, std::string& type)
{
  std::string file;

  type = std::string ();

  octave_value val = symbol_table::find_function (name);

  if (name.find_first_of ('.') == std::string::npos)
    {
      if (val.is_defined ())
        {
          octave_function *fcn = val.function_value ();

          if (fcn)
            {
              file = fcn->fcn_file_name ();

              if (file.empty ())
                {
                  if (fcn->is_user_function ())
                    type = "command-line function";
                  else
                    type = "built-in function";
                }
              else
                type = val.is_user_script ()
                  ? std::string ("script") : std::string ("function");
            }
        }
      else
        {
          // We might find a file that contains only a doc string.

          file = load_path::find_fcn_file (name);
        }
    }
  else
    {
      // File query.

      // For compatibility: "file." queries "file".
      if (name.size () > 1 && name[name.size () - 1] == '.')
        file = load_path::find_file (name.substr (0, name.size () - 1));
      else
        file = load_path::find_file (name);
    }


  return file;
}

std::string
do_which (const std::string& name)
{
  std::string retval;

  std::string type;

  retval = do_which (name, type);

  return retval;
}

DEFUN (__which__, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {} __which__ (@var{name}, @dots{})\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value retval;

  string_vector argv = args.make_argv ("which");

  if (! error_state)
    {
      int argc = argv.length ();

      if (argc > 1)
	{
	  Octave_map m (dim_vector (1, argc-1));

	  Cell names (1, argc-1);
	  Cell files (1, argc-1);
	  Cell types (1, argc-1);

	  for (int i = 1; i < argc; i++)
	    {
	      std::string name = argv[i];

	      std::string type;

	      std::string file = do_which (name, type);

	      names(i-1) = name;
	      files(i-1) = file;
	      types(i-1) = type;
	    }

	  m.assign ("name", names);
	  m.assign ("file", files);
	  m.assign ("type", types);

	  retval = m;
	}
      else
	print_usage ();
    }

  return retval;
}

// FIXME -- Are we sure this function always does the right thing?
inline bool
file_is_in_dir (const std::string filename, const std::string dir)
{
  if (filename.find (dir) == 0)
    {
      const int dir_len = dir.size ();
      const int filename_len = filename.size ();
      const int max_allowed_seps = file_ops::is_dir_sep (dir [dir_len-1]) ? 0 : 1;
      
      int num_seps = 0;
      for (int i = dir_len; i < filename_len; i++)
        if (file_ops::is_dir_sep (filename [i]))
          num_seps ++;
      
      return (num_seps <= max_allowed_seps);
    }
  else
    return false;
}

// Return a cell array of strings containing the names of all
// functions available in DIRECTORY.  If no directory is given, search
// the current path.

DEFUN (__list_functions__, args, ,
  "-*- texinfo -*-\n\
@deftypefn {Function File} {@var{retval} =} __list_functions__ ()\n\
@deftypefnx{Function File} {@var{retval} =} __list_functions__ (@var{directory})\n\
Undocumented internal function.\n\
@end deftypefn")
{
  octave_value retval;

  // Get list of functions
  string_vector ffl = load_path::fcn_names ();
  string_vector afl = autoloaded_functions ();
  
  if (args.length () == 0)
    retval = Cell (ffl.append (afl));
  else
    {
      std::string dir = args (0).string_value ();

      if (! error_state)
	{
	  string_vector fl = load_path::files (dir, true);

	  if (! error_state)
	    {
	      // Return a sorted list with unique entries (in case of
	      // .m and .oct versions of the same function in a given
	      // directory, for example).
	      fl.sort (true);

	      retval = Cell (fl);
	    }
	}
      else
        error ("__list_functions__: input must be a string");
    }  

  return retval;
}

DEFUN (doc_cache_file, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{val} =} doc_cache_file ()\n\
@deftypefnx {Built-in Function} {@var{old_val} =} doc_cache_file (@var{new_val})\n\
Query or set the internal variable that specifies the name of the\n\
Octave documentation cache file.  A cache file significantly improves\n\
the performance of the @code{lookfor} command.  The default value is \n\
@file{@var{octave-home}/share/octave/@var{version}/etc/doc-cache},\n\
in which @var{octave-home} is the root directory of the Octave installation,\n\
and @var{version} is the Octave version number.\n\
The default value may be overridden by the environment variable\n\
@w{@code{OCTAVE_DOC_CACHE_FILE}}, or the command line argument\n\
@samp{--doc-cache-file NAME}.\n\
@seealso{lookfor, info_program, doc, help, makeinfo_program}\n\
@end deftypefn")
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (doc_cache_file);
}

DEFUN (info_file, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{val} =} info_file ()\n\
@deftypefnx {Built-in Function} {@var{old_val} =} info_file (@var{new_val})\n\
Query or set the internal variable that specifies the name of the\n\
Octave info file.  The default value is\n\
@file{@var{octave-home}/info/octave.info}, in\n\
which @var{octave-home} is the root directory of the Octave installation.\n\
The default value may be overridden by the environment variable\n\
@w{@code{OCTAVE_INFO_FILE}}, or the command line argument\n\
@samp{--info-file NAME}.\n\
@seealso{info_program, doc, help, makeinfo_program}\n\
@end deftypefn")
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (info_file);
}

DEFUN (info_program, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{val} =} info_program ()\n\
@deftypefnx {Built-in Function} {@var{old_val} =} info_program (@var{new_val})\n\
Query or set the internal variable that specifies the name of the\n\
info program to run.  The default value is\n\
@file{@var{octave-home}/libexec/octave/@var{version}/exec/@var{arch}/info}\n\
in which @var{octave-home} is the root directory of the Octave installation,\n\
@var{version} is the Octave version number, and @var{arch}\n\
is the system type (for example, @code{i686-pc-linux-gnu}).  The\n\
default value may be overridden by the environment variable\n\
@w{@code{OCTAVE_INFO_PROGRAM}}, or the command line argument\n\
@samp{--info-program NAME}.\n\
@seealso{info_file, doc, help, makeinfo_program}\n\
@end deftypefn")
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (info_program);
}

DEFUN (makeinfo_program, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{val} =} makeinfo_program ()\n\
@deftypefnx {Built-in Function} {@var{old_val} =} makeinfo_program (@var{new_val})\n\
Query or set the internal variable that specifies the name of the\n\
program that Octave runs to format help text containing\n\
Texinfo markup commands.  The default value is @code{makeinfo}.\n\
@seealso{info_file, info_program, doc, help}\n\
@end deftypefn")
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (makeinfo_program);
}

DEFUN (suppress_verbose_help_message, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Built-in Function} {@var{val} =} suppress_verbose_help_message ()\n\
@deftypefnx {Built-in Function} {@var{old_val} =} suppress_verbose_help_message (@var{new_val})\n\
Query or set the internal variable that controls whether Octave\n\
will add additional help information to the end of the output from\n\
the @code{help} command and usage messages for built-in commands.\n\
@end deftypefn")
{
  return SET_INTERNAL_VARIABLE (suppress_verbose_help_message);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/