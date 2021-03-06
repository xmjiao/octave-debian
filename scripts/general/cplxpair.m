## Copyright (C) 2000-2017 Paul Kienzle
##
## This file is part of Octave.
##
## Octave is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or (at
## your option) any later version.
##
## Octave is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with Octave; see the file COPYING.  If not, see
## <http://www.gnu.org/licenses/>.

## -*- texinfo -*-
## @deftypefn  {} {} cplxpair (@var{z})
## @deftypefnx {} {} cplxpair (@var{z}, @var{tol})
## @deftypefnx {} {} cplxpair (@var{z}, @var{tol}, @var{dim})
## Sort the numbers @var{z} into complex conjugate pairs ordered by increasing
## real part.
##
## The negative imaginary complex numbers are placed first within each pair.
## All real numbers (those with
## @code{abs (imag (@var{z}) / @var{z}) < @var{tol}}) are placed after the
## complex pairs.
##
## @var{tol} is a weighting factor which determines the tolerance of matching.
## The default value is 100 and the resulting tolerance for a given complex
## pair is @code{100 * eps (abs (@var{z}(i)))}.
##
## By default the complex pairs are sorted along the first non-singleton
## dimension of @var{z}.  If @var{dim} is specified, then the complex pairs are
## sorted along this dimension.
##
## Signal an error if some complex numbers could not be paired.  Signal an
## error if all complex numbers are not exact conjugates (to within @var{tol}).
## Note that there is no defined order for pairs with identical real parts but
## differing imaginary parts.
## @c Set example in small font to prevent overfull line
##
## @smallexample
## cplxpair (exp (2i*pi*[0:4]'/5)) == exp (2i*pi*[3; 2; 4; 1; 0]/5)
## @end smallexample
## @end deftypefn

## FIXME: subsort returned pairs by imaginary magnitude
## FIXME: Why doesn't exp (2i*pi*[0:4]'/5) produce exact conjugates?  Does
## FIXME: it in Matlab?  The reason is that complex pairs are supposed
## FIXME: to be exact conjugates, and not rely on a tolerance test.

## 2006-05-12 David Bateman - Modified for NDArrays

function y = cplxpair (z, tol, dim)

  if (nargin < 1 || nargin > 3)
    print_usage ();
  endif

  if (isempty (z))
    y = zeros (size (z));
    return;
  endif

  if (nargin < 2 || isempty (tol))
    tol = 100;
  elseif (! isscalar (tol) || tol < 0)
    error ("cplxpair: TOL must be a positive scalar number");
  endif

  nd = ndims (z);
  if (nargin < 3)
    ## Find the first singleton dimension.
    sz = size (z);
    (dim = find (sz > 1, 1)) || (dim = 1);
  else
    dim = floor (dim);
    if (dim < 1 || dim > nd)
      error ("cplxpair: invalid dimension DIM");
    endif
  endif

  ## Move dimension to treat to first position, and convert to a 2-D matrix.
  perm = [dim:nd, 1:dim-1];
  z = permute (z, perm);
  sz = size (z);
  n = sz(1);
  m = prod (sz) / n;
  z = reshape (z, n, m);

  ## Sort the sequence in terms of increasing real values.
  [q, idx] = sort (real (z), 1);
  z = z(idx + n * ones (n, 1) * [0:m-1]);

  ## Put the purely real values at the end of the returned list.
  cls = ifelse (isa (z, "single"), "single", "double");
  [idxi, idxj] = find (abs (imag (z)) ./ (abs (z) + realmin (cls)) ...
                       < tol*eps (abs (z)));
  q = sparse (idxi, idxj, 1, n, m);
  nr = sum (q, 1);
  [q, idx] = sort (q, 1);
  z = z(idx);
  y = z;

  ## For each remaining z, place the value and its conjugate at the start of
  ## the returned list, and remove them from further consideration.
  for j = 1:m
    p = n - nr(j);
    for i = 1:2:p
      if (i+1 > p)
        error ("cplxpair: could not pair all complex numbers");
      endif
      [v, idx] = min (abs (z(i+1:p) - conj (z(i))));
      if (v > tol*eps (abs (z(i))))
        error ("cplxpair: could not pair all complex numbers");
      endif
      if (imag (z(i)) < 0)
        y([i, i+1]) = z([i, idx+i]);
      else
        y([i, i+1]) = z([idx+i, i]);
      endif
      z(idx+i) = z(i+1);
    endfor
  endfor

  ## Reshape the output matrix.
  y = ipermute (reshape (y, sz), perm);

endfunction


%!demo
%! [ cplxpair(exp(2i*pi*[0:4]'/5)), exp(2i*pi*[3; 2; 4; 1; 0]/5) ]

%!assert (isempty (cplxpair ([])))
%!assert (cplxpair (1), 1)
%!assert (cplxpair ([1+1i, 1-1i]), [1-1i, 1+1i])
%!assert (cplxpair ([1+1i, 1+1i, 1, 1-1i, 1-1i, 2]), ...
%!                  [1-1i, 1+1i, 1-1i, 1+1i, 1, 2])
%!assert (cplxpair ([1+1i; 1+1i; 1; 1-1i; 1-1i; 2]), ...
%!                  [1-1i; 1+1i; 1-1i; 1+1i; 1; 2])
%!assert (cplxpair ([0, 1, 2]), [0, 1, 2])

%!shared z
%! z = exp (2i*pi*[4; 3; 5; 2; 6; 1; 0]/7);
%!assert (cplxpair (z(randperm (7))), z)
%!assert (cplxpair (z(randperm (7))), z)
%!assert (cplxpair (z(randperm (7))), z)
%!assert (cplxpair ([z(randperm (7)), z(randperm (7))]), [z,z])
%!assert (cplxpair ([z(randperm (7)), z(randperm (7))],[],1), [z,z])
%!assert (cplxpair ([z(randperm (7)).'; z(randperm (7)).'],[],2), [z.';z.'])

## Test tolerance
%!assert (cplxpair ([2000 * (1+eps) + 4j; 2000 * (1-eps) - 4j]), ...
%!        [(2000 - 4j); (2000 + 4j)], 100*eps(200))
%!error <could not pair> cplxpair ([2000 * (1+eps) + 4j; 2000 * (1-eps) - 4j], 0)

%!error <could not pair> cplxpair ([2e6 + j; 2e6 - j; 1e-9 * (1 + j); 1e-9 * (1 - 2j)])

## Test input validation
%!error cplxpair ()
%!error cplxpair (1,2,3,4)
%!error <TOL must be .* positive> cplxpair (1, -1)
%!error <TOL must be .* scalar number> cplxpair (1, ones (2,2))
%!error <invalid dimension DIM> cplxpair (1, [], 3)
