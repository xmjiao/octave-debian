## Copyright (C) 2013 Roberto Porcu' <roberto.porcu@polimi.it>
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
## @deftypefn {} {@var{solution} =} integrate_const (@var{@@stepper}, @var{@@func}, @var{tspan}, @var{x0}, @var{dt}, @var{options})
##
## This function file can be called by an ODE solver function in order to
## integrate the set of ODEs on the interval @var{[t0,t1]} with a constant
## timestep @var{dt}.
##
## The function returns a structure @var{solution} with two fieldss: @var{t}
## and @var{y}.  @var{t} is a column vector and contains the time stamps.
## @var{y} is a matrix in which each column refers to a different unknown
## of the problem and the row number is the same as the @var{t} row number.
## Thus, each row of the matrix @var{y} contains the values of all unknowns at
## the time value contained in the corresponding row in @var{t}.
##
## The first input argument must be a function handle or inline function
## representing the stepper, i.e., the function responsible for step-by-step
## integration.  This function discriminates one method from the others.
##
## The second input argument is the order of the stepper.  It is needed to
## compute the adaptive timesteps.
##
## The third input argument is a function handle or inline function that
## defines the ODE:
##
## @ifhtml
## @example
## @math{y' = f(t,y)}
## @end example
## @end ifhtml
## @ifnothtml
## @math{y' = f(t,y)}.
## @end ifnothtml
##
## The fourth input argument is the time vector which defines the integration
## interval, i.e., @var{[tspan(1), tspan(end)]} and all intermediate elements
## are taken as times at which the solution is required.
##
## The fourth argument contains the initial conditions for the ODEs.
##
## The fifth input argument represents the fixed timestep and the last input
## argument contains some options that may be needed for the stepper.
## @end deftypefn
##
## @seealso{integrate_adaptive, integrate_n_steps}

function solution = integrate_const (stepper, func, tspan, x0, dt, options)

  solution = struct ();

  ## first values for time and solution
  t = tspan(1);
  x = x0(:);

  direction = odeget (options, "direction", [], "fast");
  if (sign (dt) != direction)
    error ("Octave:invalid-input-arg",
           "option 'InitialStep' has a wrong sign");
  endif

  ## setting parameters
  k = length (tspan);
  counter = 2;
  comp = 0.0;
  tk = tspan(1);
  options.comp = comp;

  ## Initialize the OutputFcn
  if (options.haveoutputfunction)
    if (options.haveoutputselection)
      solution.retout = x(options.OutputSel,end);
    else
      solution.retout = x;
    endif
    feval (options.OutputFcn, tspan, solution.retout, "init",
           options.funarguments{:});
  endif

  ## Initialize the EventFcn
  if (options.haveeventfunction)
    ode_event_handler (options.Events, t(end), x, "init",
                         options.funarguments{:});
  endif

  solution.cntloop = 2;
  solution.cntcycles = 1;
  cntiter = 0;
  solution.unhandledtermination = true;
  solution.cntsave = 2;

  z = t;
  u = x;
  k_vals = feval (func, t , x, options.funarguments{:});

  while (counter <= k)
    ## computing the integration step from t to t+dt
    [s, y, ~, k_vals] = stepper (func, z(end), u(:,end), dt, options, k_vals);

    [tk, comp] = kahan (tk,comp, dt);
    options.comp = comp;
    s(end) = tk;

    if (options.havenonnegative)
      x(options.NonNegative,end) = abs (x(options.NonNegative,end));
      y(options.NonNegative,end) = abs (y(options.NonNegative,end));
      y_est(options.NonNegative,end) = abs (y_est(options.NonNegative,end));
    endif

    if (options.haveoutputfunction && options.haverefine)
      SaveVUForRefine = u(:,end);
    endif

    ## values on this interval for time and solution
    z = [t(end);s];
    u = [x(:,end),y];

    ## if next tspan value is caught, update counter
    if ((z(end) == tspan(counter))
        || (abs (z(end) - tspan(counter)) /
            (max (abs (z(end)), abs (tspan(counter)))) < 8*eps) )
      counter += 1;

    ## if there is an element in time vector at which the solution is required
    ## the program must compute this solution before going on with next steps
    elseif (direction * z(end) > direction * tspan(counter) )
      ## initializing counter for the following cycle
      i = 2;
      while (i <= length (z))

        ## if next tspan value is caught, update counter
        if ((counter <= k)
            && (((z(i) == tspan(counter))
                 || (abs (z(i) - tspan(counter)) /
                     (max (abs (z(i)), abs (tspan(counter)))) < 8*eps))) )
          counter += 1;
        endif
        ## else, loop until there are requested values inside this subinterval
        while ((counter <= k)
               && direction * z(i) > direction * tspan(counter) )
          ## add the interpolated value of the solution
          u = [u(:,1:i-1),u(:,i-1) + (tspan(counter)-z(i-1))/(z(i)-z(i-1))* ...
              (u(:,i)-u(:,i-1)),u(:,i:end)];
          ## add the time requested
          z = [z(1:i-1);tspan(counter);z(i:end)];

          ## update counters
          counter += 1;
          i += 1;
        endwhile

        ## if new time requested is not out of this interval
        if (counter <= k && direction * z(end) > direction * tspan(counter))
          ## update the counter
          i += 1;
        else
          ## else, stop the cycle and go on with the next iteration
          i = length (z)+1;
        endif

      endwhile
    endif

    x = [x,u(:,2:end)];
    t = [t;z(2:end)];
    solution.cntsave += 1;
    solution.cntloop += 1;
    cntiter = 0;

    ## Call OutputFcn only if a valid result has been found.
    ## Stop integration if function returns false.
    if (options.haveoutputfunction)
      for cnt = 0:options.Refine  # Approximation between told and t
        if (options.haverefine)   # Do interpolation
          approxtime = (cnt + 1) / (options.Refine + 2);
          approxvals = (1 - approxtime) * SaveVUForRefine ...
                        + (approxtime) * y(:,end);
          approxtime = s(end) + approxtime*dt;
        else
          approxvals = x(:,end);
          approxtime = t(end);
        endif
        if (options.haveoutputselection)
          approxvals = approxvals(options.OutputSel);
        endif
        pltret = feval (options.OutputFcn, approxtime, approxvals, [],
                         options.funarguments{:});
        if (pltret)  # Leave refinement loop
          break;
        endif
      endfor
      if (pltret)  # Leave main loop
        solution.unhandledtermination = false;
        break;
      endif
    endif

    ## Call Events function only if a valid result has been found.
    ## Stop integration if eventbreak is true.
    if (options.haveeventfunction)
      solution.event = ode_event_handler (options.Events, t(end), x(:,end),
                                             [], options.funarguments{:});
      if (! isempty (solution.event{1}) && solution.event{1} == 1)
        t(solution.cntloop-1,:) = solution.event{3}(end,:);
        x(:,solution.cntloop-1) = solution.event{4}(end,:)';
        solution.unhandledtermination = false;
        break;
      endif
    endif

    ## Update counters that count the number of iteration cycles
    solution.cntcycles += 1;  # Needed for cost statistics
    cntiter += 1;             # Needed to find iteration problems

    ## Stop solving because, in the last 5,000 steps, no successful valid
    ## value has been found
    if (cntiter >= 5_000)
      error (["integrate_const: Solving was not successful. ", ...
              " The iterative integration loop exited at time", ...
              " t = %f before the endpoint at tend = %f was reached. ", ...
              " This happened because the iterative integration loop", ...
              " did not find a valid solution at this time stamp. ", ...
              " Try to reduce the value of 'InitialStep' and/or", ...
              " 'MaxStep' with the command 'odeset'."],
             s(end), tspan(end));
    endif

    ## if this is the last iteration, save the length of last interval
    if (counter > k)
      j = length (z);
    endif

  endwhile

  ## Check if integration of the ode has been successful
  if (direction * z(end) < direction * tspan(end))
    if (solution.unhandledtermination == true)
      error ("integrate_const:unexpected_termination",
             [" Solving was not successful. ", ...
              " The iterative integration loop exited at time", ...
              " t = %f before the endpoint at tend = %f was reached. ", ...
              " This may happen if the stepsize becomes too small. ", ...
              " Try to reduce the value of 'InitialStep'", ...
              " and/or 'MaxStep' with the command 'odeset'."],
             z(end), tspan(end));
    else
      warning ("integrate_const:unexpected_termination",
               ["Solver was stopped by a call of 'break'", ...
                " in the main iteration loop at time", ...
                " t = %f before the endpoint at tend = %f was reached. ", ...
                " This may happen because the @odeplot function", ...
                " returned 'true' or the @event function returned 'true'."],
               z(end), tspan(end));
    endif
  endif

  ## compute how many values are out of time inerval
  d = direction * t((end-(j-1)):end) > direction * tspan(end) * ones (j, 1);
  f = sum (d);

  ## remove not-requested values of time and solution
  solution.t = t(1:end-f);
  solution.x = x(:,1:end-f)';

endfunction

