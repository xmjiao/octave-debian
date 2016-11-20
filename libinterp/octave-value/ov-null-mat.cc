/*

Copyright (C) 2008-2016 Jaroslav Hajek

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

#include "ov-null-mat.h"
#include "ops.h"
#include "defun.h"

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_null_matrix, "null_matrix",
                                     "double");

const octave_value octave_null_matrix::instance (new octave_null_matrix ());

static octave_base_value *
default_null_matrix_numeric_conversion_function (const octave_base_value& a)
{
  // The cast is not necessary?
  // const octave_null_matrix& v = dynamic_cast<const octave_null_matrix&> (a);

  return a.empty_clone ();
}

octave_base_value::type_conv_info
octave_null_matrix::numeric_conversion_function (void) const
{
  return octave_base_value::type_conv_info
           (default_null_matrix_numeric_conversion_function,
            octave_matrix::static_type_id ());
}

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_null_str, "null_string", "char");

const octave_value octave_null_str::instance (new octave_null_str ());

static octave_base_value *
default_null_str_numeric_conversion_function (const octave_base_value& a)
{
  // The cast is not necessary?
  // const octave_null_str& v = dynamic_cast<const octave_null_str&> (a);

  return a.empty_clone ();
}

octave_base_value::type_conv_info
octave_null_str::numeric_conversion_function (void) const
{
  return octave_base_value::type_conv_info
          (default_null_str_numeric_conversion_function,
           octave_char_matrix_str::static_type_id ());
}

DEFINE_OV_TYPEID_FUNCTIONS_AND_DATA (octave_null_sq_str, "null_sq_string",
                                     "char");

const octave_value octave_null_sq_str::instance (new octave_null_sq_str ());

static octave_base_value *
default_null_sq_str_numeric_conversion_function (const octave_base_value& a)
{
  // The cast is not necessary?
  // const octave_null_sq_str& v = dynamic_cast<const octave_null_sq_str&> (a);

  return a.empty_clone ();
}

octave_base_value::type_conv_info
octave_null_sq_str::numeric_conversion_function (void) const
{
  return octave_base_value::type_conv_info
           (default_null_sq_str_numeric_conversion_function,
            octave_char_matrix_sq_str::static_type_id ());
}

DEFUN (isnull, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {} isnull (@var{x})
Return true if @var{x} is a special null matrix, string, or single quoted
string.

Indexed assignment with such a value on the right-hand side should delete
array elements.  This function should be used when overloading indexed
assignment for user-defined classes instead of @code{isempty}, to
distinguish the cases:

@table @asis
@item @code{A(I) = []}
This should delete elements if @code{I} is nonempty.

@item @code{X = []; A(I) = X}
This should give an error if @code{I} is nonempty.
@end table
@seealso{isempty, isindex}
@end deftypefn */)
{
  if (args.length () != 1)
    print_usage ();

  return ovl (args(0).is_null_value ());
}

/*
%!assert (isnull ([]), true)
%!assert (isnull ([1]), false)
%!assert (isnull (zeros (0,3)), false)
%!assert (isnull (""), true)
%!assert (isnull ("A"), false)
%!assert (isnull (''), true)
%!assert (isnull ('A'), false)
%!test
%! x = [];
%! assert (isnull (x), false);
*/

