/*

Copyright (C) 2008-2015 David Bateman

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

#include <algorithm>

#include "defun.h"
#include "error.h"
#include "errwarn.h"
#include "ovl.h"
#include "utils.h"

DEFUN (hex2num, args, ,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{n} =} hex2num (@var{s})
@deftypefnx {} {@var{n} =} hex2num (@var{s}, @var{class})
Typecast the 16 character hexadecimal character string to an IEEE 754
double precision number.

If fewer than 16 characters are given the strings are right padded with
@qcode{'0'} characters.

Given a string matrix, @code{hex2num} treats each row as a separate number.

@example
@group
hex2num (["4005bf0a8b145769"; "4024000000000000"])
   @result{} [2.7183; 10.000]
@end group
@end example

The optional argument @var{class} can be passed as the string
@qcode{"single"} to specify that the given string should be interpreted as
a single precision number.  In this case, @var{s} should be an 8 character
hexadecimal string.  For example:

@example
@group
hex2num (["402df854"; "41200000"], "single")
   @result{} [2.7183; 10.000]
@end group
@end example
@seealso{num2hex, hex2dec, dec2hex}
@end deftypefn */)
{
  int nargin = args.length ();

  if (nargin < 1 || nargin > 2)
    print_usage ();

  if (nargin == 2 && ! args(1).is_string ())
    error ("hex2num: CLASS must be a string");

  const charMatrix cmat = args(0).char_matrix_value ();
  std::string prec = (nargin == 2) ? args(1).string_value () : "double";
  bool is_single = (prec == "single");
  octave_idx_type nchars = (is_single) ? 8 : 16;

  if (cmat.columns () > nchars)
    error ("hex2num: S must be no more than %d characters", nchars);
  else if (prec != "double" && prec != "single")
    error ("hex2num: CLASS must be either \"double\" or \"single\"");

  octave_value retval;
  octave_idx_type nr = cmat.rows ();
  octave_idx_type nc = cmat.columns ();

  if (is_single)
    {
      FloatColumnVector m (nr);

      for (octave_idx_type i = 0; i < nr; i++)
        {
          union
          {
            uint32_t ival;
            float dval;
          } num;

          num.ival = 0;

          for (octave_idx_type j = 0; j < nc; j++)
            {
              unsigned char ch = cmat.elem (i, j);

              if (! isxdigit (ch))
                error ("hex2num: illegal character found in string S");

              num.ival <<= 4;
              if (ch >= 'a')
                num.ival += static_cast<uint32_t> (ch - 'a' + 10);
              else if (ch >= 'A')
                num.ival += static_cast<uint32_t> (ch - 'A' + 10);
              else
                num.ival += static_cast<uint32_t> (ch - '0');
            }

          if (nc < nchars)
            num.ival <<= (nchars - nc) * 4;

          m(i) = num.dval;
        }

      retval = m;
    }
  else
    {
      ColumnVector m (nr);

      for (octave_idx_type i = 0; i < nr; i++)
        {
          union
          {
            uint64_t ival;
            double dval;
          } num;

          num.ival = 0;

          for (octave_idx_type j = 0; j < nc; j++)
            {
              unsigned char ch = cmat.elem (i, j);

              if (! isxdigit (ch))
                error ("hex2num: illegal character found in string S");

              num.ival <<= 4;
              if (ch >= 'a')
                num.ival += static_cast<uint64_t> (ch - 'a' + 10);
              else if (ch >= 'A')
                num.ival += static_cast<uint64_t> (ch - 'A' + 10);
              else
                num.ival += static_cast<uint64_t> (ch - '0');
            }

          if (nc < nchars)
            num.ival <<= (nchars - nc) * 4;

          m(i) = num.dval;
        }

      retval = m;
    }

  return retval;
}

/*
%!assert (hex2num (["c00";"bff";"000";"3ff";"400"]), [-2:2]')
%!assert (hex2num (["c00";"bf8";"000";"3f8";"400"], "single"), single([-2:2])')
*/

DEFUN (num2hex, args, ,
       doc: /* -*- texinfo -*-
@deftypefn {} {@var{s} =} num2hex (@var{n})
Typecast a double or single precision number or vector to a 8 or 16
character hexadecimal string of the IEEE 754 representation of the number.

For example:

@example
@group
num2hex ([-1, 1, e, Inf])
@result{} "bff0000000000000
    3ff0000000000000
    4005bf0a8b145769
    7ff0000000000000"
@end group
@end example

If the argument @var{n} is a single precision number or vector, the returned
string has a length of 8.  For example:

@example
@group
num2hex (single ([-1, 1, e, Inf]))
@result{} "bf800000
    3f800000
    402df854
    7f800000"
@end group
@end example
@seealso{hex2num, hex2dec, dec2hex}
@end deftypefn */)
{
  if (args.length () != 1)
    print_usage ();

  if (args(0).is_complex_type ())
    error ("num2hex: N must be real");

  octave_value retval;

  if (args(0).is_single_type ())
    {
      const FloatColumnVector v (args(0).float_vector_value ());

      octave_idx_type nchars = 8;
      octave_idx_type nr = v.numel ();
      charMatrix m (nr, nchars);
      const float *pv = v.fortran_vec ();

      for (octave_idx_type i = 0; i < nr; i++)
        {
          union
          {
            uint32_t ival;
            float dval;
          } num;

          num.dval = *pv++;

          for (octave_idx_type j = 0; j < nchars; j++)
            {
              unsigned char ch =
                static_cast<char>(num.ival >> ((nchars - 1 - j) * 4) & 0xF);
              if (ch >= 10)
                ch += 'a' - 10;
              else
                ch += '0';

              m.elem (i, j) = ch;
            }
        }

      retval = m;
    }
  else
    {
      const ColumnVector v (args(0).vector_value ());

      octave_idx_type nchars = 16;
      octave_idx_type nr = v.numel ();
      charMatrix m (nr, nchars);
      const double *pv = v.fortran_vec ();

      for (octave_idx_type i = 0; i < nr; i++)
        {
          union
          {
            uint64_t ival;
            double dval;
          } num;

          num.dval = *pv++;

          for (octave_idx_type j = 0; j < nchars; j++)
            {
              unsigned char ch =
                static_cast<char>(num.ival >> ((nchars - 1 - j) * 4) & 0xF);
              if (ch >= 10)
                ch += 'a' - 10;
              else
                ch += '0';

              m.elem (i, j) = ch;
            }
        }

      retval = m;
    }

  return retval;
}

/*
%!assert (num2hex (-2:2), ["c000000000000000";"bff0000000000000";"0000000000000000";"3ff0000000000000";"4000000000000000"])
%!assert (num2hex (single (-2:2)), ["c0000000";"bf800000";"00000000";"3f800000";"40000000"])

%!error num2hex ()
%!error num2hex (1,2)
%!error num2hex (1j)
*/
