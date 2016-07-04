/*

Copyright (C) 1996-2015 John W. Eaton

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

#include "hess.h"

#include "defun.h"
#include "error.h"
#include "errwarn.h"
#include "ovl.h"
#include "utils.h"

DEFUN (hess, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{H} =} hess (@var{A})
@deftypefnx {} {[@var{P}, @var{H}] =} hess (@var{A})
@cindex Hessenberg decomposition
Compute the Hessenberg decomposition of the matrix @var{A}.

The Hessenberg decomposition is
@tex
$$
A = PHP^T
$$
where $P$ is a square unitary matrix ($P^TP = I$), and $H$
is upper Hessenberg ($H_{i,j} = 0, \forall i > j+1$).
@end tex
@ifnottex
@code{@var{P} * @var{H} * @var{P}' = @var{A}} where @var{P} is a square
unitary matrix (@code{@var{P}' * @var{P} = I}, using complex-conjugate
transposition) and @var{H} is upper Hessenberg
(@code{@var{H}(i, j) = 0 forall i > j+1)}.
@end ifnottex

The Hessenberg decomposition is usually used as the first step in an
eigenvalue computation, but has other applications as well
(see @nospell{Golub, Nash, and Van Loan},
IEEE Transactions on Automatic Control, 1979).
@seealso{eig, chol, lu, qr, qz, schur, svd}
@end deftypefn */)
{
  if (args.length () != 1)
    print_usage ();

  octave_value arg = args(0);

  octave_idx_type nr = arg.rows ();
  octave_idx_type nc = arg.columns ();

  int arg_is_empty = empty_arg ("hess", nr, nc);

  if (arg_is_empty < 0)
    return ovl ();
  else if (arg_is_empty > 0)
    return octave_value_list (2, Matrix ());

  if (nr != nc)
    err_square_matrix_required ("hess", "A");

  octave_value_list retval;

  if (arg.is_single_type ())
    {
      if (arg.is_real_type ())
        {
          FloatMatrix tmp = arg.float_matrix_value ();

          hess<FloatMatrix> result (tmp);

          if (nargout <= 1)
            retval = ovl (result.hess_matrix ());
          else
            retval = ovl (result.unitary_hess_matrix (),
                          result.hess_matrix ());
        }
      else if (arg.is_complex_type ())
        {
          FloatComplexMatrix ctmp = arg.float_complex_matrix_value ();

          hess<FloatComplexMatrix> result (ctmp);

          if (nargout <= 1)
            retval = ovl (result.hess_matrix ());
          else
            retval = ovl (result.unitary_hess_matrix (),
                          result.hess_matrix ());
        }
    }
  else
    {
      if (arg.is_real_type ())
        {
          Matrix tmp = arg.matrix_value ();

          hess<Matrix> result (tmp);

          if (nargout <= 1)
            retval = ovl (result.hess_matrix ());
          else
            retval = ovl (result.unitary_hess_matrix (),
                          result.hess_matrix ());
        }
      else if (arg.is_complex_type ())
        {
          ComplexMatrix ctmp = arg.complex_matrix_value ();

          hess<ComplexMatrix> result (ctmp);

          if (nargout <= 1)
            retval = ovl (result.hess_matrix ());
          else
            retval = ovl (result.unitary_hess_matrix (),
                          result.hess_matrix ());
        }
      else
        err_wrong_type_arg ("hess", arg);
    }

  return retval;
}

/*
%!test
%! a = [1, 2, 3; 5, 4, 6; 8, 7, 9];
%! [p, h] = hess (a);
%! assert (p * h * p', a, sqrt (eps));

%!test
%! a = single ([1, 2, 3; 5, 4, 6; 8, 7, 9]);
%! [p, h] = hess (a);
%! assert (p * h * p', a, sqrt (eps ("single")));

%!error hess ()
%!error hess ([1, 2; 3, 4], 2)
%!error <must be a square matrix> hess ([1, 2; 3, 4; 5, 6])
*/
