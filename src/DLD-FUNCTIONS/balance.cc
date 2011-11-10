/*

Copyright (C) 1996, 1997, 1998, 1999, 2000, 2002, 2003, 2005, 2006,
              2007 John W. Eaton
Copyright (C) 2008, 2009 Jaroslav Hajek

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

// Author: A. S. Hodel <scotte@eng.auburn.edu>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <string>

#include "CmplxAEPBAL.h"
#include "fCmplxAEPBAL.h"
#include "dbleAEPBAL.h"
#include "floatAEPBAL.h"
#include "CmplxGEPBAL.h"
#include "fCmplxGEPBAL.h"
#include "dbleGEPBAL.h"
#include "floatGEPBAL.h"
#include "quit.h"

#include "defun-dld.h"
#include "error.h"
#include "f77-fcn.h"
#include "gripes.h"
#include "oct-obj.h"
#include "utils.h"

DEFUN_DLD (balance, args, nargout,
  "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{aa} =} balance (@var{a}, @var{opt})\n\
@deftypefnx {Loadable Function} {[@var{dd}, @var{aa}] =} balance (@var{a}, @var{opt})\n\
@deftypefnx {Loadable Function} {[@var{d}, @var{p}, @var{aa}] =} balance (@var{a}, @var{opt})\n\
@deftypefnx {Loadable Function} {[@var{cc}, @var{dd}, @var{aa}, @var{bb}] =} balance (@var{a}, @var{b}, @var{opt})\n\
\n\
Compute @code{aa = dd \\ a * dd} in which @code{aa} is a matrix whose\n\
row and column norms are roughly equal in magnitude, and\n\
@code{dd} = @code{p * d}, in which @code{p} is a permutation\n\
matrix and @code{d} is a diagonal matrix of powers of two.  This allows\n\
the equilibration to be computed without roundoff.  Results of\n\
eigenvalue calculation are typically improved by balancing first.\n\
\n\
If two output values are requested, @code{balance} returns \n\
the diagonal @code{d} and the permutation @code{p} separately as vectors.  \n\
In this case, @code{dd = eye(n)(:,p) * diag (d)}, where @code{n} is the matrix \n\
size.  \n\
\n\
If four output values are requested, compute @code{aa = cc*a*dd} and\n\
@code{bb = cc*b*dd)}, in which @code{aa} and @code{bb} have non-zero\n\
elements of approximately the same magnitude and @code{cc} and @code{dd}\n\
are permuted diagonal matrices as in @code{dd} for the algebraic\n\
eigenvalue problem.\n\
\n\
The eigenvalue balancing option @code{opt} may be one of:\n\
\n\
@table @asis\n\
@item @code{\"noperm\"}, @code{\"S\"}\n\
Scale only; do not permute.\n\
\n\
@item @code{\"noscal\"}, @code{\"P\"}\n\
Permute only; do not scale.\n\
@end table\n\
\n\
Algebraic eigenvalue balancing uses standard @sc{lapack} routines.\n\
\n\
Generalized eigenvalue problem balancing uses Ward's algorithm\n\
(SIAM Journal on Scientific and Statistical Computing, 1981).\n\
@end deftypefn")
{
  octave_value_list retval;

  int nargin = args.length ();

  if (nargin < 1 || nargin > 3 || nargout < 0 || nargout > 4)
    {
      print_usage ();
      return retval;
    }

  // determine if it's AEP or GEP
  bool AEPcase = nargin == 1 || args(1).is_string ();

  // problem dimension
  octave_idx_type nn = args(0).rows ();

  if (nn != args(0).columns())
    {
      gripe_square_matrix_required ("balance");
      return retval;
    }

  bool isfloat = args(0).is_single_type () || 
    (! AEPcase && args(1).is_single_type()); 

  bool complex_case = (args(0).is_complex_type () || 
		       (! AEPcase && args(1).is_complex_type ()));

  // Extract argument 1 parameter for both AEP and GEP.
  Matrix aa;
  ComplexMatrix caa;
  FloatMatrix faa;
  FloatComplexMatrix fcaa;

  if (isfloat)
    {
      if (complex_case)
	fcaa = args(0).float_complex_matrix_value ();
      else
	faa = args(0).float_matrix_value ();
    }
  else
    {
      if (complex_case)
	caa = args(0).complex_matrix_value ();
      else
	aa = args(0).matrix_value ();
    }

  if (error_state)
    return retval;

  // Treat AEP/GEP cases.
  if (AEPcase)
    {  
      // Algebraic eigenvalue problem.
      bool noperm = false, noscal = false;
      if (nargin > 1)
        {
          std::string a1s = args(1).string_value ();
          noperm = a1s == "noperm" || a1s == "S";
          noscal = a1s == "noscal" || a1s == "P";
        }

      // balance the AEP
      if (isfloat)
	{
	  if (complex_case)
	    {
	      FloatComplexAEPBALANCE result (fcaa, noperm, noscal);

	      if (nargout == 0 || nargout == 1)
		retval(0) = result.balanced_matrix ();
	      else if (nargout == 2)
		{
		  retval(1) = result.balanced_matrix ();
		  retval(0) = result.balancing_matrix ();
		}
              else
                {
                  retval(2) = result.balanced_matrix ();
                  retval(0) = result.scaling_vector ();
                  retval(1) = result.permuting_vector ();
                }

	    }
	  else
	    {
	      FloatAEPBALANCE result (faa, noperm, noscal);

	      if (nargout == 0 || nargout == 1)
		retval(0) = result.balanced_matrix ();
	      else if (nargout == 2)
		{
		  retval(1) = result.balanced_matrix ();
		  retval(0) = result.balancing_matrix ();
		}
              else
                {
                  retval(2) = result.balanced_matrix ();
                  retval(0) = result.scaling_vector ();
                  retval(1) = result.permuting_vector ();
                }
	    }
	}
      else
	{
	  if (complex_case)
	    {
	      ComplexAEPBALANCE result (caa, noperm, noscal);

	      if (nargout == 0 || nargout == 1)
		retval(0) = result.balanced_matrix ();
	      else if (nargout == 2)
		{
		  retval(1) = result.balanced_matrix ();
		  retval(0) = result.balancing_matrix ();
		}
              else
                {
                  retval(2) = result.balanced_matrix ();
                  retval(0) = result.scaling_vector ();
                  retval(1) = result.permuting_vector ();
                }
	    }
	  else
	    {
	      AEPBALANCE result (aa, noperm, noscal);

	      if (nargout == 0 || nargout == 1)
		retval(0) = result.balanced_matrix ();
	      else if (nargout == 2)
		{
		  retval(1) = result.balanced_matrix ();
		  retval(0) = result.balancing_matrix ();
		}
              else
                {
                  retval(2) = result.balanced_matrix ();
                  retval(0) = result.scaling_vector ();
                  retval(1) = result.permuting_vector ();
                }
	    }
	}
    }
  else
    {
      std::string bal_job;
      if (nargout == 1)
	warning ("balance: used GEP, should have two output arguments");

      // Generalized eigenvalue problem.
      if (nargin == 2)
	bal_job = "B";
      else if (args(2).is_string ())
	bal_job = args(2).string_value ();
      else
	{
	  error ("balance: GEP argument 3 must be a string");
	  return retval;
	}

      if ((nn != args(1).columns ()) || (nn != args(1).rows ()))
	{
	  gripe_nonconformant ();
	  return retval;
	}

      Matrix bb;
      ComplexMatrix cbb;
      FloatMatrix fbb;
      FloatComplexMatrix fcbb;

      if (isfloat)
	{
	  if (complex_case)
	    fcbb = args(1).float_complex_matrix_value ();
	  else
	    fbb = args(1).float_matrix_value ();
	}
      else
	{
	  if (complex_case)
	    cbb = args(1).complex_matrix_value ();
	  else
	    bb = args(1).matrix_value ();
	}

      // balance the GEP
      if (isfloat)
	{
	  if (complex_case)
	    {
	      FloatComplexGEPBALANCE result (fcaa, fcbb, bal_job);

	      switch (nargout)
		{
		case 4:
		  retval(3) = result.balanced_matrix2 ();
		  // fall through
		case 3:
		  retval(2) = result.balanced_matrix ();
		  retval(1) = result.balancing_matrix2 ();
		  retval(0) = result.balancing_matrix ();
		  break;
		case 2:
		  retval(1) = result.balancing_matrix2 ();
		  // fall through
		case 1:
		  retval(0) = result.balancing_matrix ();
		  break;
		default:
		  error ("balance: invalid number of output arguments");
		  break;
		}
	    }
	  else
	    {
	      FloatGEPBALANCE result (faa, fbb, bal_job);

	      switch (nargout)
		{
		case 4:
		  retval(3) = result.balanced_matrix2 ();
		  // fall through
		case 3:
		  retval(2) = result.balanced_matrix ();
		  retval(1) = result.balancing_matrix2 ();
		  retval(0) = result.balancing_matrix ();
		  break;
		case 2:
		  retval(1) = result.balancing_matrix2 ();
		  // fall through
		case 1:
		  retval(0) = result.balancing_matrix ();
		  break;
		default:
		  error ("balance: invalid number of output arguments");
		  break;
		}
	    }
	}
      else
	{
	  if (complex_case)
	    {
	      ComplexGEPBALANCE result (caa, cbb, bal_job);

	      switch (nargout)
		{
		case 4:
		  retval(3) = result.balanced_matrix2 ();
		  // fall through
		case 3:
		  retval(2) = result.balanced_matrix ();
		  retval(1) = result.balancing_matrix2 ();
		  retval(0) = result.balancing_matrix ();
		  break;
		case 2:
		  retval(1) = result.balancing_matrix2 ();
		  // fall through
		case 1:
		  retval(0) = result.balancing_matrix ();
		  break;
		default:
		  error ("balance: invalid number of output arguments");
		  break;
		}
	    }
	  else
	    {
	      GEPBALANCE result (aa, bb, bal_job);

	      switch (nargout)
		{
		case 4:
		  retval(3) = result.balanced_matrix2 ();
		  // fall through
		case 3:
		  retval(2) = result.balanced_matrix ();
		  retval(1) = result.balancing_matrix2 ();
		  retval(0) = result.balancing_matrix ();
		  break;
		case 2:
		  retval(1) = result.balancing_matrix2 ();
		  // fall through
		case 1:
		  retval(0) = result.balancing_matrix ();
		  break;
		default:
		  error ("balance: invalid number of output arguments");
		  break;
		}
	    }
	}
    }

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/