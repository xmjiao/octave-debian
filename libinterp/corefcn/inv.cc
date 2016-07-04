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

#include "defun.h"
#include "error.h"
#include "errwarn.h"
#include "ovl.h"
#include "ops.h"
#include "ov-re-diag.h"
#include "ov-cx-diag.h"
#include "ov-flt-re-diag.h"
#include "ov-flt-cx-diag.h"
#include "ov-perm.h"
#include "utils.h"

DEFUN (inv, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{x} =} inv (@var{A})
@deftypefnx {} {[@var{x}, @var{rcond}] =} inv (@var{A})
Compute the inverse of the square matrix @var{A}.

Return an estimate of the reciprocal condition number if requested,
otherwise warn of an ill-conditioned matrix if the reciprocal condition
number is small.

In general it is best to avoid calculating the inverse of a matrix directly.
For example, it is both faster and more accurate to solve systems of
equations (@var{A}*@math{x} = @math{b}) with
@code{@var{y} = @var{A} \ @math{b}}, rather than
@code{@var{y} = inv (@var{A}) * @math{b}}.

If called with a sparse matrix, then in general @var{x} will be a full
matrix requiring significantly more storage.  Avoid forming the inverse of a
sparse matrix if possible.
@seealso{ldivide, rdivide}
@end deftypefn */)
{
  if (args.length () != 1)
    print_usage ();

  octave_value arg = args(0);

  octave_idx_type nr = arg.rows ();
  octave_idx_type nc = arg.columns ();

  int arg_is_empty = empty_arg ("inverse", nr, nc);

  if (arg_is_empty < 0)
    return ovl ();
  else if (arg_is_empty > 0)
    return ovl (Matrix ());

  if (nr != nc)
    err_square_matrix_required ("inverse", "A");

  octave_value result;
  octave_idx_type info;
  double rcond = 0.0;
  float frcond = 0.0;
  bool isfloat = arg.is_single_type ();

  if (arg.is_diag_matrix ())
    {
      rcond = 1.0;
      frcond = 1.0f;
      if (arg.is_complex_type ())
        {
          if (isfloat)
            {
              result = arg.float_complex_diag_matrix_value ().inverse (info);
              if (nargout > 1)
                frcond = arg.float_complex_diag_matrix_value ().rcond ();
            }
          else
            {
              result = arg.complex_diag_matrix_value ().inverse (info);
              if (nargout > 1)
                rcond = arg.complex_diag_matrix_value ().rcond ();
            }
        }
      else
        {
          if (isfloat)
            {
              result = arg.float_diag_matrix_value ().inverse (info);
              if (nargout > 1)
                frcond = arg.float_diag_matrix_value ().rcond ();
            }
          else
            {
              result = arg.diag_matrix_value ().inverse (info);
              if (nargout > 1)
                rcond = arg.diag_matrix_value ().rcond ();
            }
        }
    }
  else if (arg.is_perm_matrix ())
    {
      rcond = 1.0;
      info = 0;
      result = arg.perm_matrix_value ().inverse ();
    }
  else if (isfloat)
    {
      if (arg.is_real_type ())
        {
          FloatMatrix m = arg.float_matrix_value ();

          MatrixType mattyp = args(0).matrix_type ();
          result = m.inverse (mattyp, info, frcond, 1);
          args(0).matrix_type (mattyp);
        }
      else if (arg.is_complex_type ())
        {
          FloatComplexMatrix m = arg.float_complex_matrix_value ();

          MatrixType mattyp = args(0).matrix_type ();
          result = m.inverse (mattyp, info, frcond, 1);
          args(0).matrix_type (mattyp);
        }
    }
  else
    {
      if (arg.is_real_type ())
        {
          if (arg.is_sparse_type ())
            {
              SparseMatrix m = arg.sparse_matrix_value ();

              MatrixType mattyp = args(0).matrix_type ();
              result = m.inverse (mattyp, info, rcond, 1);
              args(0).matrix_type (mattyp);
            }
          else
            {
              Matrix m = arg.matrix_value ();

              MatrixType mattyp = args(0).matrix_type ();
              result = m.inverse (mattyp, info, rcond, 1);
              args(0).matrix_type (mattyp);
            }
        }
      else if (arg.is_complex_type ())
        {
          if (arg.is_sparse_type ())
            {
              SparseComplexMatrix m = arg.sparse_complex_matrix_value ();

              MatrixType mattyp = args(0).matrix_type ();
              result = m.inverse (mattyp, info, rcond, 1);
              args(0).matrix_type (mattyp);
            }
          else
            {
              ComplexMatrix m = arg.complex_matrix_value ();

              MatrixType mattyp = args(0).matrix_type ();
              result = m.inverse (mattyp, info, rcond, 1);
              args(0).matrix_type (mattyp);
            }
        }
      else
        err_wrong_type_arg ("inv", arg);
    }

  octave_value_list retval (nargout > 1 ? 2 : 1);

  retval(0) = result;
  if (nargout > 1)
    retval(1) = isfloat ? octave_value (frcond) : octave_value (rcond);

  bool rcond_plus_one_eq_one = false;

  if (isfloat)
    {
      volatile float xrcond = frcond;
      rcond_plus_one_eq_one = xrcond + 1.0F == 1.0F;
    }
  else
    {
      volatile double xrcond = rcond;
      rcond_plus_one_eq_one = xrcond + 1.0 == 1.0;
    }

  if (nargout < 2 && (info == -1 || rcond_plus_one_eq_one))
    warn_singular_matrix (isfloat ? frcond : rcond);

  return retval;
}

/*
%!assert (inv ([1, 2; 3, 4]), [-2, 1; 1.5, -0.5], sqrt (eps))
%!assert (inv (single ([1, 2; 3, 4])), single ([-2, 1; 1.5, -0.5]), sqrt (eps ("single")))

%!error inv ()
%!error inv ([1, 2; 3, 4], 2)
%!error <must be a square matrix> inv ([1, 2; 3, 4; 5, 6])

%!test
%! [xinv, rcond] = inv (single ([1,2;3,4]));
%! assert (isa (xinv, 'single'));
%! assert (isa (rcond, 'single'));

%!test
%! [xinv, rcond] = inv ([1,2;3,4]);
%! assert (isa (xinv, 'double'));
%! assert (isa (rcond, 'double'));
*/

// FIXME: this should really be done with an alias, but
// alias_builtin() won't do the right thing if we are actually using
// dynamic linking.

DEFUN (inverse, args, nargout,
       doc: /* -*- texinfo -*-
@deftypefn  {} {@var{x} =} inverse (@var{A})
@deftypefnx {} {[@var{x}, @var{rcond}] =} inverse (@var{A})
Compute the inverse of the square matrix @var{A}.

This is an alias for @code{inv}.
@seealso{inv}
@end deftypefn */)
{
  return Finv (args, nargout);
}
