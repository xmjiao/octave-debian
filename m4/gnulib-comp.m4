# DO NOT EDIT! GENERATED AUTOMATICALLY!
# Copyright (C) 2002-2016 Free Software Foundation, Inc.
#
# This file is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This file is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this file.  If not, see <http://www.gnu.org/licenses/>.
#
# As a special exception to the GNU General Public License,
# this file may be distributed as part of a program that
# contains a configuration script generated by Autoconf, under
# the same distribution terms as the rest of that program.
#
# Generated by gnulib-tool.
#
# This file represents the compiled summary of the specification in
# gnulib-cache.m4. It lists the computed macro invocations that need
# to be invoked from configure.ac.
# In projects that use version control, this file can be treated like
# other built files.


# This macro should be invoked from ./configure.ac, in the section
# "Checks for programs", right after AC_PROG_CC, and certainly before
# any checks for libraries, header files, types and library functions.
AC_DEFUN([gl_EARLY],
[
  m4_pattern_forbid([^gl_[A-Z]])dnl the gnulib macro namespace
  m4_pattern_allow([^gl_ES$])dnl a valid locale name
  m4_pattern_allow([^gl_LIBOBJS$])dnl a variable
  m4_pattern_allow([^gl_LTLIBOBJS$])dnl a variable

  # Pre-early section.
  AC_REQUIRE([gl_USE_SYSTEM_EXTENSIONS])
  AC_REQUIRE([gl_PROG_AR_RANLIB])

  AC_REQUIRE([AM_PROG_CC_C_O])
  # Code from module absolute-header:
  # Code from module alloca:
  # Code from module alloca-opt:
  # Code from module allocator:
  # Code from module areadlink:
  # Code from module areadlink-with-size:
  # Code from module assure:
  # Code from module at-internal:
  # Code from module base64:
  # Code from module bitrotate:
  # Code from module c-ctype:
  # Code from module canonicalize:
  # Code from module careadlinkat:
  # Code from module chdir:
  # Code from module chdir-long:
  # Code from module cloexec:
  # Code from module close:
  # Code from module closedir:
  # Code from module configmake:
  # Code from module crypto/md2:
  # Code from module crypto/md4:
  # Code from module crypto/md5:
  # Code from module crypto/sha1:
  # Code from module crypto/sha256:
  # Code from module crypto/sha512:
  # Code from module d-ino:
  # Code from module d-type:
  # Code from module dirent:
  # Code from module dirfd:
  # Code from module dirname:
  # Code from module dirname-lgpl:
  # Code from module dosname:
  # Code from module double-slash-root:
  # Code from module dup:
  # Code from module dup2:
  # Code from module environ:
  # Code from module errno:
  # Code from module error:
  # Code from module exitfail:
  # Code from module extensions:
  # Code from module extern-inline:
  # Code from module fchdir:
  # Code from module fcntl:
  # Code from module fcntl-h:
  # Code from module fd-hook:
  # Code from module fdopendir:
  # Code from module file-set:
  # Code from module filemode:
  # Code from module filename:
  # Code from module filenamecat-lgpl:
  # Code from module flexmember:
  # Code from module float:
  # Code from module fnmatch:
  # Code from module fpieee:
  AC_REQUIRE([gl_FP_IEEE])
  # Code from module fpucw:
  # Code from module frexp:
  # Code from module frexpf:
  # Code from module fseek:
  # Code from module fseeko:
  AC_REQUIRE([AC_FUNC_FSEEKO])
  # Code from module fstat:
  # Code from module fstatat:
  # Code from module ftell:
  # Code from module ftello:
  AC_REQUIRE([AC_FUNC_FSEEKO])
  # Code from module ftruncate:
  # Code from module getcwd:
  # Code from module getcwd-lgpl:
  # Code from module getdtablesize:
  # Code from module gethostname:
  # Code from module getlogin_r:
  # Code from module getopt-gnu:
  # Code from module getopt-posix:
  # Code from module getprogname:
  # Code from module getrusage:
  # Code from module gettext-h:
  # Code from module gettimeofday:
  # Code from module glob:
  # Code from module hard-locale:
  # Code from module hash:
  # Code from module hash-pjw:
  # Code from module hash-triple:
  # Code from module havelib:
  # Code from module include_next:
  # Code from module intprops:
  # Code from module isatty:
  # Code from module isnand-nolibm:
  # Code from module largefile:
  AC_REQUIRE([AC_SYS_LARGEFILE])
  # Code from module limits-h:
  # Code from module link:
  # Code from module localcharset:
  # Code from module lock:
  # Code from module lseek:
  # Code from module lstat:
  # Code from module malloc-gnu:
  # Code from module malloc-posix:
  # Code from module malloca:
  # Code from module math:
  # Code from module mbrtowc:
  # Code from module mbsinit:
  # Code from module mbsrtowcs:
  # Code from module memchr:
  # Code from module mempcpy:
  # Code from module memrchr:
  # Code from module minmax:
  # Code from module mkdir:
  # Code from module mkfifo:
  # Code from module mkostemp:
  # Code from module mktime:
  # Code from module mktime-internal:
  # Code from module msvc-inval:
  # Code from module msvc-nothrow:
  # Code from module multiarch:
  # Code from module nanosleep:
  # Code from module nocrash:
  # Code from module nproc:
  # Code from module open:
  # Code from module openat:
  # Code from module openat-die:
  # Code from module openat-h:
  # Code from module opendir:
  # Code from module pathmax:
  # Code from module pipe-posix:
  # Code from module progname:
  # Code from module putenv:
  # Code from module raise:
  # Code from module readdir:
  # Code from module readlink:
  # Code from module realloc-posix:
  # Code from module rewinddir:
  # Code from module rmdir:
  # Code from module same:
  # Code from module same-inode:
  # Code from module save-cwd:
  # Code from module secure_getenv:
  # Code from module select:
  # Code from module setenv:
  # Code from module sigaction:
  # Code from module signal:
  # Code from module signal-h:
  # Code from module sigprocmask:
  # Code from module size_max:
  # Code from module snippet/_Noreturn:
  # Code from module snippet/arg-nonnull:
  # Code from module snippet/c++defs:
  # Code from module snippet/warn-on-use:
  # Code from module snprintf:
  # Code from module socketlib:
  # Code from module sockets:
  # Code from module socklen:
  # Code from module ssize_t:
  # Code from module stat:
  # Code from module std-gnu11:
  # Code from module stdalign:
  # Code from module stdbool:
  # Code from module stddef:
  # Code from module stdint:
  # Code from module stdio:
  # Code from module stdlib:
  # Code from module strcase:
  # Code from module strdup:
  # Code from module strdup-posix:
  # Code from module streq:
  # Code from module strerror:
  # Code from module strerror-override:
  # Code from module strftime:
  # Code from module string:
  # Code from module strings:
  # Code from module strndup:
  # Code from module strnlen:
  # Code from module strnlen1:
  # Code from module strptime:
  # Code from module strsignal:
  # Code from module symlink:
  # Code from module sys_resource:
  # Code from module sys_select:
  # Code from module sys_socket:
  # Code from module sys_stat:
  # Code from module sys_time:
  # Code from module sys_times:
  # Code from module sys_types:
  # Code from module sys_uio:
  # Code from module sys_utsname:
  # Code from module sys_wait:
  # Code from module tempname:
  # Code from module threadlib:
  gl_THREADLIB_EARLY
  # Code from module time:
  # Code from module time_r:
  # Code from module time_rz:
  # Code from module timegm:
  # Code from module tls:
  # Code from module tmpdir:
  # Code from module tmpfile:
  # Code from module u64:
  # Code from module uname:
  # Code from module unistd:
  # Code from module unistd-safer:
  # Code from module unlink:
  # Code from module unsetenv:
  # Code from module vasnprintf:
  # Code from module vasprintf:
  # Code from module verify:
  # Code from module waitpid:
  # Code from module wchar:
  # Code from module wctype-h:
  # Code from module xalloc:
  # Code from module xalloc-die:
  # Code from module xalloc-oversized:
  # Code from module xgetcwd:
  # Code from module xsize:
  # Code from module xstrndup:
])

# This macro should be invoked from ./configure.ac, in the section
# "Check for header files, types and library functions".
AC_DEFUN([gl_INIT],
[
  AM_CONDITIONAL([GL_COND_LIBTOOL], [true])
  gl_cond_libtool=true
  gl_m4_base='m4'
  m4_pushdef([AC_LIBOBJ], m4_defn([gl_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gl_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gl_LIBSOURCES]))
  m4_pushdef([gl_LIBSOURCES_LIST], [])
  m4_pushdef([gl_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='libgnu'
changequote(,)dnl
LTALLOCA=`echo "$ALLOCA" | sed -e 's/\.[^.]* /.lo /g;s/\.[^.]*$/.lo/'`
changequote([, ])dnl
AC_SUBST([LTALLOCA])
  gl_FUNC_ALLOCA
  AC_LIBOBJ([openat-proc])
  gl_FUNC_BASE64
  gl_FUNC_CANONICALIZE_FILENAME_MODE
  gl_MODULE_INDICATOR([canonicalize])
  gl_MODULE_INDICATOR_FOR_TESTS([canonicalize])
  gl_STDLIB_MODULE_INDICATOR([canonicalize_file_name])
  AC_CHECK_FUNCS_ONCE([readlinkat])
  gl_UNISTD_MODULE_INDICATOR([chdir])
  gl_FUNC_CHDIR_LONG
  if test $gl_cv_have_arbitrary_file_name_length_limit = yes; then
    AC_LIBOBJ([chdir-long])
    gl_PREREQ_CHDIR_LONG
  fi
  gl_MODULE_INDICATOR_FOR_TESTS([cloexec])
  gl_FUNC_CLOSE
  if test $REPLACE_CLOSE = 1; then
    AC_LIBOBJ([close])
  fi
  gl_UNISTD_MODULE_INDICATOR([close])
  gl_FUNC_CLOSEDIR
  if test $HAVE_CLOSEDIR = 0 || test $REPLACE_CLOSEDIR = 1; then
    AC_LIBOBJ([closedir])
  fi
  gl_DIRENT_MODULE_INDICATOR([closedir])
  gl_CONFIGMAKE_PREP
  gl_MD4
  gl_MD5
  gl_SHA1
  gl_SHA256
  gl_SHA512
  gl_CHECK_TYPE_STRUCT_DIRENT_D_INO
  gl_CHECK_TYPE_STRUCT_DIRENT_D_TYPE
  gl_DIRENT_H
  gl_FUNC_DIRFD
  if test $ac_cv_func_dirfd = no && test $gl_cv_func_dirfd_macro = no \
     || test $REPLACE_DIRFD = 1; then
    AC_LIBOBJ([dirfd])
    gl_PREREQ_DIRFD
  fi
  gl_DIRENT_MODULE_INDICATOR([dirfd])
  gl_DIRNAME
  gl_MODULE_INDICATOR([dirname])
  gl_DIRNAME_LGPL
  gl_DOUBLE_SLASH_ROOT
  gl_FUNC_DUP
  if test $REPLACE_DUP = 1; then
    AC_LIBOBJ([dup])
    gl_PREREQ_DUP
  fi
  gl_UNISTD_MODULE_INDICATOR([dup])
  gl_FUNC_DUP2
  if test $HAVE_DUP2 = 0 || test $REPLACE_DUP2 = 1; then
    AC_LIBOBJ([dup2])
    gl_PREREQ_DUP2
  fi
  gl_UNISTD_MODULE_INDICATOR([dup2])
  gl_ENVIRON
  gl_UNISTD_MODULE_INDICATOR([environ])
  gl_HEADER_ERRNO_H
  gl_ERROR
  if test $ac_cv_lib_error_at_line = no; then
    AC_LIBOBJ([error])
    gl_PREREQ_ERROR
  fi
  m4_ifdef([AM_XGETTEXT_OPTION],
    [AM_][XGETTEXT_OPTION([--flag=error:3:c-format])
     AM_][XGETTEXT_OPTION([--flag=error_at_line:5:c-format])])
  AC_REQUIRE([gl_EXTERN_INLINE])
  gl_FUNC_FCHDIR
  gl_UNISTD_MODULE_INDICATOR([fchdir])
  gl_FUNC_FCNTL
  if test $HAVE_FCNTL = 0 || test $REPLACE_FCNTL = 1; then
    AC_LIBOBJ([fcntl])
  fi
  gl_FCNTL_MODULE_INDICATOR([fcntl])
  gl_FCNTL_H
  gl_FUNC_FDOPENDIR
  if test $HAVE_FDOPENDIR = 0 || test $REPLACE_FDOPENDIR = 1; then
    AC_LIBOBJ([fdopendir])
  fi
  gl_DIRENT_MODULE_INDICATOR([fdopendir])
  gl_MODULE_INDICATOR([fdopendir])
  gl_FILEMODE
  gl_FILE_NAME_CONCAT_LGPL
  AC_C_FLEXIBLE_ARRAY_MEMBER
  gl_FLOAT_H
  if test $REPLACE_FLOAT_LDBL = 1; then
    AC_LIBOBJ([float])
  fi
  if test $REPLACE_ITOLD = 1; then
    AC_LIBOBJ([itold])
  fi
  gl_FUNC_FNMATCH_POSIX
  if test -n "$FNMATCH_H"; then
    AC_LIBOBJ([fnmatch])
    gl_PREREQ_FNMATCH
  fi
  gl_FUNC_FREXP
  if test $gl_func_frexp != yes; then
    AC_LIBOBJ([frexp])
  fi
  gl_MATH_MODULE_INDICATOR([frexp])
  gl_FUNC_FREXPF
  if test $HAVE_FREXPF = 0 || test $REPLACE_FREXPF = 1; then
    AC_LIBOBJ([frexpf])
  fi
  gl_MATH_MODULE_INDICATOR([frexpf])
  gl_FUNC_FSEEK
  if test $REPLACE_FSEEK = 1; then
    AC_LIBOBJ([fseek])
  fi
  gl_STDIO_MODULE_INDICATOR([fseek])
  gl_FUNC_FSEEKO
  if test $HAVE_FSEEKO = 0 || test $REPLACE_FSEEKO = 1; then
    AC_LIBOBJ([fseeko])
    gl_PREREQ_FSEEKO
  fi
  gl_STDIO_MODULE_INDICATOR([fseeko])
  gl_FUNC_FSTAT
  if test $REPLACE_FSTAT = 1; then
    AC_LIBOBJ([fstat])
    gl_PREREQ_FSTAT
  fi
  gl_SYS_STAT_MODULE_INDICATOR([fstat])
  gl_FUNC_FSTATAT
  if test $HAVE_FSTATAT = 0 || test $REPLACE_FSTATAT = 1; then
    AC_LIBOBJ([fstatat])
  fi
  gl_SYS_STAT_MODULE_INDICATOR([fstatat])
  gl_FUNC_FTELL
  if test $REPLACE_FTELL = 1; then
    AC_LIBOBJ([ftell])
  fi
  gl_STDIO_MODULE_INDICATOR([ftell])
  gl_FUNC_FTELLO
  if test $HAVE_FTELLO = 0 || test $REPLACE_FTELLO = 1; then
    AC_LIBOBJ([ftello])
    gl_PREREQ_FTELLO
  fi
  gl_STDIO_MODULE_INDICATOR([ftello])
  gl_FUNC_FTRUNCATE
  if test $HAVE_FTRUNCATE = 0 || test $REPLACE_FTRUNCATE = 1; then
    AC_LIBOBJ([ftruncate])
    gl_PREREQ_FTRUNCATE
  fi
  gl_UNISTD_MODULE_INDICATOR([ftruncate])
  gl_FUNC_GETCWD
  if test $REPLACE_GETCWD = 1; then
    AC_LIBOBJ([getcwd])
    gl_PREREQ_GETCWD
  fi
  gl_MODULE_INDICATOR([getcwd])
  gl_UNISTD_MODULE_INDICATOR([getcwd])
  gl_FUNC_GETCWD_LGPL
  if test $REPLACE_GETCWD = 1; then
    AC_LIBOBJ([getcwd-lgpl])
  fi
  gl_UNISTD_MODULE_INDICATOR([getcwd])
  gl_FUNC_GETDTABLESIZE
  if test $HAVE_GETDTABLESIZE = 0 || test $REPLACE_GETDTABLESIZE = 1; then
    AC_LIBOBJ([getdtablesize])
    gl_PREREQ_GETDTABLESIZE
  fi
  gl_UNISTD_MODULE_INDICATOR([getdtablesize])
  gl_FUNC_GETHOSTNAME
  if test $HAVE_GETHOSTNAME = 0; then
    AC_LIBOBJ([gethostname])
    gl_PREREQ_GETHOSTNAME
  fi
  gl_UNISTD_MODULE_INDICATOR([gethostname])
  gl_FUNC_GETLOGIN_R
  if test $HAVE_GETLOGIN_R = 0 || test $REPLACE_GETLOGIN_R = 1; then
    AC_LIBOBJ([getlogin_r])
    gl_PREREQ_GETLOGIN_R
  fi
  gl_UNISTD_MODULE_INDICATOR([getlogin_r])
  gl_FUNC_GETOPT_GNU
  if test $REPLACE_GETOPT = 1; then
    AC_LIBOBJ([getopt])
    AC_LIBOBJ([getopt1])
    gl_PREREQ_GETOPT
    dnl Arrange for unistd.h to include getopt.h.
    GNULIB_GL_UNISTD_H_GETOPT=1
  fi
  AC_SUBST([GNULIB_GL_UNISTD_H_GETOPT])
  gl_MODULE_INDICATOR_FOR_TESTS([getopt-gnu])
  gl_FUNC_GETOPT_POSIX
  if test $REPLACE_GETOPT = 1; then
    AC_LIBOBJ([getopt])
    AC_LIBOBJ([getopt1])
    gl_PREREQ_GETOPT
    dnl Arrange for unistd.h to include getopt.h.
    GNULIB_GL_UNISTD_H_GETOPT=1
  fi
  AC_SUBST([GNULIB_GL_UNISTD_H_GETOPT])
  gl_FUNC_GETPROGNAME
  gl_FUNC_GETRUSAGE
  if test $HAVE_GETRUSAGE = 0; then
    AC_LIBOBJ([getrusage])
  fi
  gl_SYS_RESOURCE_MODULE_INDICATOR([getrusage])
  AC_SUBST([LIBINTL])
  AC_SUBST([LTLIBINTL])
  gl_FUNC_GETTIMEOFDAY
  if test $HAVE_GETTIMEOFDAY = 0 || test $REPLACE_GETTIMEOFDAY = 1; then
    AC_LIBOBJ([gettimeofday])
    gl_PREREQ_GETTIMEOFDAY
  fi
  gl_SYS_TIME_MODULE_INDICATOR([gettimeofday])
  gl_GLOB
  if test -n "$GLOB_H"; then
    AC_LIBOBJ([glob])
    gl_PREREQ_GLOB
  fi
  gl_HARD_LOCALE
  gl_FUNC_ISATTY
  if test $REPLACE_ISATTY = 1; then
    AC_LIBOBJ([isatty])
    gl_PREREQ_ISATTY
  fi
  gl_UNISTD_MODULE_INDICATOR([isatty])
  gl_FUNC_ISNAND_NO_LIBM
  if test $gl_func_isnand_no_libm != yes; then
    AC_LIBOBJ([isnand])
    gl_PREREQ_ISNAND
  fi
  AC_REQUIRE([gl_LARGEFILE])
  gl_LIMITS_H
  gl_FUNC_LINK
  if test $HAVE_LINK = 0 || test $REPLACE_LINK = 1; then
    AC_LIBOBJ([link])
  fi
  gl_UNISTD_MODULE_INDICATOR([link])
  gl_LOCALCHARSET
  LOCALCHARSET_TESTS_ENVIRONMENT="CHARSETALIASDIR=\"\$(abs_top_builddir)/$gl_source_base\""
  AC_SUBST([LOCALCHARSET_TESTS_ENVIRONMENT])
  gl_LOCK
  gl_MODULE_INDICATOR([lock])
  gl_FUNC_LSEEK
  if test $REPLACE_LSEEK = 1; then
    AC_LIBOBJ([lseek])
  fi
  gl_UNISTD_MODULE_INDICATOR([lseek])
  gl_FUNC_LSTAT
  if test $REPLACE_LSTAT = 1; then
    AC_LIBOBJ([lstat])
    gl_PREREQ_LSTAT
  fi
  gl_SYS_STAT_MODULE_INDICATOR([lstat])
  gl_FUNC_MALLOC_GNU
  if test $REPLACE_MALLOC = 1; then
    AC_LIBOBJ([malloc])
  fi
  gl_MODULE_INDICATOR([malloc-gnu])
  gl_FUNC_MALLOC_POSIX
  if test $REPLACE_MALLOC = 1; then
    AC_LIBOBJ([malloc])
  fi
  gl_STDLIB_MODULE_INDICATOR([malloc-posix])
  gl_MALLOCA
  gl_MATH_H
  gl_FUNC_MBRTOWC
  if test $HAVE_MBRTOWC = 0 || test $REPLACE_MBRTOWC = 1; then
    AC_LIBOBJ([mbrtowc])
    gl_PREREQ_MBRTOWC
  fi
  gl_WCHAR_MODULE_INDICATOR([mbrtowc])
  gl_FUNC_MBSINIT
  if test $HAVE_MBSINIT = 0 || test $REPLACE_MBSINIT = 1; then
    AC_LIBOBJ([mbsinit])
    gl_PREREQ_MBSINIT
  fi
  gl_WCHAR_MODULE_INDICATOR([mbsinit])
  gl_FUNC_MBSRTOWCS
  if test $HAVE_MBSRTOWCS = 0 || test $REPLACE_MBSRTOWCS = 1; then
    AC_LIBOBJ([mbsrtowcs])
    AC_LIBOBJ([mbsrtowcs-state])
    gl_PREREQ_MBSRTOWCS
  fi
  gl_WCHAR_MODULE_INDICATOR([mbsrtowcs])
  gl_FUNC_MEMCHR
  if test $HAVE_MEMCHR = 0 || test $REPLACE_MEMCHR = 1; then
    AC_LIBOBJ([memchr])
    gl_PREREQ_MEMCHR
  fi
  gl_STRING_MODULE_INDICATOR([memchr])
  gl_FUNC_MEMPCPY
  if test $HAVE_MEMPCPY = 0; then
    AC_LIBOBJ([mempcpy])
    gl_PREREQ_MEMPCPY
  fi
  gl_STRING_MODULE_INDICATOR([mempcpy])
  gl_FUNC_MEMRCHR
  if test $ac_cv_func_memrchr = no; then
    AC_LIBOBJ([memrchr])
    gl_PREREQ_MEMRCHR
  fi
  gl_STRING_MODULE_INDICATOR([memrchr])
  gl_MINMAX
  gl_FUNC_MKDIR
  if test $REPLACE_MKDIR = 1; then
    AC_LIBOBJ([mkdir])
  fi
  gl_FUNC_MKFIFO
  if test $HAVE_MKFIFO = 0 || test $REPLACE_MKFIFO = 1; then
    AC_LIBOBJ([mkfifo])
  fi
  gl_UNISTD_MODULE_INDICATOR([mkfifo])
  gl_FUNC_MKOSTEMP
  if test $HAVE_MKOSTEMP = 0; then
    AC_LIBOBJ([mkostemp])
    gl_PREREQ_MKOSTEMP
  fi
  gl_MODULE_INDICATOR([mkostemp])
  gl_STDLIB_MODULE_INDICATOR([mkostemp])
  gl_FUNC_MKTIME
  if test $REPLACE_MKTIME = 1; then
    AC_LIBOBJ([mktime])
    gl_PREREQ_MKTIME
  fi
  gl_TIME_MODULE_INDICATOR([mktime])
  gl_FUNC_MKTIME_INTERNAL
  if test $REPLACE_MKTIME = 1; then
    AC_LIBOBJ([mktime])
    gl_PREREQ_MKTIME
  fi
  AC_REQUIRE([gl_MSVC_INVAL])
  if test $HAVE_MSVC_INVALID_PARAMETER_HANDLER = 1; then
    AC_LIBOBJ([msvc-inval])
  fi
  AC_REQUIRE([gl_MSVC_NOTHROW])
  if test $HAVE_MSVC_INVALID_PARAMETER_HANDLER = 1; then
    AC_LIBOBJ([msvc-nothrow])
  fi
  gl_MULTIARCH
  gl_FUNC_NANOSLEEP
  if test $HAVE_NANOSLEEP = 0 || test $REPLACE_NANOSLEEP = 1; then
    AC_LIBOBJ([nanosleep])
    gl_PREREQ_NANOSLEEP
  fi
  gl_TIME_MODULE_INDICATOR([nanosleep])
  gl_NPROC
  gl_FUNC_OPEN
  if test $REPLACE_OPEN = 1; then
    AC_LIBOBJ([open])
    gl_PREREQ_OPEN
  fi
  gl_FCNTL_MODULE_INDICATOR([open])
  gl_FUNC_OPENAT
  if test $HAVE_OPENAT = 0 || test $REPLACE_OPENAT = 1; then
    AC_LIBOBJ([openat])
    gl_PREREQ_OPENAT
  fi
  gl_MODULE_INDICATOR([openat]) dnl for lib/getcwd.c
  gl_FCNTL_MODULE_INDICATOR([openat])
  gl_FUNC_OPENDIR
  if test $HAVE_OPENDIR = 0 || test $REPLACE_OPENDIR = 1; then
    AC_LIBOBJ([opendir])
  fi
  gl_DIRENT_MODULE_INDICATOR([opendir])
  gl_PATHMAX
  gl_FUNC_PIPE
  if test $HAVE_PIPE = 0; then
    AC_LIBOBJ([pipe])
  fi
  gl_UNISTD_MODULE_INDICATOR([pipe])
  AC_CHECK_DECLS([program_invocation_name], [], [], [#include <errno.h>])
  AC_CHECK_DECLS([program_invocation_short_name], [], [], [#include <errno.h>])
  gl_FUNC_PUTENV
  if test $REPLACE_PUTENV = 1; then
    AC_LIBOBJ([putenv])
    gl_PREREQ_PUTENV
  fi
  gl_STDLIB_MODULE_INDICATOR([putenv])
  gl_FUNC_RAISE
  if test $HAVE_RAISE = 0 || test $REPLACE_RAISE = 1; then
    AC_LIBOBJ([raise])
    gl_PREREQ_RAISE
  fi
  gl_SIGNAL_MODULE_INDICATOR([raise])
  gl_FUNC_READDIR
  if test $HAVE_READDIR = 0; then
    AC_LIBOBJ([readdir])
  fi
  gl_DIRENT_MODULE_INDICATOR([readdir])
  gl_FUNC_READLINK
  if test $HAVE_READLINK = 0 || test $REPLACE_READLINK = 1; then
    AC_LIBOBJ([readlink])
    gl_PREREQ_READLINK
  fi
  gl_UNISTD_MODULE_INDICATOR([readlink])
  gl_FUNC_REALLOC_POSIX
  if test $REPLACE_REALLOC = 1; then
    AC_LIBOBJ([realloc])
  fi
  gl_STDLIB_MODULE_INDICATOR([realloc-posix])
  gl_FUNC_REWINDDIR
  if test $HAVE_REWINDDIR = 0; then
    AC_LIBOBJ([rewinddir])
  fi
  gl_DIRENT_MODULE_INDICATOR([rewinddir])
  gl_FUNC_RMDIR
  if test $REPLACE_RMDIR = 1; then
    AC_LIBOBJ([rmdir])
  fi
  gl_UNISTD_MODULE_INDICATOR([rmdir])
  gl_SAME
  gl_SAVE_CWD
  gl_FUNC_SECURE_GETENV
  if test $HAVE_SECURE_GETENV = 0; then
    AC_LIBOBJ([secure_getenv])
    gl_PREREQ_SECURE_GETENV
  fi
  gl_STDLIB_MODULE_INDICATOR([secure_getenv])
  gl_FUNC_SELECT
  if test $REPLACE_SELECT = 1; then
    AC_LIBOBJ([select])
  fi
  gl_SYS_SELECT_MODULE_INDICATOR([select])
  gl_FUNC_SETENV
  if test $HAVE_SETENV = 0 || test $REPLACE_SETENV = 1; then
    AC_LIBOBJ([setenv])
  fi
  gl_STDLIB_MODULE_INDICATOR([setenv])
  gl_SIGACTION
  if test $HAVE_SIGACTION = 0; then
    AC_LIBOBJ([sigaction])
    gl_PREREQ_SIGACTION
  fi
  gl_SIGNAL_MODULE_INDICATOR([sigaction])
  gl_SIGNAL_H
  gl_SIGNALBLOCKING
  if test $HAVE_POSIX_SIGNALBLOCKING = 0; then
    AC_LIBOBJ([sigprocmask])
    gl_PREREQ_SIGPROCMASK
  fi
  gl_SIGNAL_MODULE_INDICATOR([sigprocmask])
  gl_SIZE_MAX
  gl_FUNC_SNPRINTF
  gl_STDIO_MODULE_INDICATOR([snprintf])
  gl_MODULE_INDICATOR([snprintf])
  AC_REQUIRE([gl_SOCKETLIB])
  AC_REQUIRE([gl_SOCKETS])
  gl_TYPE_SOCKLEN_T
  gt_TYPE_SSIZE_T
  gl_FUNC_STAT
  if test $REPLACE_STAT = 1; then
    AC_LIBOBJ([stat])
    gl_PREREQ_STAT
  fi
  gl_SYS_STAT_MODULE_INDICATOR([stat])
  gl_STDALIGN_H
  AM_STDBOOL_H
  gl_STDDEF_H
  gl_STDINT_H
  gl_STDIO_H
  gl_STDLIB_H
  gl_STRCASE
  if test $HAVE_STRCASECMP = 0; then
    AC_LIBOBJ([strcasecmp])
    gl_PREREQ_STRCASECMP
  fi
  if test $HAVE_STRNCASECMP = 0; then
    AC_LIBOBJ([strncasecmp])
    gl_PREREQ_STRNCASECMP
  fi
  gl_FUNC_STRDUP
  if test $ac_cv_func_strdup = no; then
    AC_LIBOBJ([strdup])
    gl_PREREQ_STRDUP
  fi
  gl_STRING_MODULE_INDICATOR([strdup])
  gl_FUNC_STRDUP_POSIX
  if test $ac_cv_func_strdup = no || test $REPLACE_STRDUP = 1; then
    AC_LIBOBJ([strdup])
    gl_PREREQ_STRDUP
  fi
  gl_STRING_MODULE_INDICATOR([strdup])
  gl_FUNC_STRERROR
  if test $REPLACE_STRERROR = 1; then
    AC_LIBOBJ([strerror])
  fi
  gl_MODULE_INDICATOR([strerror])
  gl_STRING_MODULE_INDICATOR([strerror])
  AC_REQUIRE([gl_HEADER_ERRNO_H])
  AC_REQUIRE([gl_FUNC_STRERROR_0])
  if test -n "$ERRNO_H" || test $REPLACE_STRERROR_0 = 1; then
    AC_LIBOBJ([strerror-override])
    gl_PREREQ_SYS_H_WINSOCK2
  fi
  gl_FUNC_GNU_STRFTIME
  gl_HEADER_STRING_H
  gl_HEADER_STRINGS_H
  gl_FUNC_STRNDUP
  if test $HAVE_STRNDUP = 0 || test $REPLACE_STRNDUP = 1; then
    AC_LIBOBJ([strndup])
  fi
  gl_STRING_MODULE_INDICATOR([strndup])
  gl_FUNC_STRNLEN
  if test $HAVE_DECL_STRNLEN = 0 || test $REPLACE_STRNLEN = 1; then
    AC_LIBOBJ([strnlen])
    gl_PREREQ_STRNLEN
  fi
  gl_STRING_MODULE_INDICATOR([strnlen])
  gl_FUNC_STRPTIME
  if test $HAVE_STRPTIME = 0; then
    AC_LIBOBJ([strptime])
    gl_PREREQ_STRPTIME
  fi
  gl_TIME_MODULE_INDICATOR([strptime])
  gl_FUNC_STRSIGNAL
  if test $HAVE_STRSIGNAL = 0 || test $REPLACE_STRSIGNAL = 1; then
    AC_LIBOBJ([strsignal])
    gl_PREREQ_STRSIGNAL
  fi
  gl_STRING_MODULE_INDICATOR([strsignal])
  gl_FUNC_SYMLINK
  if test $HAVE_SYMLINK = 0 || test $REPLACE_SYMLINK = 1; then
    AC_LIBOBJ([symlink])
  fi
  gl_UNISTD_MODULE_INDICATOR([symlink])
  gl_HEADER_SYS_RESOURCE
  AC_PROG_MKDIR_P
  gl_HEADER_SYS_SELECT
  AC_PROG_MKDIR_P
  AC_REQUIRE([gl_HEADER_SYS_SOCKET])
  AC_PROG_MKDIR_P
  gl_HEADER_SYS_STAT_H
  AC_PROG_MKDIR_P
  gl_HEADER_SYS_TIME_H
  AC_PROG_MKDIR_P
  gl_SYS_TIMES_H
  AC_PROG_MKDIR_P
  gl_SYS_TYPES_H
  AC_PROG_MKDIR_P
  gl_HEADER_SYS_UIO
  AC_PROG_MKDIR_P
  gl_SYS_UTSNAME_H
  AC_PROG_MKDIR_P
  gl_SYS_WAIT_H
  AC_PROG_MKDIR_P
  gl_FUNC_GEN_TEMPNAME
  gl_THREADLIB
  gl_HEADER_TIME_H
  gl_TIME_R
  if test $HAVE_LOCALTIME_R = 0 || test $REPLACE_LOCALTIME_R = 1; then
    AC_LIBOBJ([time_r])
    gl_PREREQ_TIME_R
  fi
  gl_TIME_MODULE_INDICATOR([time_r])
  gl_TIME_RZ
  if test "$HAVE_TIMEZONE_T" = 0; then
    AC_LIBOBJ([time_rz])
  fi
  gl_TIME_MODULE_INDICATOR([time_rz])
  gl_FUNC_TIMEGM
  if test $HAVE_TIMEGM = 0 || test $REPLACE_TIMEGM = 1; then
    AC_LIBOBJ([timegm])
    gl_PREREQ_TIMEGM
  fi
  gl_TIME_MODULE_INDICATOR([timegm])
  gl_TLS
  gt_TMPDIR
  gl_FUNC_TMPFILE
  if test $REPLACE_TMPFILE = 1; then
    AC_LIBOBJ([tmpfile])
    gl_PREREQ_TMPFILE
  fi
  gl_STDIO_MODULE_INDICATOR([tmpfile])
  gl_FUNC_UNAME
  if test $HAVE_UNAME = 0; then
    AC_LIBOBJ([uname])
    gl_PREREQ_UNAME
  fi
  gl_SYS_UTSNAME_MODULE_INDICATOR([uname])
  gl_UNISTD_H
  gl_UNISTD_SAFER
  gl_FUNC_UNLINK
  if test $REPLACE_UNLINK = 1; then
    AC_LIBOBJ([unlink])
  fi
  gl_UNISTD_MODULE_INDICATOR([unlink])
  gl_FUNC_UNSETENV
  if test $HAVE_UNSETENV = 0 || test $REPLACE_UNSETENV = 1; then
    AC_LIBOBJ([unsetenv])
    gl_PREREQ_UNSETENV
  fi
  gl_STDLIB_MODULE_INDICATOR([unsetenv])
  gl_FUNC_VASNPRINTF
  gl_FUNC_VASPRINTF
  gl_STDIO_MODULE_INDICATOR([vasprintf])
  m4_ifdef([AM_XGETTEXT_OPTION],
    [AM_][XGETTEXT_OPTION([--flag=asprintf:2:c-format])
     AM_][XGETTEXT_OPTION([--flag=vasprintf:2:c-format])])
  gl_FUNC_WAITPID
  if test $HAVE_WAITPID = 0; then
    AC_LIBOBJ([waitpid])
  fi
  gl_SYS_WAIT_MODULE_INDICATOR([waitpid])
  gl_WCHAR_H
  gl_WCTYPE_H
  gl_XALLOC
  gl_XGETCWD
  gl_XSIZE
  gl_XSTRNDUP
  # End of code from modules
  m4_ifval(gl_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gl_LIBSOURCES_DIR])[ ||
      for gl_file in ]gl_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gl_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gl_LIBSOURCES_DIR])
  m4_popdef([gl_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gl_libobjs=
    gl_ltlibobjs=
    if test -n "$gl_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gl_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gl_libobjs="$gl_libobjs $i.$ac_objext"
        gl_ltlibobjs="$gl_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gl_LIBOBJS], [$gl_libobjs])
    AC_SUBST([gl_LTLIBOBJS], [$gl_ltlibobjs])
  ])
  gltests_libdeps=
  gltests_ltlibdeps=
  m4_pushdef([AC_LIBOBJ], m4_defn([gltests_LIBOBJ]))
  m4_pushdef([AC_REPLACE_FUNCS], m4_defn([gltests_REPLACE_FUNCS]))
  m4_pushdef([AC_LIBSOURCES], m4_defn([gltests_LIBSOURCES]))
  m4_pushdef([gltests_LIBSOURCES_LIST], [])
  m4_pushdef([gltests_LIBSOURCES_DIR], [])
  gl_COMMON
  gl_source_base='tests'
changequote(,)dnl
  gltests_WITNESS=IN_`echo "${PACKAGE-$PACKAGE_TARNAME}" | LC_ALL=C tr abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ | LC_ALL=C sed -e 's/[^A-Z0-9_]/_/g'`_GNULIB_TESTS
changequote([, ])dnl
  AC_SUBST([gltests_WITNESS])
  gl_module_indicator_condition=$gltests_WITNESS
  m4_pushdef([gl_MODULE_INDICATOR_CONDITION], [$gl_module_indicator_condition])
  m4_popdef([gl_MODULE_INDICATOR_CONDITION])
  m4_ifval(gltests_LIBSOURCES_LIST, [
    m4_syscmd([test ! -d ]m4_defn([gltests_LIBSOURCES_DIR])[ ||
      for gl_file in ]gltests_LIBSOURCES_LIST[ ; do
        if test ! -r ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file ; then
          echo "missing file ]m4_defn([gltests_LIBSOURCES_DIR])[/$gl_file" >&2
          exit 1
        fi
      done])dnl
      m4_if(m4_sysval, [0], [],
        [AC_FATAL([expected source file, required through AC_LIBSOURCES, not found])])
  ])
  m4_popdef([gltests_LIBSOURCES_DIR])
  m4_popdef([gltests_LIBSOURCES_LIST])
  m4_popdef([AC_LIBSOURCES])
  m4_popdef([AC_REPLACE_FUNCS])
  m4_popdef([AC_LIBOBJ])
  AC_CONFIG_COMMANDS_PRE([
    gltests_libobjs=
    gltests_ltlibobjs=
    if test -n "$gltests_LIBOBJS"; then
      # Remove the extension.
      sed_drop_objext='s/\.o$//;s/\.obj$//'
      for i in `for i in $gltests_LIBOBJS; do echo "$i"; done | sed -e "$sed_drop_objext" | sort | uniq`; do
        gltests_libobjs="$gltests_libobjs $i.$ac_objext"
        gltests_ltlibobjs="$gltests_ltlibobjs $i.lo"
      done
    fi
    AC_SUBST([gltests_LIBOBJS], [$gltests_libobjs])
    AC_SUBST([gltests_LTLIBOBJS], [$gltests_ltlibobjs])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_LIBOBJ], [
  AS_LITERAL_IF([$1], [gl_LIBSOURCES([$1.c])])dnl
  gl_LIBOBJS="$gl_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gl_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gl_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gl_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gl_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gl_LIBSOURCES_DIR], [libgnu])
      m4_append([gl_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# Like AC_LIBOBJ, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_LIBOBJ], [
  AS_LITERAL_IF([$1], [gltests_LIBSOURCES([$1.c])])dnl
  gltests_LIBOBJS="$gltests_LIBOBJS $1.$ac_objext"
])

# Like AC_REPLACE_FUNCS, except that the module name goes
# into gltests_LIBOBJS instead of into LIBOBJS.
AC_DEFUN([gltests_REPLACE_FUNCS], [
  m4_foreach_w([gl_NAME], [$1], [AC_LIBSOURCES(gl_NAME[.c])])dnl
  AC_CHECK_FUNCS([$1], , [gltests_LIBOBJ($ac_func)])
])

# Like AC_LIBSOURCES, except the directory where the source file is
# expected is derived from the gnulib-tool parameterization,
# and alloca is special cased (for the alloca-opt module).
# We could also entirely rely on EXTRA_lib..._SOURCES.
AC_DEFUN([gltests_LIBSOURCES], [
  m4_foreach([_gl_NAME], [$1], [
    m4_if(_gl_NAME, [alloca.c], [], [
      m4_define([gltests_LIBSOURCES_DIR], [tests])
      m4_append([gltests_LIBSOURCES_LIST], _gl_NAME, [ ])
    ])
  ])
])

# This macro records the list of files which have been installed by
# gnulib-tool and may be removed by future gnulib-tool invocations.
AC_DEFUN([gl_FILE_LIST], [
  build-aux/config.rpath
  build-aux/snippet/_Noreturn.h
  build-aux/snippet/arg-nonnull.h
  build-aux/snippet/c++defs.h
  build-aux/snippet/warn-on-use.h
  lib/alloca.c
  lib/alloca.in.h
  lib/allocator.c
  lib/allocator.h
  lib/areadlink-with-size.c
  lib/areadlink.c
  lib/areadlink.h
  lib/asnprintf.c
  lib/asprintf.c
  lib/assure.h
  lib/at-func.c
  lib/base64.c
  lib/base64.h
  lib/basename-lgpl.c
  lib/basename.c
  lib/bitrotate.c
  lib/bitrotate.h
  lib/c-ctype.c
  lib/c-ctype.h
  lib/canonicalize.c
  lib/canonicalize.h
  lib/careadlinkat.c
  lib/careadlinkat.h
  lib/chdir-long.c
  lib/chdir-long.h
  lib/cloexec.c
  lib/cloexec.h
  lib/close.c
  lib/closedir.c
  lib/config.charset
  lib/dirent-private.h
  lib/dirent.in.h
  lib/dirfd.c
  lib/dirname-lgpl.c
  lib/dirname.c
  lib/dirname.h
  lib/dosname.h
  lib/dup-safer.c
  lib/dup.c
  lib/dup2.c
  lib/errno.in.h
  lib/error.c
  lib/error.h
  lib/exitfail.c
  lib/exitfail.h
  lib/fchdir.c
  lib/fcntl.c
  lib/fcntl.in.h
  lib/fd-hook.c
  lib/fd-hook.h
  lib/fd-safer.c
  lib/fdopendir.c
  lib/file-set.c
  lib/file-set.h
  lib/filemode.c
  lib/filemode.h
  lib/filename.h
  lib/filenamecat-lgpl.c
  lib/filenamecat.h
  lib/flexmember.h
  lib/float+.h
  lib/float.c
  lib/float.in.h
  lib/fnmatch.c
  lib/fnmatch.in.h
  lib/fnmatch_loop.c
  lib/fpucw.h
  lib/frexp.c
  lib/frexpf.c
  lib/fseek.c
  lib/fseeko.c
  lib/fstat.c
  lib/fstatat.c
  lib/ftell.c
  lib/ftello.c
  lib/ftruncate.c
  lib/getcwd-lgpl.c
  lib/getcwd.c
  lib/getdtablesize.c
  lib/gethostname.c
  lib/getlogin_r.c
  lib/getopt.c
  lib/getopt.in.h
  lib/getopt1.c
  lib/getopt_int.h
  lib/getprogname.c
  lib/getprogname.h
  lib/getrusage.c
  lib/gettext.h
  lib/gettimeofday.c
  lib/gl_openssl.h
  lib/glob-libc.h
  lib/glob.c
  lib/glob.in.h
  lib/glthread/lock.c
  lib/glthread/lock.h
  lib/glthread/threadlib.c
  lib/glthread/tls.c
  lib/glthread/tls.h
  lib/hard-locale.c
  lib/hard-locale.h
  lib/hash-pjw.c
  lib/hash-pjw.h
  lib/hash-triple.c
  lib/hash-triple.h
  lib/hash.c
  lib/hash.h
  lib/intprops.h
  lib/isatty.c
  lib/isnan.c
  lib/isnand-nolibm.h
  lib/isnand.c
  lib/itold.c
  lib/limits.in.h
  lib/link.c
  lib/localcharset.c
  lib/localcharset.h
  lib/lseek.c
  lib/lstat.c
  lib/malloc.c
  lib/malloca.c
  lib/malloca.h
  lib/malloca.valgrind
  lib/math.c
  lib/math.in.h
  lib/mbrtowc.c
  lib/mbsinit.c
  lib/mbsrtowcs-impl.h
  lib/mbsrtowcs-state.c
  lib/mbsrtowcs.c
  lib/md2.c
  lib/md2.h
  lib/md4.c
  lib/md4.h
  lib/md5.c
  lib/md5.h
  lib/memchr.c
  lib/memchr.valgrind
  lib/mempcpy.c
  lib/memrchr.c
  lib/minmax.h
  lib/mkdir.c
  lib/mkfifo.c
  lib/mkostemp.c
  lib/mktime-internal.h
  lib/mktime.c
  lib/msvc-inval.c
  lib/msvc-inval.h
  lib/msvc-nothrow.c
  lib/msvc-nothrow.h
  lib/nanosleep.c
  lib/nproc.c
  lib/nproc.h
  lib/open.c
  lib/openat-die.c
  lib/openat-priv.h
  lib/openat-proc.c
  lib/openat.c
  lib/openat.h
  lib/opendir.c
  lib/pathmax.h
  lib/pipe-safer.c
  lib/pipe.c
  lib/printf-args.c
  lib/printf-args.h
  lib/printf-parse.c
  lib/printf-parse.h
  lib/progname.c
  lib/progname.h
  lib/putenv.c
  lib/raise.c
  lib/readdir.c
  lib/readlink.c
  lib/realloc.c
  lib/ref-add.sin
  lib/ref-del.sin
  lib/rewinddir.c
  lib/rmdir.c
  lib/same-inode.h
  lib/same.c
  lib/same.h
  lib/save-cwd.c
  lib/save-cwd.h
  lib/secure_getenv.c
  lib/select.c
  lib/setenv.c
  lib/sha1.c
  lib/sha1.h
  lib/sha256.c
  lib/sha256.h
  lib/sha512.c
  lib/sha512.h
  lib/sig-handler.c
  lib/sig-handler.h
  lib/sigaction.c
  lib/siglist.h
  lib/signal.in.h
  lib/sigprocmask.c
  lib/size_max.h
  lib/snprintf.c
  lib/sockets.c
  lib/sockets.h
  lib/stat.c
  lib/stdalign.in.h
  lib/stdbool.in.h
  lib/stddef.in.h
  lib/stdint.in.h
  lib/stdio-impl.h
  lib/stdio.in.h
  lib/stdlib.in.h
  lib/strcasecmp.c
  lib/strdup.c
  lib/streq.h
  lib/strerror-override.c
  lib/strerror-override.h
  lib/strerror.c
  lib/strftime.c
  lib/strftime.h
  lib/string.in.h
  lib/strings.in.h
  lib/stripslash.c
  lib/strncasecmp.c
  lib/strndup.c
  lib/strnlen.c
  lib/strnlen1.c
  lib/strnlen1.h
  lib/strptime.c
  lib/strsignal.c
  lib/symlink.c
  lib/sys_resource.in.h
  lib/sys_select.in.h
  lib/sys_socket.c
  lib/sys_socket.in.h
  lib/sys_stat.in.h
  lib/sys_time.in.h
  lib/sys_times.in.h
  lib/sys_types.in.h
  lib/sys_uio.in.h
  lib/sys_utsname.in.h
  lib/sys_wait.in.h
  lib/tempname.c
  lib/tempname.h
  lib/time-internal.h
  lib/time.in.h
  lib/time_r.c
  lib/time_rz.c
  lib/timegm.c
  lib/tmpdir.c
  lib/tmpdir.h
  lib/tmpfile.c
  lib/u64.c
  lib/u64.h
  lib/uname.c
  lib/unistd--.h
  lib/unistd-safer.h
  lib/unistd.c
  lib/unistd.in.h
  lib/unlink.c
  lib/unsetenv.c
  lib/vasnprintf.c
  lib/vasnprintf.h
  lib/vasprintf.c
  lib/verify.h
  lib/w32sock.h
  lib/waitpid.c
  lib/wchar.in.h
  lib/wctype-h.c
  lib/wctype.in.h
  lib/xalloc-die.c
  lib/xalloc-oversized.h
  lib/xalloc.h
  lib/xgetcwd.c
  lib/xgetcwd.h
  lib/xmalloc.c
  lib/xsize.c
  lib/xsize.h
  lib/xstrndup.c
  lib/xstrndup.h
  m4/00gnulib.m4
  m4/absolute-header.m4
  m4/alloca.m4
  m4/base64.m4
  m4/canonicalize.m4
  m4/chdir-long.m4
  m4/close.m4
  m4/closedir.m4
  m4/codeset.m4
  m4/configmake.m4
  m4/d-ino.m4
  m4/d-type.m4
  m4/dirent_h.m4
  m4/dirfd.m4
  m4/dirname.m4
  m4/double-slash-root.m4
  m4/dup.m4
  m4/dup2.m4
  m4/eealloc.m4
  m4/environ.m4
  m4/errno_h.m4
  m4/error.m4
  m4/exponentd.m4
  m4/extensions.m4
  m4/extern-inline.m4
  m4/fchdir.m4
  m4/fcntl-o.m4
  m4/fcntl.m4
  m4/fcntl_h.m4
  m4/fdopendir.m4
  m4/filemode.m4
  m4/filenamecat.m4
  m4/flexmember.m4
  m4/float_h.m4
  m4/fnmatch.m4
  m4/fpieee.m4
  m4/frexp.m4
  m4/frexpf.m4
  m4/fseek.m4
  m4/fseeko.m4
  m4/fstat.m4
  m4/fstatat.m4
  m4/ftell.m4
  m4/ftello.m4
  m4/ftruncate.m4
  m4/getcwd-abort-bug.m4
  m4/getcwd-path-max.m4
  m4/getcwd.m4
  m4/getdtablesize.m4
  m4/gethostname.m4
  m4/getlogin_r.m4
  m4/getopt.m4
  m4/getprogname.m4
  m4/getrusage.m4
  m4/gettimeofday.m4
  m4/gl-openssl.m4
  m4/glibc21.m4
  m4/glob.m4
  m4/gnulib-common.m4
  m4/hard-locale.m4
  m4/include_next.m4
  m4/intmax_t.m4
  m4/inttypes_h.m4
  m4/isatty.m4
  m4/isnand.m4
  m4/largefile.m4
  m4/lib-ld.m4
  m4/lib-link.m4
  m4/lib-prefix.m4
  m4/limits-h.m4
  m4/link.m4
  m4/localcharset.m4
  m4/locale-fr.m4
  m4/locale-ja.m4
  m4/locale-zh.m4
  m4/lock.m4
  m4/longlong.m4
  m4/lseek.m4
  m4/lstat.m4
  m4/malloc.m4
  m4/malloca.m4
  m4/math_h.m4
  m4/mathfunc.m4
  m4/mbrtowc.m4
  m4/mbsinit.m4
  m4/mbsrtowcs.m4
  m4/mbstate_t.m4
  m4/md4.m4
  m4/md5.m4
  m4/memchr.m4
  m4/mempcpy.m4
  m4/memrchr.m4
  m4/minmax.m4
  m4/mkdir.m4
  m4/mkfifo.m4
  m4/mkostemp.m4
  m4/mktime.m4
  m4/mmap-anon.m4
  m4/mode_t.m4
  m4/msvc-inval.m4
  m4/msvc-nothrow.m4
  m4/multiarch.m4
  m4/nanosleep.m4
  m4/nocrash.m4
  m4/nproc.m4
  m4/off_t.m4
  m4/open.m4
  m4/openat.m4
  m4/opendir.m4
  m4/pathmax.m4
  m4/pipe.m4
  m4/printf.m4
  m4/putenv.m4
  m4/raise.m4
  m4/readdir.m4
  m4/readlink.m4
  m4/realloc.m4
  m4/rewinddir.m4
  m4/rmdir.m4
  m4/same.m4
  m4/save-cwd.m4
  m4/secure_getenv.m4
  m4/select.m4
  m4/setenv.m4
  m4/sha1.m4
  m4/sha256.m4
  m4/sha512.m4
  m4/sigaction.m4
  m4/signal_h.m4
  m4/signalblocking.m4
  m4/size_max.m4
  m4/snprintf.m4
  m4/socketlib.m4
  m4/sockets.m4
  m4/socklen.m4
  m4/sockpfaf.m4
  m4/ssize_t.m4
  m4/st_dm_mode.m4
  m4/stat.m4
  m4/std-gnu11.m4
  m4/stdalign.m4
  m4/stdbool.m4
  m4/stddef_h.m4
  m4/stdint.m4
  m4/stdint_h.m4
  m4/stdio_h.m4
  m4/stdlib_h.m4
  m4/strcase.m4
  m4/strdup.m4
  m4/strerror.m4
  m4/strftime.m4
  m4/string_h.m4
  m4/strings_h.m4
  m4/strndup.m4
  m4/strnlen.m4
  m4/strptime.m4
  m4/strsignal.m4
  m4/symlink.m4
  m4/sys_resource_h.m4
  m4/sys_select_h.m4
  m4/sys_socket_h.m4
  m4/sys_stat_h.m4
  m4/sys_time_h.m4
  m4/sys_times_h.m4
  m4/sys_types_h.m4
  m4/sys_uio_h.m4
  m4/sys_utsname_h.m4
  m4/sys_wait_h.m4
  m4/tempname.m4
  m4/threadlib.m4
  m4/time_h.m4
  m4/time_r.m4
  m4/time_rz.m4
  m4/timegm.m4
  m4/tls.m4
  m4/tm_gmtoff.m4
  m4/tmpdir.m4
  m4/tmpfile.m4
  m4/uname.m4
  m4/unistd-safer.m4
  m4/unistd_h.m4
  m4/unlink.m4
  m4/vasnprintf.m4
  m4/vasprintf.m4
  m4/waitpid.m4
  m4/warn-on-use.m4
  m4/wchar_h.m4
  m4/wchar_t.m4
  m4/wctype_h.m4
  m4/wint_t.m4
  m4/xalloc.m4
  m4/xgetcwd.m4
  m4/xsize.m4
  m4/xstrndup.m4
])
