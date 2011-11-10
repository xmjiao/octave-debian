/*

Copyright (C) 2005, 2006, 2007, 2008 David Bateman

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

// This is the octave interface to ccolamd, which bore the copyright given
// in the help of the functions.

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <cstdlib>

#include <string>
#include <vector>

#include "ov.h"
#include "defun-dld.h"
#include "pager.h"
#include "ov-re-mat.h"

#include "ov-re-sparse.h"
#include "ov-cx-sparse.h"

#include "oct-sparse.h"
#include "oct-locbuf.h"

#ifdef IDX_TYPE_LONG
#define CCOLAMD_NAME(name) ccolamd_l ## name
#define CSYMAMD_NAME(name) csymamd_l ## name
#else
#define CCOLAMD_NAME(name) ccolamd ## name
#define CSYMAMD_NAME(name) csymamd ## name
#endif

DEFUN_DLD (ccolamd, args, nargout,
    "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{p} =} ccolamd (@var{s})\n\
@deftypefnx {Loadable Function} {@var{p} =} ccolamd (@var{s}, @var{knobs})\n\
@deftypefnx {Loadable Function} {@var{p} =} ccolamd (@var{s}, @var{knobs}, @var{cmember})\n\
@deftypefnx {Loadable Function} {[@var{p}, @var{stats}] =} ccolamd (@dots{})\n\
\n\
Constrained column approximate minimum degree permutation.  @code{@var{p} =\n\
ccolamd (@var{s})} returns the column approximate minimum degree permutation\n\
vector for the sparse matrix @var{s}.  For a non-symmetric matrix @var{s},\n\
@code{@var{s} (:, @var{p})} tends to have sparser LU factors than @var{s}.\n\
@code{chol (@var{s} (:, @var{p})' * @var{s} (:, @var{p}))} also tends to be\n\
sparser than @code{chol (@var{s}' * @var{s})}.  @code{@var{p} = ccolamd\n\
(@var{s}, 1)} optimizes the ordering for @code{lu (@var{s} (:, @var{p}))}.\n\
The ordering is followed by a column elimination tree post-ordering.\n\
\n\
@var{knobs} is an optional one- to five-element input vector, with a default\n\
value of @code{[0 10 10 1 0]} if not present or empty.  Entries not present\n\
are set to their defaults.\n\
\n\
@table @code\n\
@item @var{knobs}(1)\n\
if nonzero, the ordering is optimized for @code{lu (S (:, p))}.  It will be a\n\
poor ordering for @code{chol (@var{s} (:, @var{p})' * @var{s} (:,\n\
@var{p}))}.  This is the most important knob for ccolamd.\n\
\n\
@item @var{knob}(2)\n\
if @var{s} is m-by-n, rows with more than @code{max (16, @var{knobs} (2) *\n\
sqrt (n))} entries are ignored.\n\
\n\
@item @var{knob}(3)\n\
columns with more than @code{max (16, @var{knobs} (3) * sqrt (min (@var{m},\n\
@var{n})))} entries are ignored and ordered last in the output permutation\n\
(subject to the cmember constraints).\n\
\n\
@item @var{knob}(4)\n\
if nonzero, aggressive absorption is performed.\n\
\n\
@item @var{knob}(5)\n\
if nonzero, statistics and knobs are printed.\n\
\n\
@end table\n\
\n\
@var{cmember} is an optional vector of length n.  It defines the constraints\n\
on the column ordering.  If @code{@var{cmember} (j) = @var{c}}, then column\n\
@var{j} is in constraint set @var{c} (@var{c} must be in the range 1 to\n\
@var{n}).  In the output permutation @var{p}, all columns in set 1 appear\n\
first, followed by all columns in set 2, and so on.  @code{@var{cmember} =\n\
ones(1,n)} if not present or empty.  @code{ccolamd (@var{s}, [], 1 :\n\
@var{n})} returns @code{1 : @var{n}}\n\
\n\
@code{@var{p} = ccolamd (@var{s})} is about the same as @code{@var{p} =\n\
colamd (@var{s})}.  @var{knobs} and its default values differ.  @code{colamd}\n\
always does aggressive absorption, and it finds an ordering suitable for\n\
both @code{lu (@var{s} (:, @var{p}))} and @code{chol (@var{S} (:, @var{p})'\n\
* @var{s} (:, @var{p}))}; it cannot optimize its ordering for\n\
@code{lu (@var{s} (:, @var{p}))} to the extent that\n\
@code{ccolamd (@var{s}, 1)} can.\n\
\n\
@var{stats} is an optional 20-element output vector that provides data\n\
about the ordering and the validity of the input matrix @var{s}.  Ordering\n\
statistics are in @code{@var{stats} (1 : 3)}.  @code{@var{stats} (1)} and\n\
@code{@var{stats} (2)} are the number of dense or empty rows and columns\n\
ignored by CCOLAMD and @code{@var{stats} (3)} is the number of garbage\n\
collections performed on the internal data structure used by CCOLAMD\n\
(roughly of size @code{2.2 * nnz (@var{s}) + 4 * @var{m} + 7 * @var{n}}\n\
integers).\n\
\n\
@code{@var{stats} (4 : 7)} provide information if CCOLAMD was able to\n\
continue.  The matrix is OK if @code{@var{stats} (4)} is zero, or 1 if\n\
invalid.  @code{@var{stats} (5)} is the rightmost column index that is\n\
unsorted or contains duplicate entries, or zero if no such column exists.\n\
@code{@var{stats} (6)} is the last seen duplicate or out-of-order row\n\
index in the column index given by @code{@var{stats} (5)}, or zero if no\n\
such row index exists.  @code{@var{stats} (7)} is the number of duplicate\n\
or out-of-order row indices.  @code{@var{stats} (8 : 20)} is always zero in\n\
the current version of CCOLAMD (reserved for future use).\n\
\n\
The authors of the code itself are S. Larimore, T. Davis (Uni of Florida)\n\
and S. Rajamanickam in collaboration with J. Bilbert and E. Ng.  Supported\n\
by the National Science Foundation (DMS-9504974, DMS-9803599, CCR-0203270),\n\
and a grant from Sandia National Lab.  See\n\
@url{http://www.cise.ufl.edu/research/sparse} for ccolamd, csymamd, amd,\n\
colamd, symamd, and other related orderings.\n\
@seealso{colamd, csymamd}\n\
@end deftypefn")
{
  octave_value_list retval;

#ifdef HAVE_CCOLAMD

  int nargin = args.length ();
  int spumoni = 0;
 
  if (nargout < 0 || nargout > 2 || nargin < 0 || nargin > 3)
    usage ("ccolamd: incorrect number of input and/or output arguments");
  else
    {
      // Get knobs
      OCTAVE_LOCAL_BUFFER (double, knobs, CCOLAMD_KNOBS);      
      CCOLAMD_NAME (_set_defaults) (knobs);

      // Check for user-passed knobs
      if (nargin > 1)
	{
	  NDArray User_knobs = args(1).array_value ();
	  int nel_User_knobs = User_knobs.length ();

	  if (nel_User_knobs > 0) 
	    knobs [CCOLAMD_LU] = (User_knobs (0) != 0);
	  if (nel_User_knobs > 1) 
	    knobs [CCOLAMD_DENSE_ROW]  = User_knobs (1);
	  if (nel_User_knobs > 2) 
	    knobs [CCOLAMD_DENSE_COL]  = User_knobs (2);
	  if (nel_User_knobs > 3) 
	    knobs [CCOLAMD_AGGRESSIVE] = (User_knobs (3) != 0);
	  if (nel_User_knobs > 4) 
	    spumoni = (User_knobs (4) != 0);

	  // print knob settings if spumoni is set
	  if (spumoni)
	    {
	      octave_stdout << "\nccolamd version " << CCOLAMD_MAIN_VERSION << "."
			    <<  CCOLAMD_SUB_VERSION << ", " << CCOLAMD_DATE 
			    << ":\nknobs(1): " << User_knobs (0) << ", order for ";
	      if ( knobs [CCOLAMD_LU] != 0)
		octave_stdout << "lu(A)\n";
	      else
		octave_stdout << "chol(A'*A)\n";

	      if (knobs [CCOLAMD_DENSE_ROW] >= 0)
		octave_stdout << "knobs(2): " << User_knobs (1) 
			      << ", rows with > max(16,"
			      << knobs [CCOLAMD_DENSE_ROW] << "*sqrt(size(A,2)))"
			      << " entries removed\n";
	      else
		octave_stdout << "knobs(2): " << User_knobs (1)
			      << ", no dense rows removed\n";

	      if (knobs [CCOLAMD_DENSE_COL] >= 0)
		octave_stdout << "knobs(3): " << User_knobs (2) 
			      << ", cols with > max(16,"
			      << knobs [CCOLAMD_DENSE_COL] << "*sqrt(size(A)))"
			      << " entries removed\n";
	      else
		octave_stdout << "knobs(3): " << User_knobs (2)
			      << ", no dense columns removed\n";

	      if (knobs [CCOLAMD_AGGRESSIVE] != 0)
		octave_stdout << "knobs(4): " << User_knobs(3) 
			      << ", aggressive absorption: yes";
	      else
		octave_stdout << "knobs(4): " << User_knobs(3) 
			      << ", aggressive absorption: no";
 
	      octave_stdout << "knobs(5): " << User_knobs (4) 
			    << ", statistics and knobs printed\n";
	    }
	}
      
      octave_idx_type n_row, n_col, nnz;
      octave_idx_type *ridx, *cidx;
      SparseComplexMatrix scm;
      SparseMatrix sm;

      if (args(0).is_sparse_type ())
	{
	  if (args(0).is_complex_type ())
	    {
	      scm = args(0). sparse_complex_matrix_value ();
	      n_row = scm.rows ();
	      n_col = scm.cols ();
	      nnz = scm.nzmax ();
	      ridx = scm.xridx ();
	      cidx = scm.xcidx ();
	    }
	  else
	    {
	      sm = args(0).sparse_matrix_value ();

	      n_row = sm.rows ();
	      n_col = sm.cols ();
	      nnz = sm.nzmax ();
	      ridx = sm.xridx ();
	      cidx = sm.xcidx ();
	    }
	}
      else
	{
	  if (args(0).is_complex_type ())
	    sm = SparseMatrix (real (args(0).complex_matrix_value ()));
	  else
	    sm = SparseMatrix (args(0).matrix_value ());

	  n_row = sm.rows ();
	  n_col = sm.cols ();
	  nnz = sm.nzmax ();
	  ridx = sm.xridx ();
	  cidx = sm.xcidx ();
	}

      // Allocate workspace for ccolamd
      OCTAVE_LOCAL_BUFFER (octave_idx_type, p, n_col+1);
      for (octave_idx_type i = 0; i < n_col+1; i++)
	p[i] = cidx [i];

      octave_idx_type Alen = CCOLAMD_NAME (_recommended) (nnz, n_row, n_col);
      OCTAVE_LOCAL_BUFFER (octave_idx_type, A, Alen);
      for (octave_idx_type i = 0; i < nnz; i++)
	A[i] = ridx [i];

      OCTAVE_LOCAL_BUFFER (octave_idx_type, stats, CCOLAMD_STATS);

      if (nargin > 2)
	{
	  NDArray in_cmember = args(2).array_value();
	  octave_idx_type cslen = in_cmember.length();
	  OCTAVE_LOCAL_BUFFER (octave_idx_type, cmember, cslen);
	  for (octave_idx_type i = 0; i < cslen; i++)
	    // convert cmember from 1-based to 0-based
	    cmember[i] = static_cast<octave_idx_type>(in_cmember(i) - 1);
	  
	  if (cslen != n_col)
	    error ("ccolamd: cmember must be of length equal to #cols of A");
	  else
	    // Order the columns (destroys A)
	    if (! CCOLAMD_NAME () (n_row, n_col, Alen, A, p, knobs, stats, cmember))
	      {
		CCOLAMD_NAME (_report) (stats) ;
		error ("ccolamd: internal error!");
		return retval;
	      }
	}
      else
	{
	  // Order the columns (destroys A)
	  if (! CCOLAMD_NAME () (n_row, n_col, Alen, A, p, knobs, stats, 0))
	    {
	      CCOLAMD_NAME (_report) (stats) ;
	      error ("ccolamd: internal error!");
	      return retval;
	    }
	}

      // return the permutation vector
      NDArray out_perm (dim_vector (1, n_col));
      for (octave_idx_type i = 0; i < n_col; i++)
	out_perm(i) = p [i] + 1;

      retval (0) = out_perm;

      // print stats if spumoni > 0
      if (spumoni > 0)
	CCOLAMD_NAME (_report) (stats) ;

      // Return the stats vector
      if (nargout == 2)
	{
	  NDArray out_stats (dim_vector (1, CCOLAMD_STATS));
	  for (octave_idx_type i = 0 ; i < CCOLAMD_STATS ; i++)
	    out_stats (i) = stats [i] ;
	  retval(1) = out_stats;

	  // fix stats (5) and (6), for 1-based information on 
	  // jumbled matrix.  note that this correction doesn't 
	  // occur if symamd returns FALSE
	  out_stats (CCOLAMD_INFO1) ++ ; 
	  out_stats (CCOLAMD_INFO2) ++ ; 
	}
    }

#else

  error ("ccolamd: not available in this version of Octave");

#endif

  return retval;
}

DEFUN_DLD (csymamd, args, nargout,
    "-*- texinfo -*-\n\
@deftypefn {Loadable Function} {@var{p} =} csymamd (@var{s})\n\
@deftypefnx {Loadable Function} {@var{p} =} csymamd (@var{s}, @var{knobs})\n\
@deftypefnx {Loadable Function} {@var{p} =} csymamd (@var{s}, @var{knobs}, @var{cmember})\n\
@deftypefnx {Loadable Function} {[@var{p}, @var{stats}] =} csymamd (@dots{})\n\
\n\
For a symmetric positive definite matrix @var{s}, returns the permutation\n\
vector @var{p} such that @code{@var{s}(@var{p},@var{p})} tends to have a\n\
sparser Cholesky factor than @var{s}.  Sometimes @code{csymamd} works well\n\
for symmetric indefinite matrices too.  The matrix @var{s} is assumed to\n\
be symmetric; only the strictly lower triangular part is referenced.\n\
@var{s} must be square.  The ordering is followed by an elimination tree\n\
post-ordering.\n\
\n\
@var{knobs} is an optional one- to three-element input vector, with a\n\
default value of @code{[10 1 0]} if present or empty.  Entries not\n\
present are set to their defaults.\n\
\n\
@table @code\n\
@item @var{knobs}(1)\n\
If @var{s} is n-by-n, then rows and columns with more than\n\
@code{max(16,@var{knobs}(1)*sqrt(n))} entries are ignored, and ordered\n\
last in the output permutation (subject to the cmember constraints).\n\
\n\
@item @var{knobs}(2)\n\
If nonzero, aggressive absorption is performed.\n\
\n\
@item @var{knobs}(3)\n\
If nonzero, statistics and knobs are printed.\n\
\n\
@end table\n\
\n\
@var{cmember} is an optional vector of length n. It defines the constraints\n\
on the ordering.  If @code{@var{cmember}(j) = @var{s}}, then row/column j is\n\
in constraint set @var{c} (@var{c} must be in the range 1 to n).  In the\n\
output permutation @var{p}, rows/columns in set 1 appear first, followed\n\
by all rows/columns in set 2, and so on.  @code{@var{cmember} = ones(1,n)}\n\
if not present or empty.  @code{csymamd(@var{s},[],1:n)} returns @code{1:n}.\n\
\n\
@code{@var{p} = csymamd(@var{s})} is about the same as @code{@var{p} =\n\
symamd(@var{s})}.  @var{knobs} and its default values differ.\n\
\n\
@code{@var{stats} (4:7)} provide information if CCOLAMD was able to\n\
continue.  The matrix is OK if @code{@var{stats} (4)} is zero, or 1 if\n\
invalid.  @code{@var{stats} (5)} is the rightmost column index that is\n\
unsorted or contains duplicate entries, or zero if no such column exists.\n\
@code{@var{stats} (6)} is the last seen duplicate or out-of-order row\n\
index in the column index given by @code{@var{stats} (5)}, or zero if no\n\
such row index exists.  @code{@var{stats} (7)} is the number of duplicate\n\
or out-of-order row indices.  @code{@var{stats} (8:20)} is always zero in\n\
the current version of CCOLAMD (reserved for future use).\n\
\n\
The authors of the code itself are S. Larimore, T. Davis (Uni of Florida)\n\
and S. Rajamanickam in collaboration with J. Bilbert and E. Ng.  Supported\n\
by the National Science Foundation (DMS-9504974, DMS-9803599, CCR-0203270),\n\
and a grant from Sandia National Lab.  See\n\
@url{http://www.cise.ufl.edu/research/sparse} for ccolamd, csymamd, amd,\n\
colamd, symamd, and other related orderings.\n\
@seealso{symamd, ccolamd}\n\
@end deftypefn")
{
  octave_value_list retval;

#if HAVE_CCOLAMD

  int nargin = args.length ();
  int spumoni = 0;
 
  if (nargout < 0 || nargout > 2 || nargin < 0 || nargin > 3)
    usage ("ccolamd: incorrect number of input and/or output arguments");
  else
    {
      // Get knobs
      OCTAVE_LOCAL_BUFFER (double, knobs, CCOLAMD_KNOBS);
      CCOLAMD_NAME (_set_defaults) (knobs);

      // Check for user-passed knobs
      if (nargin > 1)
	{
	  NDArray User_knobs = args(1).array_value ();
	  int nel_User_knobs = User_knobs.length ();
	  
	  if (nel_User_knobs > 0) 
	    knobs [CCOLAMD_DENSE_ROW] = User_knobs (0);
	  if (nel_User_knobs > 0) 
	    knobs [CCOLAMD_AGGRESSIVE] = User_knobs (1);
	  if (nel_User_knobs > 1) 
	    spumoni = static_cast<int> (User_knobs (2));

	  // print knob settings if spumoni is set
	  if (spumoni)
	    {
	      octave_stdout << "\ncsymamd version " << CCOLAMD_MAIN_VERSION << "."
			    <<  CCOLAMD_SUB_VERSION << ", " << CCOLAMD_DATE << "\n";

	      if (knobs [CCOLAMD_DENSE_ROW] >= 0)
		octave_stdout << "knobs(1): " << User_knobs (0) 
			      << ", rows/cols with > max(16,"
			      << knobs [CCOLAMD_DENSE_ROW] << "*sqrt(size(A,2)))"
			      << " entries removed\n";
	      else
		octave_stdout << "knobs(1): " << User_knobs (0)
			      << ", no dense rows/cols removed\n";

	      if (knobs [CCOLAMD_AGGRESSIVE] != 0)
		octave_stdout << "knobs(2): " << User_knobs(1) 
			      << ", aggressive absorption: yes";
	      else
		octave_stdout << "knobs(2): " << User_knobs(1) 
			      << ", aggressive absorption: no";
 

	      octave_stdout << "knobs(3): " << User_knobs (2) 
			    << ", statistics and knobs printed\n";
	    }
	}
      
      octave_idx_type n_row, n_col, nnz;
      octave_idx_type *ridx, *cidx;
      SparseMatrix sm;
      SparseComplexMatrix scm;

      if (args(0).is_sparse_type ())
	{
	  if (args(0).is_complex_type ())
	    {
	      scm = args(0).sparse_complex_matrix_value ();
	      n_row = scm.rows ();
	      n_col = scm.cols ();
	      nnz = scm.nzmax ();
	      ridx = scm.xridx ();
	      cidx = scm.xcidx ();
	    }
	  else
	    {
	      sm = args(0).sparse_matrix_value ();
	      n_row = sm.rows ();
	      n_col = sm.cols ();
	      nnz = sm.nzmax ();
	      ridx = sm.xridx ();
	      cidx = sm.xcidx ();
	    }
	}
      else
	{
	  if (args(0).is_complex_type ())
	    sm = SparseMatrix (real (args(0).complex_matrix_value ()));
	  else
	    sm = SparseMatrix (args(0).matrix_value ());
	  
	  n_row = sm.rows ();
	  n_col = sm.cols ();
	  nnz = sm.nzmax ();
	  ridx = sm.xridx ();
	  cidx = sm.xcidx ();
	}

      if (n_row != n_col)
	{
	  error ("symamd: matrix must be square");
	  return retval;
	}

      // Allocate workspace for symamd
      OCTAVE_LOCAL_BUFFER (octave_idx_type, perm, n_col+1);
      OCTAVE_LOCAL_BUFFER (octave_idx_type, stats, CCOLAMD_STATS);

      if (nargin > 2)
	{
	  NDArray in_cmember = args(2).array_value();
	  octave_idx_type cslen = in_cmember.length();
	  OCTAVE_LOCAL_BUFFER (octave_idx_type, cmember, cslen);
	  for (octave_idx_type i = 0; i < cslen; i++)
	    // convert cmember from 1-based to 0-based
	    cmember[i] = static_cast<octave_idx_type>(in_cmember(i) - 1);
	  
	  if (cslen != n_col)
	    error ("ccolamd: cmember must be of length equal to #cols of A");
	  else
	    if (!CSYMAMD_NAME () (n_col, ridx, cidx, perm, knobs, stats, 
				  &calloc, &free, cmember, -1))
	      {
		CSYMAMD_NAME (_report) (stats) ;
		error ("symamd: internal error!") ;
		return retval;
	      }
	}
      else
	{
	  if (!CSYMAMD_NAME () (n_col, ridx, cidx, perm, knobs, stats, 
				&calloc, &free, 0, -1))
	    {
	      CSYMAMD_NAME (_report) (stats) ;
	      error ("symamd: internal error!") ;
	      return retval;
	    }
	}

      // return the permutation vector
      NDArray out_perm (dim_vector (1, n_col));
      for (octave_idx_type i = 0; i < n_col; i++)
	out_perm(i) = perm [i] + 1;

      retval (0) = out_perm;

      // Return the stats vector
      if (nargout == 2)
	{
	  NDArray out_stats (dim_vector (1, CCOLAMD_STATS));
	  for (octave_idx_type i = 0 ; i < CCOLAMD_STATS ; i++)
	    out_stats (i) = stats [i] ;
	  retval(1) = out_stats;

	  // fix stats (5) and (6), for 1-based information on 
	  // jumbled matrix.  note that this correction doesn't 
	  // occur if symamd returns FALSE
	  out_stats (CCOLAMD_INFO1) ++ ; 
	  out_stats (CCOLAMD_INFO2) ++ ; 
	}

      // print stats if spumoni > 0
      if (spumoni > 0)
	CSYMAMD_NAME (_report) (stats) ;

      // Return the stats vector
      if (nargout == 2)
	{
	  NDArray out_stats (dim_vector (1, CCOLAMD_STATS));
	  for (octave_idx_type i = 0 ; i < CCOLAMD_STATS ; i++)
	    out_stats (i) = stats [i] ;
	  retval(1) = out_stats;

	  // fix stats (5) and (6), for 1-based information on 
	  // jumbled matrix.  note that this correction doesn't 
	  // occur if symamd returns FALSE
	  out_stats (CCOLAMD_INFO1) ++ ; 
	  out_stats (CCOLAMD_INFO2) ++ ; 
	}
    }

#else

  error ("csymamd: not available in this version of Octave");

#endif

  return retval;
}

/*
;;; Local Variables: ***
;;; mode: C++ ***
;;; End: ***
*/