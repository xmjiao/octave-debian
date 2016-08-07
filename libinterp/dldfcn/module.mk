## DO NOT EDIT -- generated from module-files by config-module.awk

EXTRA_DIST += \
  libinterp/dldfcn/config-module.sh \
  libinterp/dldfcn/config-module.awk \
  libinterp/dldfcn/module-files \
  libinterp/dldfcn/oct-qhull.h

DLDFCN_SRC = \
  libinterp/dldfcn/__delaunayn__.cc \
  libinterp/dldfcn/__eigs__.cc \
  libinterp/dldfcn/__fltk_uigetfile__.cc \
  libinterp/dldfcn/__glpk__.cc \
  libinterp/dldfcn/__init_fltk__.cc \
  libinterp/dldfcn/__init_gnuplot__.cc \
  libinterp/dldfcn/__osmesa_print__.cc \
  libinterp/dldfcn/__voronoi__.cc \
  libinterp/dldfcn/amd.cc \
  libinterp/dldfcn/audiodevinfo.cc \
  libinterp/dldfcn/audioread.cc \
  libinterp/dldfcn/ccolamd.cc \
  libinterp/dldfcn/chol.cc \
  libinterp/dldfcn/colamd.cc \
  libinterp/dldfcn/convhulln.cc \
  libinterp/dldfcn/dmperm.cc \
  libinterp/dldfcn/fftw.cc \
  libinterp/dldfcn/qr.cc \
  libinterp/dldfcn/symbfact.cc \
  libinterp/dldfcn/symrcm.cc \
  libinterp/dldfcn/xzip.cc

DLDFCN_LIBS = $(DLDFCN_SRC:.cc=.la)

if AMCOND_ENABLE_DYNAMIC_LINKING

octlib_LTLIBRARIES += $(DLDFCN_LIBS)

## Use stamp files to avoid problems with checking timestamps
## of symbolic links

%.oct : %.la
	$(AM_V_GEN)$(INSTALL_PROGRAM) libinterp/dldfcn/.libs/$(shell $(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $<) $@

else

noinst_LTLIBRARIES += $(DLDFCN_LIBS)

endif

libinterp_dldfcn___delaunayn___la_SOURCES = libinterp/dldfcn/__delaunayn__.cc
libinterp_dldfcn___delaunayn___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn___delaunayn___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn___delaunayn___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn___delaunayn___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QHULL_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___delaunayn___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(QHULL_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn___eigs___la_SOURCES = libinterp/dldfcn/__eigs__.cc
libinterp_dldfcn___eigs___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(ARPACK_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn___eigs___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(ARPACK_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn___eigs___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(ARPACK_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn___eigs___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(ARPACK_LDFLAGS) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___eigs___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(ARPACK_LIBS) $(SPARSE_XLIBS) $(LAPACK_LIBS) $(BLAS_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn___fltk_uigetfile___la_SOURCES = libinterp/dldfcn/__fltk_uigetfile__.cc
libinterp_dldfcn___fltk_uigetfile___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(FLTK_CPPFLAGS) $(FT2_CPPFLAGS)
libinterp_dldfcn___fltk_uigetfile___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(FLTK_CPPFLAGS) $(FT2_CPPFLAGS)
libinterp_dldfcn___fltk_uigetfile___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(FLTK_CPPFLAGS) $(FT2_CPPFLAGS)
libinterp_dldfcn___fltk_uigetfile___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(FLTK_LDFLAGS) $(FT2_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___fltk_uigetfile___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(FLTK_LIBS) $(FT2_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn___glpk___la_SOURCES = libinterp/dldfcn/__glpk__.cc
libinterp_dldfcn___glpk___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(GLPK_CPPFLAGS)
libinterp_dldfcn___glpk___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(GLPK_CPPFLAGS)
libinterp_dldfcn___glpk___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(GLPK_CPPFLAGS)
libinterp_dldfcn___glpk___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(GLPK_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___glpk___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(GLPK_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn___init_fltk___la_SOURCES = libinterp/dldfcn/__init_fltk__.cc
libinterp_dldfcn___init_fltk___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(FLTK_CPPFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
libinterp_dldfcn___init_fltk___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(FLTK_CPPFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
libinterp_dldfcn___init_fltk___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(FLTK_CPPFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
libinterp_dldfcn___init_fltk___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(FLTK_LDFLAGS) $(FT2_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___init_fltk___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(FLTK_LIBS) $(FT2_LIBS) $(OPENGL_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn___init_gnuplot___la_SOURCES = libinterp/dldfcn/__init_gnuplot__.cc
libinterp_dldfcn___init_gnuplot___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
libinterp_dldfcn___init_gnuplot___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
libinterp_dldfcn___init_gnuplot___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(FT2_CPPFLAGS) $(FONTCONFIG_CPPFLAGS)
libinterp_dldfcn___init_gnuplot___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG)  $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___init_gnuplot___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la  $(OCT_LINK_DEPS)

libinterp_dldfcn___osmesa_print___la_SOURCES = libinterp/dldfcn/__osmesa_print__.cc
libinterp_dldfcn___osmesa_print___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(OSMESA_CPPFLAGS) $(FT2_CPPFLAGS)
libinterp_dldfcn___osmesa_print___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(OSMESA_CPPFLAGS) $(FT2_CPPFLAGS)
libinterp_dldfcn___osmesa_print___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(OSMESA_CPPFLAGS) $(FT2_CPPFLAGS)
libinterp_dldfcn___osmesa_print___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(OSMESA_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___osmesa_print___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(OSMESA_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn___voronoi___la_SOURCES = libinterp/dldfcn/__voronoi__.cc
libinterp_dldfcn___voronoi___la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn___voronoi___la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn___voronoi___la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn___voronoi___la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QHULL_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn___voronoi___la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(QHULL_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_amd_la_SOURCES = libinterp/dldfcn/amd.cc
libinterp_dldfcn_amd_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_amd_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_amd_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_amd_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_amd_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_audiodevinfo_la_SOURCES = libinterp/dldfcn/audiodevinfo.cc
libinterp_dldfcn_audiodevinfo_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(PORTAUDIO_CPPFLAGS)
libinterp_dldfcn_audiodevinfo_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(PORTAUDIO_CPPFLAGS)
libinterp_dldfcn_audiodevinfo_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(PORTAUDIO_CPPFLAGS)
libinterp_dldfcn_audiodevinfo_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(PORTAUDIO_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_audiodevinfo_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(PORTAUDIO_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_audioread_la_SOURCES = libinterp/dldfcn/audioread.cc
libinterp_dldfcn_audioread_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SNDFILE_CPPFLAGS)
libinterp_dldfcn_audioread_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SNDFILE_CPPFLAGS)
libinterp_dldfcn_audioread_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SNDFILE_CPPFLAGS)
libinterp_dldfcn_audioread_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SNDFILE_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_audioread_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SNDFILE_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_ccolamd_la_SOURCES = libinterp/dldfcn/ccolamd.cc
libinterp_dldfcn_ccolamd_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_ccolamd_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_ccolamd_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_ccolamd_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_ccolamd_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_chol_la_SOURCES = libinterp/dldfcn/chol.cc
libinterp_dldfcn_chol_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_chol_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_chol_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_chol_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_chol_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_colamd_la_SOURCES = libinterp/dldfcn/colamd.cc
libinterp_dldfcn_colamd_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_colamd_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_colamd_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_colamd_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_colamd_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_convhulln_la_SOURCES = libinterp/dldfcn/convhulln.cc
libinterp_dldfcn_convhulln_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn_convhulln_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn_convhulln_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(QHULL_CPPFLAGS)
libinterp_dldfcn_convhulln_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QHULL_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_convhulln_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(QHULL_LIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_dmperm_la_SOURCES = libinterp/dldfcn/dmperm.cc
libinterp_dldfcn_dmperm_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_dmperm_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_dmperm_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_dmperm_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_dmperm_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_fftw_la_SOURCES = libinterp/dldfcn/fftw.cc
libinterp_dldfcn_fftw_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(FFTW_XCPPFLAGS)
libinterp_dldfcn_fftw_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(FFTW_XCPPFLAGS)
libinterp_dldfcn_fftw_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(FFTW_XCPPFLAGS)
libinterp_dldfcn_fftw_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(FFTW_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_fftw_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(FFTW_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_qr_la_SOURCES = libinterp/dldfcn/qr.cc
libinterp_dldfcn_qr_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(QRUPDATE_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_qr_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(QRUPDATE_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_qr_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(QRUPDATE_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_qr_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(QRUPDATE_LDFLAGS) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_qr_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(QRUPDATE_LIBS) $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_symbfact_la_SOURCES = libinterp/dldfcn/symbfact.cc
libinterp_dldfcn_symbfact_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_symbfact_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_symbfact_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_symbfact_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_symbfact_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_symrcm_la_SOURCES = libinterp/dldfcn/symrcm.cc
libinterp_dldfcn_symrcm_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_symrcm_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_symrcm_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(SPARSE_XCPPFLAGS)
libinterp_dldfcn_symrcm_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(SPARSE_XLDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_symrcm_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(SPARSE_XLIBS) $(OCT_LINK_DEPS)

libinterp_dldfcn_xzip_la_SOURCES = libinterp/dldfcn/xzip.cc
libinterp_dldfcn_xzip_la_CPPFLAGS = $(libinterp_liboctinterp_la_CPPFLAGS) $(Z_CPPFLAGS) $(BZ2_CPPFLAGS)
libinterp_dldfcn_xzip_la_CFLAGS = $(libinterp_liboctinterp_la_CFLAGS) $(Z_CPPFLAGS) $(BZ2_CPPFLAGS)
libinterp_dldfcn_xzip_la_CXXFLAGS = $(libinterp_liboctinterp_la_CXXFLAGS) $(Z_CPPFLAGS) $(BZ2_CPPFLAGS)
libinterp_dldfcn_xzip_la_LDFLAGS = -avoid-version -module $(NO_UNDEFINED_LDFLAG) $(Z_LDFLAGS) $(BZ2_LDFLAGS) $(OCT_LINK_OPTS) $(WARN_LDFLAGS)
libinterp_dldfcn_xzip_la_LIBADD = $(DLD_LIBOCTINTERP_LIBADD) liboctave/liboctave.la $(Z_LIBS) $(BZ2_LIBS) $(OCT_LINK_DEPS)
