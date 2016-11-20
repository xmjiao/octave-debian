libinterp_EXTRA_DIST =

libinterp_CLEANFILES =
libinterp_DISTCLEANFILES =
libinterp_MAINTAINERCLEANFILES =

## Search local directories before those specified by the user.
libinterp_liboctinterp_la_CPPFLAGS = \
  @OCTINTERP_DLL_DEFS@ \
  -Iliboctave -I$(srcdir)/liboctave \
  -I$(srcdir)/liboctave/cruft/misc \
  -I$(srcdir)/liboctave/array \
  -Iliboctave/numeric -I$(srcdir)/liboctave/numeric \
  -Iliboctave/operators -I$(srcdir)/liboctave/operators \
  -I$(srcdir)/liboctave/system \
  -I$(srcdir)/liboctave/util \
  -I$(srcdir)/libinterp/octave-value \
  -Ilibinterp -I$(srcdir)/libinterp \
  -I$(srcdir)/libinterp/operators \
  -Ilibinterp/parse-tree -I$(srcdir)/libinterp/parse-tree \
  -Ilibinterp/corefcn -I$(srcdir)/libinterp/corefcn \
  -I$(srcdir)/liboctave/wrappers \
  $(HDF5_CPPFLAGS) \
  $(MAGICK_CPPFLAGS)

libinterp_liboctinterp_la_CFLAGS = $(AM_CFLAGS) $(WARN_CFLAGS)

libinterp_liboctinterp_la_CXXFLAGS = $(AM_CXXFLAGS) $(WARN_CXXFLAGS)

octlib_LTLIBRARIES += libinterp/liboctinterp.la

BUILT_SOURCES += \
  libinterp/builtin-defun-decls.h \
  libinterp/corefcn/defaults.h \
  libinterp/corefcn/graphics-props.cc \
  libinterp/corefcn/graphics.h \
  libinterp/corefcn/mxarray.h \
  libinterp/corefcn/oct-tex-parser.h \
  libinterp/corefcn/oct-tex-symbols.cc \
  libinterp/parse-tree/oct-gperf.h \
  libinterp/parse-tree/oct-parse.h \
  libinterp/version.h

ULT_PARSER_SRC := \
  libinterp/corefcn/oct-tex-lexer.in.ll \
  libinterp/corefcn/oct-tex-parser.in.yy \
  libinterp/parse-tree/oct-parse.in.yy

GENERATED_PARSER_FILES := \
  libinterp/corefcn/oct-tex-lexer.ll \
  libinterp/corefcn/oct-tex-parser.h \
  libinterp/corefcn/oct-tex-parser.yy \
  libinterp/parse-tree/oct-parse.yy

## These generated files are included in the source distribution to
## avoid needing certain tools to build from a distribution tarball.

LIBINTERP_BUILT_DISTFILES = \
  $(GENERATED_PARSER_FILES) \
  $(OPT_HANDLERS) \
  libinterp/corefcn/oct-tex-parser.h \
  libinterp/corefcn/oct-tex-symbols.cc \
  libinterp/parse-tree/oct-gperf.h \
  libinterp/parse-tree/oct-parse.h

## Files that are created during build process and installed,
## BUT not distributed in tarball.
LIBINTERP_BUILT_NODISTFILES = \
  libinterp/build-env.cc \
  libinterp/build-env-features.cc \
  libinterp/liboctinterp-build-info.cc \
  libinterp/corefcn/mxarray.h \
  libinterp/corefcn/oct-errno.cc \
  libinterp/corefcn/defaults.h \
  libinterp/corefcn/graphics-props.cc \
  libinterp/corefcn/graphics.h \
  libinterp/builtin-defun-decls.h \
  libinterp/operators/ops.cc \
  libinterp/version.h \
  libinterp/builtins.cc

libinterp_EXTRA_DIST += \
  libinterp/DOCSTRINGS \
  libinterp/build-env.in.cc \
  libinterp/build-env-features.sh \
  libinterp/deprecated-config.h \
  libinterp/gendoc.pl \
  libinterp/genprops.awk \
  libinterp/liboctinterp-build-info.in.cc \
  libinterp/mk-errno-list \
  libinterp/mk-pkg-add \
  libinterp/mkops \
  libinterp/op-kw-docs \
  libinterp/version.in.h \
  $(LIBINTERP_BUILT_DISTFILES)

octinclude_HEADERS += \
  libinterp/builtins.h \
  libinterp/build-env.h \
  libinterp/liboctinterp-build-info.h \
  libinterp/octave.h \
  libinterp/options-usage.h \
  $(COREFCN_INC) \
  $(LIBINTERP_OPERATORS_INC) \
  $(OCTAVE_VALUE_INC) \
  $(PARSE_TREE_INC) \
  $(PARSER_INC)

noinst_HEADERS += \
  $(NOINSTALL_LIBINTERP_OPERATORS_INC)

nodist_octinclude_HEADERS += \
  libinterp/builtin-defun-decls.h \
  libinterp/corefcn/defaults.h \
  libinterp/corefcn/graphics-props.cc \
  libinterp/corefcn/graphics.h \
  libinterp/corefcn/mxarray.h \
  libinterp/version.h

DIST_SRC += \
  libinterp/octave.cc \
  libinterp/version.cc \
  $(OCTAVE_VALUE_SRC) \
  $(PARSE_TREE_SRC) \
  $(COREFCN_SRC)

include libinterp/parse-tree/module.mk
include libinterp/octave-value/module.mk
include libinterp/operators/module.mk
include libinterp/template-inst/module.mk
include libinterp/corefcn/module.mk
include libinterp/dldfcn/module.mk

$(srcdir)/libinterp/dldfcn/module.mk: $(srcdir)/libinterp/dldfcn/config-module.sh $(srcdir)/libinterp/dldfcn/config-module.awk $(srcdir)/libinterp/dldfcn/module-files
	$(AM_V_GEN)$(SHELL) $(srcdir)/libinterp/dldfcn/config-module.sh $(srcdir)

if AMCOND_ENABLE_DYNAMIC_LINKING
  OCT_FILES = $(DLDFCN_LIBS:.la=.oct)
  DLD_LIBOCTINTERP_LIBADD = libinterp/liboctinterp.la
  LIBINTERP_DLDFCN_LIBADD =
else
  OCT_FILES =
  DLD_LIBOCTINTERP_LIBADD =
  LIBINTERP_DLDFCN_LIBADD = $(DLDFCN_LIBS)
endif

libinterp_liboctinterp_la_SOURCES = \
  libinterp/octave.cc \
  libinterp/version.cc \
  $(LIBINTERP_OPERATORS_SRC) \
  $(TEMPLATE_INST_SRC)

nodist_libinterp_liboctinterp_la_SOURCES = \
  libinterp/corefcn/mxarray.h \
  libinterp/corefcn/oct-errno.cc \
  libinterp/corefcn/defaults.h \
  libinterp/corefcn/graphics.h \
  libinterp/operators/ops.cc \
  libinterp/builtin-defun-decls.h \
  libinterp/builtins.cc \
  libinterp/build-env.cc \
  libinterp/build-env-features.cc \
  libinterp/liboctinterp-build-info.cc \
  libinterp/version.h

libinterp_liboctinterp_la_LIBADD = \
  libinterp/octave-value/liboctave-value.la \
  libinterp/parse-tree/libparse-tree.la \
  libinterp/corefcn/libcorefcn.la \
  $(LIBINTERP_DLDFCN_LIBADD) \
  liboctave/liboctave.la \
  $(LIBOCTINTERP_LINK_DEPS)

# Increment these as needed and according to the rules in the libtool manual:
libinterp_liboctinterp_current = 4
libinterp_liboctinterp_revision = 0
libinterp_liboctinterp_age = 0

libinterp_liboctinterp_version_info = $(libinterp_liboctinterp_current):$(libinterp_liboctinterp_revision):$(libinterp_liboctinterp_age)

libinterp_liboctinterp_la_LDFLAGS = \
  -version-info $(libinterp_liboctinterp_version_info) \
  $(NO_UNDEFINED_LDFLAG) \
  -bindir $(bindir) \
  $(LIBOCTINTERP_LINK_OPTS) \
  $(WARN_LDFLAGS)

ULT_DIST_SRC := \
  $(filter-out $(GENERATED_PARSER_FILES), $(DIST_SRC)) $(ULT_PARSER_SRC)

LIBINTERP_FOUND_DEFUN_FILES := \
  $(shell $(SHELL) $(srcdir)/build-aux/find-defun-files.sh "$(srcdir)" $(ULT_DIST_SRC))

BUILT_IN_DEFUN_FILES = $(OPT_HANDLERS) $(LIBINTERP_FOUND_DEFUN_FILES)

DLDFCN_DEFUN_FILES = $(DLDFCN_SRC)

if AMCOND_ENABLE_DYNAMIC_LINKING
  DEFUN_FILES = $(BUILT_IN_DEFUN_FILES)
else
  DEFUN_FILES = $(BUILT_IN_DEFUN_FILES) $(DLDFCN_DEFUN_FILES)
endif

LIBINTERP_DEFUN_FILES = $(BUILT_IN_DEFUN_FILES) $(DLDFCN_DEFUN_FILES)

## FIXME: The following two variables are deprecated and should be removed
##        in Octave version 3.12.
DLL_CDEFS = @OCTINTERP_DLL_DEFS@
DLL_CXXDEFS = @OCTINTERP_DLL_DEFS@

## Rules to build test files

LIBINTERP_TST_FILES_SRC := $(shell $(SHELL) $(srcdir)/build-aux/find-files-with-tests.sh "$(srcdir)" $(ULT_DIST_SRC) $(DLDFCN_SRC))

LIBINTERP_TST_FILES := $(addsuffix -tst,$(LIBINTERP_TST_FILES_SRC))

libinterptestsdir := $(octtestsdir)

nobase_libinterptests_DATA = $(LIBINTERP_TST_FILES)

## Cancel the suffix rule and use a pattern rule instead.
.yy.cc:

## The ylwrap script always updates the parser source file so we use a temporary file
## name and our own move-if-change rule for that file.  Additionally fix up the file
## name comments that bison writes into the source file.
%.cc %.h : %.yy
	$(AM_V_YACC)$(am__skipyacc) rm -f $*.cc-t $*.cc-tt && \
	$(SHELL) $(YLWRAP) $< y.tab.c $*.cc-t y.tab.h $*.h y.output $*.output -- $(YACCCOMPILE) && \
	$(SED) 's|"$*\.cc-t"|"$*.cc"|g' $*.cc-t > $*.cc-tt && \
	mv $*.cc-tt $*.cc-t && \
	$(call move_if_change_rule,$*.cc-t,$*.cc)

## Special rules:
## Mostly for sources which must be built before rest of compilation.

libinterp/build-env.cc: libinterp/build-env.in.cc build-aux/subst-config-vals.sh | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)$(call simple-filter-rule,build-aux/subst-config-vals.sh)

libinterp/build-env-features.cc: config.h libinterp/build-env-features.sh | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)rm -f $@-t && \
	$(SHELL) $(srcdir)/libinterp/build-env-features.sh $< > $@-t && \
	mv $@-t $@

libinterp/version.h: libinterp/version.in.h build-aux/mk-version-h.sh | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)$(call simple-filter-rule,build-aux/mk-version-h.sh)

libinterp/liboctinterp-build-info.cc: libinterp/liboctinterp-build-info.in.cc HG-ID | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)rm -f $@-t && \
	$(SED) \
	  -e "s|%NO_EDIT_WARNING%|DO NOT EDIT!  Generated automatically by Makefile|" \
	  -e "s|%OCTAVE_HG_ID%|$(HG_ID_VAR)|" $< > $@-t && \
	$(simple_move_if_change_rule)

if AMCOND_ENABLE_DYNAMIC_LINKING
  mkbuiltins_dld_opt =
else
  mkbuiltins_dld_opt = --disable-dl
endif

libinterp/builtins.cc: $(LIBINTERP_DEFUN_FILES) build-aux/mk-builtins.sh | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)rm -f $@-t && \
	$(SHELL) $(srcdir)/build-aux/mk-builtins.sh --source $(mkbuiltins_dld_opt) "$(srcdir)" -- $(LIBINTERP_DEFUN_FILES) > $@-t && \
	mv $@-t $@

libinterp/builtin-defun-decls.h: $(LIBINTERP_DEFUN_FILES) build-aux/mk-builtins.sh | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)rm -f $@-t && \
	$(SHELL) $(srcdir)/build-aux/mk-builtins.sh --header $(mkbuiltins_dld_opt) "$(srcdir)" -- $(LIBINTERP_DEFUN_FILES) > $@-t && \
	$(simple_move_if_change_rule)

if AMCOND_ENABLE_DYNAMIC_LINKING
DLDFCN_PKG_ADD_FILE = libinterp/dldfcn/PKG_ADD

libinterp/dldfcn/PKG_ADD: $(DLDFCN_DEFUN_FILES) libinterp/mk-pkg-add | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)rm -f $@-t && \
	$(SHELL) $(srcdir)/libinterp/mk-pkg-add "$(srcdir)" $(DLDFCN_DEFUN_FILES) > $@-t && \
	mv $@-t $@
endif

DOCSTRING_FILES += libinterp/DOCSTRINGS

libinterp/DOCSTRINGS: $(LIBINTERP_DEFUN_FILES) libinterp/op-kw-docs | libinterp/$(octave_dirstamp)
	$(AM_V_GEN)rm -f libinterp/DOCSTRINGS-t && \
	( $(PERL) $(srcdir)/libinterp/gendoc.pl "$(srcdir)" $(LIBINTERP_DEFUN_FILES); $(SED) -ne '/^\x1d/,$$p' $(srcdir)/libinterp/op-kw-docs ) > libinterp/DOCSTRINGS-t && \
	$(call move_if_change_rule,libinterp/DOCSTRINGS-t,$@)

OCTAVE_INTERPRETER_TARGETS += \
  $(OCT_FILES) \
  $(DLDFCN_PKG_ADD_FILE) \
  $(LIBINTERP_TST_FILES)

DIRSTAMP_FILES += libinterp/$(octave_dirstamp)

install-data-hook: install-oct install-built-in-docstrings install-deprecated-config-h

uninstall-local: uninstall-oct uninstall-built-in-docstrings uninstall-deprecated-config-h

if AMCOND_ENABLE_DYNAMIC_LINKING
install-oct:
	$(MKDIR_P) $(DESTDIR)$(octfiledir)
	if [ -n "`cat $(DLDFCN_PKG_ADD_FILE)`" ]; then \
	  $(INSTALL_DATA) $(DLDFCN_PKG_ADD_FILE) $(DESTDIR)$(octfiledir)/PKG_ADD; \
	fi
	cd $(DESTDIR)$(octlibdir) && \
	for ltlib in $(DLDFCN_LIBS); do \
	  f=`echo $$ltlib | $(SED) 's,.*/,,'`; \
	  dl=`$(SED) -n -e "s/dlname='\([^']*\)'/\1/p" < $$f`; \
	  if [ -n "$$dl" ]; then \
	    $(INSTALL_PROGRAM) $$dl $(DESTDIR)$(octfiledir)/`echo $$f | $(SED) 's,^lib,,; s,\.la$$,.oct,'`; \
	  else \
	    echo "error: dlname is empty in $$ltlib!"; \
	    exit 1; \
	  fi; \
	  lnames=`$(SED) -n -e "s/library_names='\([^']*\)'/\1/p" < $$f`; \
	  if [ -n "$$lnames" ]; then \
	    rm -f $$f $$lnames $$dl; \
	  fi \
	done

uninstall-oct:
	for f in $(notdir $(OCT_FILES)); do \
	  rm -f $(DESTDIR)$(octfiledir)/$$f; \
	done
	rm -f $(DESTDIR)$(octfiledir)/PKG_ADD
endif
.PHONY: install-oct uninstall-oct

install-built-in-docstrings: libinterp/DOCSTRINGS
	$(MKDIR_P) $(DESTDIR)$(octetcdir)
	$(INSTALL_DATA) $< $(DESTDIR)$(octetcdir)/built-in-docstrings
.PHONY: install-built-in-docstrings

uninstall-built-in-docstrings:
	rm -f $(DESTDIR)$(octetcdir)/built-in-docstrings
.PHONY: uninstall-built-in-docstrings

install-deprecated-config-h: libinterp/deprecated-config.h
	$(MKDIR_P) $(DESTDIR)$(octincludedir)
	$(INSTALL_DATA) $< $(DESTDIR)$(octincludedir)/config.h
.PHONY: install-deprecated-config-h

uninstall-deprecated-config-h:
	rm -f $(DESTDIR)$(octincludedir)/config.h
.PHONY: uninstall-deprecated-config-h

EXTRA_DIST += $(libinterp_EXTRA_DIST)

libinterp_CLEANFILES += \
  $(DLDFCN_PKG_ADD_FILE) \
  $(LIBINTERP_BUILT_NODISTFILES) \
  $(LIBINTERP_TST_FILES) \
  $(OCT_FILES) \
  libinterp/corefcn/oct-tex-parser.output \
  libinterp/parse-tree/oct-parse.output

libinterp_MAINTAINERCLEANFILES += \
  libinterp/DOCSTRINGS \
  $(LIBINTERP_BUILT_DISTFILES)

BUILT_DISTFILES += $(LIBINTERP_BUILT_DISTFILES)
BUILT_NODISTFILES += $(LIBINTERP_BUILT_NODISTFILES)

CLEANFILES += $(libinterp_CLEANFILES)
DISTCLEANFILES += $(libinterp_DISTCLEANFILES)
MAINTAINERCLEANFILES += $(libinterp_MAINTAINERCLEANFILES)

libinterp-clean:
	rm -f $(libinterp_CLEANFILES)

libinterp-distclean: libinterp-clean
	rm -f $(libinterp_DISTCLEANFILES)

libinterp-maintainer-clean: libinterp-distclean
	rm -f $(libinterp_MAINTAINERCLEANFILES)
