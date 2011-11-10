/*

Copyright (C) 1996, 1997, 1999, 2000, 2001, 2002, 2004, 2005, 2006,
              2007, 2008, 2009 John W. Eaton

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

#include "defun-dld.h"
#include "error.h"
#include "gripes.h"
#include "oct-obj.h"
#include "ops.h"
#include "ov-re-diag.h"
#include "ov-cx-diag.h"
#include "ov-flt-re-diag.h"
#include "ov-flt-cx-diag.h"
#include "ov-perm.h"
#include "utils.h"

DEFUN_DLD (inv, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {[@var{x}, @var{rcond}] =} inv (@var{a})\n\
@deftypefnx {Loadable Function} {[@var{x}, @var{rcond}] =} inverse (@var{a})\n\
Compute the inverse of the square matrix @var{a}.  Return an estimate\n\
of the reciprocal condition number if requested, otherwise warn of an\n\
ill-conditioned matrix if the reciprocal condition number is small.\n\
\n\
If called with a sparse matrix, then in general @var{x} will be a full\n\
matrix, and so if possible forming the inverse of a sparse matrix should\n\
be avoided.  It is significantly more accurate and faster to do\n\
@code{@var{y} = @var{a} \\ @var{b}}, rather than\n\
@code{@var{y} = inv (@var{a}) * @var{b}}.\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin != 1)
    {
      print_usage ();
      return retval;
    }

  octave_value arg = args(0);

  octave_idx_type nr = arg.rows ();
  octave_idx_type nc = arg.columns ();

  int arg_is_empty = empty_arg ("inverse", nr, nc);

  if (arg_is_empty < 0)
    return retval;
  else if (arg_is_empty > 0)
    return octave_value (Matrix ());

  if (nr != nc)
    {
      gripe_square_matrix_required ("inverse");
      return retval;
    }

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
	  if (! error_state)
	    {
	      MatrixType mattyp = args(0).matrix_type ();
	      result = m.inverse (mattyp, info, frcond, 1);
	      args(0).matrix_type (mattyp);
	    }
	}
      else if (arg.is_complex_type ())
	{
	  FloatComplexMatrix m = arg.float_complex_matrix_value ();
	  if (! error_state)
	    {
	      MatrixType mattyp = args(0).matrix_type ();
	      result = m.inverse (mattyp, info, frcond, 1);
	      args(0).matrix_type (mattyp);
	    }
	}
    }
  else
    {
      if (arg.is_real_type ())
	{
	  if (arg.is_sparse_type ())
	    {
	      SparseMatrix m = arg.sparse_matrix_value ();
	      if (! error_state)
		{
		  MatrixType mattyp = args(0).matrix_type ();
		  result = m.inverse (mattyp, info, rcond, 1);
		  args(0).matrix_type (mattyp);
		}
	    }
	  else
	    {
	      Matrix m = arg.matrix_value ();
	      if (! error_state)
		{
		  MatrixType mattyp = args(0).matrix_type ();
		  result = m.inverse (mattyp, info, rcond, 1);
		  args(0).matrix_type (mattyp);
		}
	    }
	}
      else if (arg.is_complex_type ())
	{
	  if (arg.is_sparse_type ())
	    {
	      SparseComplexMatrix m = arg.sparse_complex_matrix_value ();
	      if (! error_state)
		{
		  MatrixType mattyp = args(0).matrix_type ();
		  result = m.inverse (mattyp, info, rcond, 1);
		  args(0).matrix_type (mattyp);
		}
	    }
	  else
	    {
	      ComplexMatrix m = arg.complex_matrix_value ();
	      if (! error_state)
		{
		  MatrixType mattyp = args(0).matrix_type ();
		  result = m.inverse (mattyp, info, rcond, 1);
		  args(0).matrix_type (mattyp);
		}
	    }
	}
      else
	gripe_wrong_type_arg ("inv", arg);
    }

  if (! error_state)
    {
      if (nargout > 1)
	retval(1) = isfloat ? octave_value (frcond) : octave_value (rcond);

      retval(0) = result;

      volatile double xrcond = rcond;
      xrcond += 1.0;
      if (nargout < 2 && (info == -1 || xrcond == 1.0))
	warning ("inverse: matrix singular to machine precision, rcond = %g", 
		 rcond);
    }

  return retval;
}

/*

%!assert(inv ([1, 2; 3, 4]), [-2, 1; 1.5, -0.5], sqrt (eps))
%!assert(inv (single([1, 2; 3, 4])), single([-2, 1; 1.5, -0.5]), sqrt (eps ('single')))

%!error <Invalid call to inv.*> inv ();
%!error <Invalid call to inv.*> inv ([1, 2; 3, 4], 2);
%!error inv ([1, 2; 3, 4; 5, 6]);

 */

// FIXME -- this should really be done with an alias, but
// alias_builtin() won't do the right thing if we are actually using
// dynamic linking.

DEFUN_DLD (inverse, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {} inverse (@var{a})\n\
See inv.\n\
@end deftypefn")
{
  return Finv (args, nargout);
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/