## Copyright (C) 1995, 1996, 1997, 2005, 2007, 2008 Kurt Hornik
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
## @deftypefn {Function File} {} exponential_pdf (@var{x}, @var{lambda})
## For each element of @var{x}, compute the probability density function
## (PDF) of the exponential distribution with parameter @var{lambda}.
## @end deftypefn

## Author: KH <Kurt.Hornik@wu-wien.ac.at>
## Description: PDF of the exponential distribution

## Deprecated in version 3.0

function pdf = exponential_pdf (varargin)

  persistent warned = false;
  if (! warned)
    warned = true;
    warning ("Octave:deprecated-function",
             "exponential_pdf is obsolete and will be removed from a future version of Octave; please use exppdf instead");
  endif

 if (nargin > 1)
   varargin{2} = 1 ./ varargin{2};
 endif

 pdf =  exppdf (varargin{:});

endfunction