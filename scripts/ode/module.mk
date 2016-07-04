FCN_FILE_DIRS += \
  scripts/ode \
  scripts/ode/private

scripts_ode_PRIVATE_FCN_FILES = \
  scripts/ode/private/AbsRel_Norm.m \
  scripts/ode/private/integrate_adaptive.m \
  scripts/ode/private/integrate_const.m \
  scripts/ode/private/integrate_n_steps.m \
  scripts/ode/private/kahan.m \
  scripts/ode/private/known_option_names.m \
  scripts/ode/private/ode_event_handler.m \
  scripts/ode/private/ode_struct_value_check.m \
  scripts/ode/private/runge_kutta_23.m \
  scripts/ode/private/runge_kutta_45_dorpri.m \
  scripts/ode/private/runge_kutta_interpolate.m \
  scripts/ode/private/starting_stepsize.m

scripts_ode_FCN_FILES =  \
  scripts/ode/ode23.m \
  scripts/ode/ode45.m \
  scripts/ode/odeset.m \
  scripts/ode/odeget.m \
  scripts/ode/odeplot.m

scripts_odedir = $(fcnfiledir)/ode

scripts_ode_DATA = $(scripts_ode_FCN_FILES)

scripts_ode_privatedir = $(fcnfiledir)/ode/private

scripts_ode_private_DATA = $(scripts_ode_PRIVATE_FCN_FILES)

FCN_FILES += \
  $(scripts_ode_FCN_FILES) \
  $(scripts_ode_PRIVATE_FCN_FILES)

PKG_ADD_FILES += scripts/ode/PKG_ADD

DIRSTAMP_FILES += scripts/ode/$(octave_dirstamp)
