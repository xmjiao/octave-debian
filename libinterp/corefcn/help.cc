/*

Copyright (C) 1993-2015 John W. Eaton

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

#include <cstdlib>
#include <cstring>

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "cmd-edit.h"
#include "file-ops.h"
#include "file-stat.h"
#include "oct-env.h"
#include "oct-locbuf.h"
#include "str-vec.h"

#include <defaults.h>
#include "Cell.h"
#include "defun.h"
#include "dirfns.h"
#include "error.h"
#include "errwarn.h"
#include "help.h"
#include "input.h"
#include "load-path.h"
#include "ovl.h"
#include "ov-usr-fcn.h"
#include "ov-fcn-handle.h"
#include "pager.h"
#include "parse.h"
#include "pathsearch.h"
#include "procstream.h"
#include "pt-pr-code.h"
#include "sighandlers.h"
#include "symtab.h"
#include "toplev.h"
#include "unwind-prot.h"
#include "utils.h"
#include "variables.h"
#include "version.h"
#include "quit.h"

// Name of the doc cache file specified on the command line.
// (--doc-cache-file file)
std::string Vdoc_cache_file;

// Name of the file containing local Texinfo macros that are prepended
// to doc strings before processing.
// (--texi-macros-file)
std::string Vtexi_macros_file;

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

template <typename T, size_t z>
size_t
size (T const (&)[z])
{
  return z;
}

const static pair_type operators[] =
{
  pair_type ("!",
  "-*- texinfo -*-\n\
@deftypefn {} {} !\n\
Logical 'not' operator.\n\
@seealso{~, not}\n\
@end deftypefn"),

  pair_type ("~",
  "-*- texinfo -*-\n\
@deftypefn {} {} ~\n\
Logical 'not' operator.\n\
@seealso{!, not}\n\
@end deftypefn"),

  pair_type ("!=",
  "-*- texinfo -*-\n\
@deftypefn {} {} !=\n\
Logical 'not equals' operator.\n\
@seealso{~=, ne}\n\
@end deftypefn"),

  pair_type ("~=",
  "-*- texinfo -*-\n\
@deftypefn {} {} ~=\n\
Logical 'not equals' operator.\n\
@seealso{!=, ne}\n\
@end deftypefn"),

  pair_type ("\"",
  "-*- texinfo -*-\n\
@deftypefn {} {} \"\n\
String delimiter.\n\
@end deftypefn"),

  pair_type ("#",
  "-*- texinfo -*-\n\
@deftypefn {} {} #\n\
Begin comment character.\n\
@seealso{%, #@\\{}\n\
@end deftypefn"),

  pair_type ("%",
  "-*- texinfo -*-\n\
@deftypefn {} {} %\n\
Begin comment character.\n\
@seealso{#, %@\\{}\n\
@end deftypefn"),

  pair_type ("#{",
  "-*- texinfo -*-\n\
@deftypefn {} {} #@{\n\
Begin block comment.  There must be nothing else, other than\n\
whitespace, in the line both before and after @code{#@{}.\n\
It is possible to nest block comments.\n\
@seealso{%@\\{, #@\\}, #}\n\
@end deftypefn"),

  pair_type ("%{",
  "-*- texinfo -*-\n\
@deftypefn {} {} %@{\n\
Begin block comment.  There must be nothing else, other than\n\
whitespace, in the line both before and after @code{%@{}.\n\
It is possible to nest block comments.\n\
@seealso{#@\\{, %@\\}, %}\n\
@end deftypefn"),

  pair_type ("#}",
  "-*- texinfo -*-\n\
@deftypefn {} {} #@}\n\
Close block comment.  There must be nothing else, other than\n\
whitespace, in the line both before and after @code{#@}}.\n\
It is possible to nest block comments.\n\
@seealso{%@\\}, #@\\{, #}\n\
@end deftypefn"),

  pair_type ("%}",
  "-*- texinfo -*-\n\
@deftypefn {} {} %@}\n\
Close block comment.  There must be nothing else, other than\n\
whitespace, in the line both before and after @code{%@}}.\n\
It is possible to nest block comments.\n\
@seealso{#@\\}, %@\\{, %}\n\
@end deftypefn"),

  pair_type ("...",
  "-*- texinfo -*-\n\
@deftypefn {} {} ...\n\
Continuation marker.  Joins current line with following line.\n\
@end deftypefn"),

  pair_type ("&",
  "-*- texinfo -*-\n\
@deftypefn {} {} &\n\
Element by element logical 'and' operator.\n\
@seealso{&&, and}\n\
@end deftypefn"),

  pair_type ("&&",
  "-*- texinfo -*-\n\
@deftypefn {} {} &&\n\
Logical 'and' operator (with short-circuit evaluation).\n\
@seealso{&, and}\n\
@end deftypefn"),

  pair_type ("'",
  "-*- texinfo -*-\n\
@deftypefn {} {} '\n\
Matrix transpose operator.  For complex matrices, computes the\n\
complex conjugate (Hermitian) transpose.\n\
\n\
The single quote character may also be used to delimit strings, but\n\
it is better to use the double quote character, since that is never\n\
ambiguous.\n\
@seealso{.', transpose}\n\
@end deftypefn"),

  pair_type ("(",
  "-*- texinfo -*-\n\
@deftypefn {} {} (\n\
Array index or function argument delimiter.\n\
@end deftypefn"),

  pair_type (")",
  "-*- texinfo -*-\n\
@deftypefn {} {})\n\
Array index or function argument delimiter.\n\
@end deftypefn"),

  pair_type ("*",
  "-*- texinfo -*-\n\
@deftypefn {} {} *\n\
Multiplication operator.\n\
@seealso{.*, times}\n\
@end deftypefn"),

  pair_type ("**",
  "-*- texinfo -*-\n\
@deftypefn {} {} **\n\
Power operator.  This may return complex results for real inputs.  Use\n\
@code{realsqrt}, @code{cbrt}, @code{nthroot}, or @code{realroot} to obtain\n\
real results when possible.\n\
@seealso{power, ^, .**, .^, realpow, realsqrt, cbrt, nthroot}\n\
@end deftypefn"),

  pair_type ("^",
  "-*- texinfo -*-\n\
@deftypefn {} {} ^\n\
Power operator.  This may return complex results for real inputs.  Use\n\
@code{realsqrt}, @code{cbrt}, @code{nthroot}, or @code{realroot} to obtain\n\
real results when possible.\n\
@seealso{power, **, .^, .**, realpow, realsqrt, cbrt, nthroot}\n\
@end deftypefn"),

  pair_type ("+",
  "-*- texinfo -*-\n\
@deftypefn {} {} +\n\
Addition operator.\n\
@seealso{plus}\n\
@end deftypefn"),

  pair_type ("++",
  "-*- texinfo -*-\n\
@deftypefn {} {} ++\n\
Increment operator.  As in C, may be applied as a prefix or postfix\n\
operator.\n\
@seealso{--}\n\
@end deftypefn"),

  pair_type (",",
  "-*- texinfo -*-\n\
@deftypefn {} {} ,\n\
Array index, function argument, or command separator.\n\
@end deftypefn"),

  pair_type ("-",
  "-*- texinfo -*-\n\
@deftypefn {} {} -\n\
Subtraction or unary negation operator.\n\
@seealso{minus}\n\
@end deftypefn"),

  pair_type ("--",
  "-*- texinfo -*-\n\
@deftypefn {} {} --\n\
Decrement operator.  As in C, may be applied as a prefix or postfix\n\
operator.\n\
@seealso{++}\n\
@end deftypefn"),

  pair_type (".'",
  "-*- texinfo -*-\n\
@deftypefn {} {} .'\n\
Matrix transpose operator.  For complex matrices, computes the\n\
transpose, @emph{not} the complex conjugate transpose.\n\
@seealso{', transpose}\n\
@end deftypefn"),

  pair_type (".*",
  "-*- texinfo -*-\n\
@deftypefn {} {} .*\n\
Element by element multiplication operator.\n\
@seealso{*, times}\n\
@end deftypefn"),

  pair_type (".**",
  "-*- texinfo -*-\n\
@deftypefn {} {} .*\n\
Element by element power operator.  If several complex results are possible,\n\
returns the one with smallest non-negative argument (angle).  Use\n\
@code{realpow}, @code{realsqrt}, @code{cbrt}, or @code{nthroot} if a\n\
real result is preferred.\n\
@seealso{**, ^, .^, power, realpow, realsqrt, cbrt, nthroot}\n\
@end deftypefn"),

  pair_type (".^",
  "-*- texinfo -*-\n\
@deftypefn {} {} .^\n\
Element by element power operator.  If several complex results are possible,\n\
returns the one with smallest non-negative argument (angle).  Use\n\
@code{realpow}, @code{realsqrt}, @code{cbrt}, or @code{nthroot} if a\n\
real result is preferred.\n\
@seealso{.**, ^, **, power, realpow, realsqrt, cbrt, nthroot}\n\
@end deftypefn"),

  pair_type ("./",
  "-*- texinfo -*-\n\
@deftypefn {} {} ./\n\
Element by element right division operator.\n\
@seealso{/, .\\, rdivide, mrdivide}\n\
@end deftypefn"),

  pair_type ("/",
  "-*- texinfo -*-\n\
@deftypefn {} {} /\n\
Right division operator.\n\
@seealso{./, \\, rdivide, mrdivide}\n\
@end deftypefn"),

  pair_type (".\\",
  "-*- texinfo -*-\n\
@deftypefn {} {} .\\\n\
Element by element left division operator.\n\
@seealso{\\, ./, rdivide, mrdivide}\n\
@end deftypefn"),

  pair_type ("\\",
  "-*- texinfo -*-\n\
@deftypefn {} {} \\\n\
Left division operator.\n\
@seealso{.\\, /, ldivide, mldivide}\n\
@end deftypefn"),

  pair_type (":",
  "-*- texinfo -*-\n\
@deftypefn {} {} :\n\
Select entire rows or columns of matrices.\n\
@end deftypefn"),

  pair_type (";",
  "-*- texinfo -*-\n\
@deftypefn {} {} ;\n\
Array row or command separator.\n\
@seealso{,}\n\
@end deftypefn"),

  pair_type ("<",
  "-*- texinfo -*-\n\
@deftypefn {} {} <\n\
'Less than' operator.\n\
@seealso{lt}\n\
@end deftypefn"),

  pair_type ("<=",
  "-*- texinfo -*-\n\
@deftypefn {} {} <=\n\
'Less than' or 'equals' operator.\n\
@seealso{le}\n\
@end deftypefn"),

  pair_type ("=",
  "-*- texinfo -*-\n\
@deftypefn {} {} =\n\
Assignment operator.\n\
@end deftypefn"),

  pair_type ("==",
  "-*- texinfo -*-\n\
@deftypefn {} {} ==\n\
Equality test operator.\n\
@seealso{eq}\n\
@end deftypefn"),

  pair_type (">",
  "-*- texinfo -*-\n\
@deftypefn {} {} >\n\
'Greater than' operator.\n\
@seealso{gt}\n\
@end deftypefn"),

  pair_type (">=",
  "-*- texinfo -*-\n\
@deftypefn {} {} >=\n\
'Greater than' or 'equals' operator.\n\
@seealso{ge}\n\
@end deftypefn"),

  pair_type ("[",
  "-*- texinfo -*-\n\
@deftypefn {} {} [\n\
Return list delimiter.\n\
@seealso{]}\n\
@end deftypefn"),

  pair_type ("]",
  "-*- texinfo -*-\n\
@deftypefn {} {} ]\n\
Return list delimiter.\n\
@seealso{[}\n\
@end deftypefn"),

  pair_type ("|",
  "-*- texinfo -*-\n\
@deftypefn {} {} |\n\
Element by element logical 'or' operator.\n\
@seealso{||, or}\n\
@end deftypefn"),

  pair_type ("||",
  "-*- texinfo -*-\n\
@deftypefn {} {} ||\n\
Logical 'or' (with short-circuit evaluation) operator.\n\
@seealso{|, or}\n\
@end deftypefn"),
};

const static pair_type keywords[] =
{
  pair_type ("break",
  "-*- texinfo -*-\n\
@deftypefn {} {} break\n\
Exit the innermost enclosing do, while or for loop.\n\
@seealso{do, while, for, parfor, continue}\n\
@end deftypefn"),

  pair_type ("case",
  "-*- texinfo -*-\n\
@deftypefn  {} {} case @var{value}\n\
@deftypefnx {} {} case @{@var{value}, @dots{}@}\n\
A case statement in a switch.  Octave cases are exclusive and do not\n\
fall-through as do C-language cases.  A switch statement must have at least\n\
one case.  See @code{switch} for an example.\n\
@seealso{switch}\n\
@end deftypefn"),

  pair_type ("catch",
  "-*- texinfo -*-\n\
@deftypefn  {} {} catch\n\
@deftypefnx {} {} catch @var{value}\n\
Begin the cleanup part of a try-catch block.\n\
@seealso{try}\n\
@end deftypefn"),

  pair_type ("continue",
  "-*- texinfo -*-\n\
@deftypefn {} {} continue\n\
Jump to the end of the innermost enclosing do, while or for loop.\n\
@seealso{do, while, for, parfor, break}\n\
@end deftypefn"),

  pair_type ("do",
  "-*- texinfo -*-\n\
@deftypefn {} {} do\n\
Begin a do-until loop.  This differs from a do-while loop in that the\n\
body of the loop is executed at least once.\n\
\n\
@example\n\
@group\n\
i = 0;\n\
do\n\
  i++\n\
until (i == 10)\n\
@end group\n\
@end example\n\
@seealso{for, until, while}\n\
@end deftypefn"),

  pair_type ("else",
  "-*- texinfo -*-\n\
@deftypefn {} {} else\n\
Alternate action for an if block.  See @code{if} for an example.\n\
@seealso{if}\n\
@end deftypefn"),

  pair_type ("elseif",
  "-*- texinfo -*-\n\
@deftypefn {} {} elseif (@var{condition})\n\
Alternate conditional test for an if block.  See @code{if} for an example.\n\
@seealso{if}\n\
@end deftypefn"),

  pair_type ("end",
  "-*- texinfo -*-\n\
@deftypefn {} {} end\n\
Mark the end of any @code{for}, @code{parfor}, @code{if}, @code{do},\n\
@code{while}, @code{function}, @code{switch}, @code{try}, or\n\
@code{unwind_protect} block.\n\
@seealso{for, parfor, if, do, while, function, switch, try, unwind_protect}\n\
@end deftypefn"),

  pair_type ("end_try_catch",
  "-*- texinfo -*-\n\
@deftypefn {} {} end_try_catch\n\
Mark the end of an @code{try-catch} block.\n\
@seealso{try, catch}\n\
@end deftypefn"),

  pair_type ("end_unwind_protect",
  "-*- texinfo -*-\n\
@deftypefn {} {} end_unwind_protect\n\
Mark the end of an unwind_protect block.\n\
@seealso{unwind_protect}\n\
@end deftypefn"),

  pair_type ("endfor",
  "-*- texinfo -*-\n\
@deftypefn {} {} endfor\n\
Mark the end of a for loop.  See @code{for} for an example.\n\
@seealso{for}\n\
@end deftypefn"),

  pair_type ("endfunction",
  "-*- texinfo -*-\n\
@deftypefn {} {} endfunction\n\
Mark the end of a function.\n\
@seealso{function}\n\
@end deftypefn"),

  pair_type ("endif",
  "-*- texinfo -*-\n\
@deftypefn {} {} endif\n\
Mark the end of an if block.  See @code{if} for an example.\n\
@seealso{if}\n\
@end deftypefn"),

  pair_type ("endparfor",
  "-*- texinfo -*-\n\
@deftypefn {} {} endparfor\n\
Mark the end of a parfor loop.  See @code{parfor} for an example.\n\
@seealso{parfor}\n\
@end deftypefn"),

  pair_type ("endswitch",
  "-*- texinfo -*-\n\
@deftypefn {} {} endswitch\n\
Mark the end of a switch block.  See @code{switch} for an example.\n\
@seealso{switch}\n\
@end deftypefn"),

  pair_type ("endwhile",
  "-*- texinfo -*-\n\
@deftypefn {} {} endwhile\n\
Mark the end of a while loop.  See @code{while} for an example.\n\
@seealso{do, while}\n\
@end deftypefn"),

  pair_type ("for",
  "-*- texinfo -*-\n\
@deftypefn {} {} for @var{i} = @var{range}\n\
Begin a for loop.\n\
\n\
@example\n\
@group\n\
for i = 1:10\n\
  i\n\
endfor\n\
@end group\n\
@end example\n\
@seealso{do, parfor, while}\n\
@end deftypefn"),

  pair_type ("function",
  "-*- texinfo -*-\n\
@deftypefn  {} {} function @var{outputs} = function (@var{input}, @dots{})\n\
@deftypefnx {} {} function {} function (@var{input}, @dots{})\n\
@deftypefnx {} {} function @var{outputs} = function\n\
Begin a function body with @var{outputs} as results and @var{inputs} as\n\
parameters.\n\
@seealso{return}\n\
@end deftypefn"),

  pair_type ("global",
  "-*- texinfo -*-\n\
@deftypefn {} {} global @var{var}\n\
Declare variables to have global scope.\n\
\n\
@example\n\
@group\n\
global @var{x};\n\
if (isempty (@var{x}))\n\
  x = 1;\n\
endif\n\
@end group\n\
@end example\n\
@seealso{persistent}\n\
@end deftypefn"),

  pair_type ("if",
  "-*- texinfo -*-\n\
@deftypefn  {} {} if (@var{cond}) @dots{} endif\n\
@deftypefnx {} {} if (@var{cond}) @dots{} else @dots{} endif\n\
@deftypefnx {} {} if (@var{cond}) @dots{} elseif (@var{cond}) @dots{} endif\n\
@deftypefnx {} {} if (@var{cond}) @dots{} elseif (@var{cond}) @dots{} else @dots{} endif\n\
Begin an if block.\n\
\n\
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
@end deftypefn"),

  pair_type ("otherwise",
  "-*- texinfo -*-\n\
@deftypefn {} {} otherwise\n\
The default statement in a switch block (similar to else in an if block).\n\
@seealso{switch}\n\
@end deftypefn"),

  pair_type ("parfor",
  "-*- texinfo -*-\n\
@deftypefn  {} {} parfor @var{i} = @var{range}\n\
@deftypefnx {} {} parfor (@var{i} = @var{range}, @var{maxproc})\n\
Begin a for loop that may execute in parallel.\n\
\n\
@example\n\
@group\n\
parfor i = 1:10\n\
  i\n\
endparfor\n\
@end group\n\
@end example\n\
@seealso{for, do, while}\n\
@end deftypefn"),

  pair_type ("persistent",
  "-*- texinfo -*-\n\
@deftypefn {} {} persistent @var{var}\n\
Declare variables as persistent.  A variable that has been declared\n\
persistent within a function will retain its contents in memory between\n\
subsequent calls to the same function.  The difference between persistent\n\
variables and global variables is that persistent variables are local in\n\
scope to a particular function and are not visible elsewhere.\n\
@seealso{global}\n\
@end deftypefn"),

  pair_type ("return",
  "-*- texinfo -*-\n\
@deftypefn {} {} return\n\
Return from a function.\n\
@seealso{function}\n\
@end deftypefn"),

  pair_type ("static",
  "-*- texinfo -*-\n\
@deftypefn {} {} static\n\
This statement has been deprecated in favor of @code{persistent}.\n\
@seealso{persistent}\n\
@end deftypefn"),

  pair_type ("switch",
  "-*- texinfo -*-\n\
@deftypefn {} {} switch @var{statement}\n\
Begin a switch block.\n\
\n\
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
@end deftypefn"),

  pair_type ("try",
  "-*- texinfo -*-\n\
@deftypefn {} {} try\n\
Begin a try-catch block.\n\
\n\
If an error occurs within a try block, then the catch code will be run and\n\
execution will proceed after the catch block (though it is often\n\
recommended to use the lasterr function to re-throw the error after cleanup\n\
is completed).\n\
@seealso{catch, unwind_protect}\n\
@end deftypefn"),

  pair_type ("until",
  "-*- texinfo -*-\n\
@deftypefn {} {} until (@var{cond})\n\
End a do-until loop.  See @code{do} for an example.\n\
@seealso{do}\n\
@end deftypefn"),

  pair_type ("unwind_protect",
  "-*- texinfo -*-\n\
@deftypefn {} {} unwind_protect\n\
Begin an unwind_protect block.\n\
\n\
If an error occurs within the first part of an unwind_protect block\n\
the commands within the unwind_protect_cleanup block are executed before\n\
the error is thrown.  If an error is not thrown, then the\n\
unwind_protect_cleanup block is still executed (in other words, the\n\
unwind_protect_cleanup will be run with or without an error in the\n\
unwind_protect block).\n\
@seealso{unwind_protect_cleanup, try}\n\
@end deftypefn"),

  pair_type ("unwind_protect_cleanup",
  "-*- texinfo -*-\n\
@deftypefn {} {} unwind_protect_cleanup\n\
Begin the cleanup section of an unwind_protect block.\n\
@seealso{unwind_protect}\n\
@end deftypefn"),

  pair_type ("varargin",
  "-*- texinfo -*-\n\
@deftypefn {} {} varargin\n\
Pass an arbitrary number of arguments into a function.\n\
@seealso{varargout, nargin, isargout, nargout, nthargout}\n\
@end deftypefn"),

  pair_type ("varargout",
  "-*- texinfo -*-\n\
@deftypefn {} {} varargout\n\
Pass an arbitrary number of arguments out of a function.\n\
@seealso{varargin, nargin, isargout, nargout, nthargout}\n\
@end deftypefn"),

  pair_type ("while",
  "-*- texinfo -*-\n\
@deftypefn {} {} while\n\
Begin a while loop.\n\
\n\
@example\n\
@group\n\
i = 0;\n\
while (i < 10)\n\
  i++\n\
endwhile\n\
@end group\n\
@end example\n\
@seealso{do, endwhile, for, until}\n\
@end deftypefn"),
};

// Return a copy of the operator or keyword names.
static string_vector
names (const map_type& lst)
{
  string_vector retval (lst.size ());
  int j = 0;
  for (map_iter iter = lst.begin (); iter != lst.end (); iter++)
    retval[j++] = iter->first;
  return retval;
}

const static map_type operators_map (operators, operators + size (operators));
const static map_type keywords_map (keywords, keywords + size (keywords));
const static string_vector keyword_names = names (keywords_map);

// FIXME: It's not likely that this does the right thing now.

string_vector
make_name_list (void)
{
  const int key_len = keyword_names.numel ();

  const string_vector bif = symbol_table::built_in_function_names ();
  const int bif_len = bif.numel ();

  const string_vector cfl = symbol_table::cmdline_function_names ();
  const int cfl_len = cfl.numel ();

  const string_vector lcl = symbol_table::variable_names ();
  const int lcl_len = lcl.numel ();

  const string_vector ffl = load_path::fcn_names ();
  const int ffl_len = ffl.numel ();

  const string_vector afl = autoloaded_functions ();
  const int afl_len = afl.numel ();

  const int total_len
    = key_len + bif_len + cfl_len + lcl_len + ffl_len + afl_len;

  string_vector list (total_len);

  // Put all the symbols in one big list.

  int j = 0;
  int i = 0;
  for (i = 0; i < key_len; i++)
    list[j++] = keyword_names[i];

  for (i = 0; i < bif_len; i++)
    list[j++] = bif[i];

  for (i = 0; i < cfl_len; i++)
    list[j++] = cfl[i];

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
  // FIXME: this comparison should be case-insensitive
  const size_t p2 = t.find ("<html");

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

  h = get_help_from_file (nm, symbol_found, file);

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

  bool found;

  found = raw_help_from_symbol_table (nm, h, w, symbol_found);

  if (! found)
    {
      found = raw_help_from_file (nm, h, f, symbol_found);

      if (! found)
        {
          found = raw_help_from_map (nm, h, operators_map, symbol_found);

          if (! found)
            raw_help_from_map (nm, h, keywords_map, symbol_found);
        }
    }

  return h;
}

DEFUN (built_in_docstrings_file, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{val} =} built_in_docstrings_file ()
@deftypefnx {} {@var{old_val} =} built_in_docstrings_file (@var{new_val})
@deftypefnx {} {} built_in_docstrings_file (@var{new_val}, "local")
Query or set the internal variable that specifies the name of the
file containing docstrings for built-in Octave functions.

The default value is
@file{@var{octave-home}/share/octave/@var{version}/etc/built-in-docstrings},
in which @var{octave-home} is the root directory of the Octave installation,
and @var{version} is the Octave version number.  The default value may be
overridden by the environment variable
@w{@env{OCTAVE_BUILT_IN_DOCSTRINGS_FILE}}, or the command line argument
@option{--built-in-docstrings-file FNAME}.

Note: This variable is only used when Octave is initializing itself.
Modifying it during a running session of Octave will have no effect.
@end deftypefn */)
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (built_in_docstrings_file);
}

void
install_built_in_docstrings (void)
{
  std::string fname = Vbuilt_in_docstrings_file;

  std::ifstream file (fname.c_str (), std::ios::in | std::ios::binary);

  if (file)
    {
      // Ignore header;
      file.ignore (1000, 0x1d);

      if (file.gcount () == 1000)
        {
          // We use std::cerr here instead of calling Octave's warning
          // function because install_built_in_docstrings is called
          // before the interpreter is initialized, so warning messages
          // won't work properly.

          std::cerr << "warning: is builtin-docstrings file corrupted?"
                    << std::endl;
          return;
        }

      // FIXME: eliminate fixed buffer size.
      size_t bufsize = 100000;

      OCTAVE_LOCAL_BUFFER (char, buf, bufsize);

      while (! file.eof ())
        {
          file.getline (buf, bufsize, 0x1d);

          std::string tmp (buf);

          size_t pos = tmp.find ('\n');

          std::string fcn = tmp.substr (0, pos);

          octave_value ov = symbol_table::find_built_in_function (fcn);

          if (ov.is_defined ())
            {
              octave_function *fp = ov.function_value ();

              if (fp)
                {
                  tmp = tmp.substr (pos+1);

                  // Strip @c FILENAME which is part of current DOCSTRINGS
                  // syntax.  This may disappear if a specific format for
                  // docstring files is developed.
                  while (tmp.length () > 2 && tmp[0] == '@' && tmp[1] == 'c')
                    {
                      pos = tmp.find ('\n');
                      tmp = tmp.substr (pos+1);
                    }

                  fp->document (tmp);
                }
            }
        }
    }
  else
    {
      // See note above about using std::cerr instead of warning.

      std::cerr << "warning: docstring file '" << fname << "' not found"
                << std::endl;
    }

}

static void
do_get_help_text (const std::string& name, std::string& text,
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

DEFUN (get_help_text, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {[@var{text}, @var{format}] =} get_help_text (@var{name})
Return the raw help text of function @var{name}.

The raw help text is returned in @var{text} and the format in @var{format}
The format is a string which is one of @qcode{"texinfo"},
@qcode{"html"}, or @qcode{"plain text"}.
@seealso{get_help_text_from_file}
@end deftypefn */)
{
  if (args.length () != 1)
    print_usage ();

  const std::string name = args(0).xstring_value ("get_help_text: NAME must be a string");

  std::string text, format;

  do_get_help_text (name, text, format);

  return ovl (text, format);
}

static void
do_get_help_text_from_file (const std::string& fname, std::string& text,
                            std::string& format)
{
  bool symbol_found = false;

  std::string f;

  raw_help_from_file (fname, text, f, symbol_found);

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

DEFUN (get_help_text_from_file, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {[@var{text}, @var{format}] =} get_help_text_from_file (@var{fname})
Return the raw help text from the file @var{fname}.

The raw help text is returned in @var{text} and the format in @var{format}
The format is a string which is one of @qcode{"texinfo"},
@qcode{"html"}, or @qcode{"plain text"}.
@seealso{get_help_text}
@end deftypefn */)
{
  if (args.length () != 1)
    print_usage ();

  const std::string fname = args(0).xstring_value ("get_help_text_from_file: NAME must be a string");

  std::string text, format;

  do_get_help_text_from_file (fname, text, format);

  return ovl (text, format);
}

// Return a cell array of strings containing the names of all
// operators.

DEFUN (__operators__, , ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} __operators__ ()
Undocumented internal function.
@end deftypefn */)
{
  return ovl (Cell (names (operators_map)));
}

// Return a cell array of strings containing the names of all
// keywords.

DEFUN (__keywords__, , ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} __keywords__ ()
Undocumented internal function.
@end deftypefn */)
{
  return ovl (Cell (names (keywords_map)));
}

// Return a cell array of strings containing the names of all builtin
// functions.

DEFUN (__builtins__, , ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} __builtins__ ()
Undocumented internal function.
@end deftypefn */)
{
  const string_vector bif = symbol_table::built_in_function_names ();

  return ovl (Cell (bif));
}

DEFUN (localfunctions, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} localfunctions ()
Return a list of all local functions, i.e., subfunctions, within the current
file.

The return value is a column cell array of function handles to all local
functions accessible from the function from which @code{localfunctions} is
called.  Nested functions are @emph{not} included in the list.

If the call is from the command line, an anonymous function, or a script,
the return value is an empty cell array.

Compatibility Note: Subfunctions which contain nested functions are not
included in the list.  This is a known issue.
@end deftypefn */)
{
  if (args.length () != 0)
    print_usage ();

  Cell retval;

  // Find the main function we are in.
  octave_user_code *parent_fcn = octave_call_stack::debug_user_code ();

  if (! parent_fcn)
    return ovl (retval);

  // Find the subfunctions of this function.
  // FIXME: This includes all nested functions.
  //        Once handles of nested functions are implemented,
  //        we will need to exclude ones not in scope.
  const std::list<std::string> names = parent_fcn->subfunction_names ();
  const std::map<std::string, octave_value> h = parent_fcn->subfunctions ();

  size_t sz = names.size ();
  retval.resize (dim_vector (sz, 1));

  // loop over them.
  size_t i = 0;
  for (std::list<std::string>::const_iterator p = names.begin ();
       p != names.end (); p++)
    {
      std::map<std::string, octave_value>::const_iterator q = h.find (*p);
      if (q != h.end () &&
          ! q->second.user_function_value ()->is_nested_function ())
        retval(i++) = octave_value (new octave_fcn_handle (q->second, *p));
    }

  // remove pre-allocation for nested functions
  retval.resize (dim_vector (i, 1));

  return ovl (retval);
}

/*
%!test
%! f = tempname (".", "oct_");
%! fcn_name = f(3:end);
%! f = [f ".m"];
%! unwind_protect
%!   fid = fopen (f, "w+");
%!   fprintf (fid, "function z = %s\n z = localfunctions; end\n", fcn_name);
%!   fprintf (fid, "function z = b(x)\n z = x+1; end\n");
%!   fprintf (fid, "function z = c(x)\n z = 2*x; end\n");
%!   fclose (fid);
%!   d = eval (fcn_name);
%!   assert (size (d), [2, 1]);
%!   assert (d{1}(3), 4);
%!   assert (d{2}(3), 6);
%! unwind_protect_cleanup
%!   unlink (f);
%! end_unwind_protect
*/

static std::string
do_which (const std::string& name, std::string& type)
{
  std::string file;

  type = "";

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
                    {
                      file = fcn->src_file_name ();
                      type = "built-in function";
                    }
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

      file = octave::sys::env::make_absolute (file);
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
       doc: /* -*- texinfo -*-
@deftypefn {} {} __which__ (@var{name}, @dots{})
Undocumented internal function.
@end deftypefn */)
{
  string_vector argv = args.make_argv ();

  int nargin = argv.numel ();

  octave_map m (dim_vector (1, nargin));

  Cell names (1, nargin);
  Cell files (1, nargin);
  Cell types (1, nargin);

  for (int i = 0; i < nargin; i++)
    {
      std::string name = argv[i];

      std::string type;

      std::string file = do_which (name, type);

      names(i) = name;
      files(i) = file;
      types(i) = type;
    }

  m.assign ("name", names);
  m.assign ("file", files);
  m.assign ("type", types);

  return ovl (m);
}

// FIXME: Are we sure this function always does the right thing?
inline bool
file_is_in_dir (const std::string filename, const std::string dir)
{
  if (filename.find (dir) == 0)
    {
      const int dir_len = dir.size ();
      const int filename_len = filename.size ();
      const int max_allowed_seps = octave::sys::file_ops::is_dir_sep (dir[dir_len-1]) ? 0
                                                                         : 1;

      int num_seps = 0;
      for (int i = dir_len; i < filename_len; i++)
        if (octave::sys::file_ops::is_dir_sep (filename[i]))
          num_seps++;

      return (num_seps <= max_allowed_seps);
    }
  else
    return false;
}

// Return a cell array of strings containing the names of all
// functions available in DIRECTORY.  If no directory is given, search
// the current path.

DEFUN (__list_functions__, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{retval} =} __list_functions__ ()
@deftypefnx {} {@var{retval} =} __list_functions__ (@var{directory})
Undocumented internal function.
@end deftypefn */)
{
  octave_value retval;

  // Get list of functions
  string_vector ffl = load_path::fcn_names ();
  string_vector afl = autoloaded_functions ();

  if (args.length () == 0)
    retval = Cell (ffl.append (afl));
  else
    {
      std::string dir = args(0).xstring_value ("__list_functions__: DIRECTORY argument must be a string");

      string_vector fl = load_path::files (dir, true);

      // Return a sorted list with unique entries (in case of
      // .m and .oct versions of the same function in a given
      // directory, for example).
      fl.sort (true);

      retval = Cell (fl);
    }

  return retval;
}

DEFUN (doc_cache_file, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{val} =} doc_cache_file ()
@deftypefnx {} {@var{old_val} =} doc_cache_file (@var{new_val})
@deftypefnx {} {} doc_cache_file (@var{new_val}, "local")
Query or set the internal variable that specifies the name of the
Octave documentation cache file.

A cache file significantly improves the performance of the @code{lookfor}
command.  The default value is
@file{@var{octave-home}/share/octave/@var{version}/etc/doc-cache},
in which @var{octave-home} is the root directory of the Octave installation,
and @var{version} is the Octave version number.
The default value may be overridden by the environment variable
@w{@env{OCTAVE_DOC_CACHE_FILE}}, or the command line argument
@option{--doc-cache-file FNAME}.

When called from inside a function with the @qcode{"local"} option, the
variable is changed locally for the function and any subroutines it calls.
The original variable value is restored when exiting the function.
@seealso{doc_cache_create, lookfor, info_program, doc, help, makeinfo_program}
@seealso{lookfor}
@end deftypefn */)
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (doc_cache_file);
}

DEFUN (texi_macros_file, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{val} =} texi_macros_file ()
@deftypefnx {} {@var{old_val} =} texi_macros_file (@var{new_val})
@deftypefnx {} {} texi_macros_file (@var{new_val}, "local")
Query or set the internal variable that specifies the name of the
file containing Texinfo macros that are prepended to documentation strings
before they are passed to makeinfo.

The default value is
@file{@var{octave-home}/share/octave/@var{version}/etc/macros.texi},
in which @var{octave-home} is the root directory of the Octave installation,
and @var{version} is the Octave version number.
The default value may be overridden by the environment variable
@w{@env{OCTAVE_TEXI_MACROS_FILE}}, or the command line argument
@option{--texi-macros-file FNAME}.

When called from inside a function with the @qcode{"local"} option, the
variable is changed locally for the function and any subroutines it calls.
The original variable value is restored when exiting the function.
@seealso{makeinfo_program}
@end deftypefn */)
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (texi_macros_file);
}

DEFUN (info_file, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{val} =} info_file ()
@deftypefnx {} {@var{old_val} =} info_file (@var{new_val})
@deftypefnx {} {} info_file (@var{new_val}, "local")
Query or set the internal variable that specifies the name of the
Octave info file.

The default value is
@file{@var{octave-home}/info/octave.info}, in
which @var{octave-home} is the root directory of the Octave installation.
The default value may be overridden by the environment variable
@w{@env{OCTAVE_INFO_FILE}}, or the command line argument
@option{--info-file FNAME}.

When called from inside a function with the @qcode{"local"} option, the
variable is changed locally for the function and any subroutines it calls.
The original variable value is restored when exiting the function.
@seealso{info_program, doc, help, makeinfo_program}
@end deftypefn */)
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (info_file);
}

DEFUN (info_program, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{val} =} info_program ()
@deftypefnx {} {@var{old_val} =} info_program (@var{new_val})
@deftypefnx {} {} info_program (@var{new_val}, "local")
Query or set the internal variable that specifies the name of the
info program to run.

The default value is
@file{@var{octave-home}/libexec/octave/@var{version}/exec/@var{arch}/info}
in which @var{octave-home} is the root directory of the Octave installation,
@var{version} is the Octave version number, and @var{arch} is the system
type (for example, @code{i686-pc-linux-gnu}).  The default value may be
overridden by the environment variable
@w{@env{OCTAVE_INFO_PROGRAM}}, or the command line argument
@option{--info-program NAME}.

When called from inside a function with the @qcode{"local"} option, the
variable is changed locally for the function and any subroutines it calls.
The original variable value is restored when exiting the function.
@seealso{info_file, doc, help, makeinfo_program}
@end deftypefn */)
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (info_program);
}

DEFUN (makeinfo_program, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{val} =} makeinfo_program ()
@deftypefnx {} {@var{old_val} =} makeinfo_program (@var{new_val})
@deftypefnx {} {} makeinfo_program (@var{new_val}, "local")
Query or set the internal variable that specifies the name of the
program that Octave runs to format help text containing
Texinfo markup commands.

The default value is @code{makeinfo}.

When called from inside a function with the @qcode{"local"} option, the
variable is changed locally for the function and any subroutines it calls.
The original variable value is restored when exiting the function.
@seealso{texi_macros_file, info_file, info_program, doc, help}
@end deftypefn */)
{
  return SET_NONEMPTY_INTERNAL_STRING_VARIABLE (makeinfo_program);
}

DEFUN (suppress_verbose_help_message, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{val} =} suppress_verbose_help_message ()
@deftypefnx {} {@var{old_val} =} suppress_verbose_help_message (@var{new_val})
@deftypefnx {} {} suppress_verbose_help_message (@var{new_val}, "local")
Query or set the internal variable that controls whether Octave
will add additional help information to the end of the output from
the @code{help} command and usage messages for built-in commands.

When called from inside a function with the @qcode{"local"} option, the
variable is changed locally for the function and any subroutines it calls.
The original variable value is restored when exiting the function.
@end deftypefn */)
{
  return SET_INTERNAL_VARIABLE (suppress_verbose_help_message);
}
