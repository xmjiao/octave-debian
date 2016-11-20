/*

Copyright (C) 2001-2016 John W. Eaton and Paul Kienzle

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

#include <list>
#include <map>
#include <string>

#include "Cell.h"
#include "oct-map.h"
#include "defun.h"
#include "ov.h"
#include "ov-fcn.h"
#include "ov-typeinfo.h"
#include "pager.h"
#include "parse.h"
#include "symtab.h"
#include "variables.h"

DEFUN (__dispatch__, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn {} {} __dispatch__ ()
Undocumented internal function.
@end deftypefn */)
{
  int nargin = args.length ();

  if (nargin < 1 || nargin > 3)
    print_usage ();

  std::string f, r, t;

  f = args(0).xstring_value ("__dispatch__: first argument must be a function name");

  if (nargin > 1)
    r = args(1).xstring_value ("__dispatch__: second argument must be a function name");

  if (nargin > 2)
    t = args(2).xstring_value ("__dispatch__: third argument must be a type name");

  octave_value retval;

  if (nargin == 1)
    {
      if (nargout > 0)
        {
          symbol_table::fcn_info::dispatch_map_type dm
            = symbol_table::get_dispatch (f);

          size_t len = dm.size ();

          Cell type_field (len, 1);
          Cell name_field (len, 1);

          symbol_table::fcn_info::dispatch_map_type::const_iterator p
            = dm.begin ();

          for (size_t i = 0; i < len; i++)
            {
              type_field(i) = p->first;
              name_field(i) = p->second;

              p++;
            }

          octave_scalar_map m;

          m.assign ("type", type_field);
          m.assign ("name", name_field);

          retval = m;
        }
      else
        symbol_table::print_dispatch (octave_stdout, f);
    }
  else if (nargin == 2)
    {
      t = r;
      symbol_table::clear_dispatch (f, t);
    }
  else
    symbol_table::add_dispatch (f, t, r);

  return retval;
}

/*
## No test needed for internal helper function.
%!assert (1)
*/

