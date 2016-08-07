FCN_FILE_DIRS += \
  scripts/miscellaneous \
  scripts/miscellaneous/private

scripts_miscellaneous_PRIVATE_FCN_FILES = \
  scripts/miscellaneous/private/display_info_file.m \
  scripts/miscellaneous/private/__w2mpth__.m

scripts_miscellaneous_FCN_FILES = \
  scripts/miscellaneous/bug_report.m \
  scripts/miscellaneous/bunzip2.m \
  scripts/miscellaneous/cast.m \
  scripts/miscellaneous/citation.m \
  scripts/miscellaneous/compare_versions.m \
  scripts/miscellaneous/computer.m \
  scripts/miscellaneous/copyfile.m \
  scripts/miscellaneous/debug.m \
  scripts/miscellaneous/delete.m \
  scripts/miscellaneous/desktop.m \
  scripts/miscellaneous/dir.m \
  scripts/miscellaneous/dos.m \
  scripts/miscellaneous/edit.m \
  scripts/miscellaneous/fact.m \
  scripts/miscellaneous/fileattrib.m \
  scripts/miscellaneous/fileparts.m \
  scripts/miscellaneous/fullfile.m \
  scripts/miscellaneous/genvarname.m \
  scripts/miscellaneous/getappdata.m \
  scripts/miscellaneous/getfield.m \
  scripts/miscellaneous/gunzip.m \
  scripts/miscellaneous/info.m \
  scripts/miscellaneous/inputname.m \
  scripts/miscellaneous/isappdata.m \
  scripts/miscellaneous/isdeployed.m \
  scripts/miscellaneous/ismac.m \
  scripts/miscellaneous/ispc.m \
  scripts/miscellaneous/isunix.m \
  scripts/miscellaneous/license.m \
  scripts/miscellaneous/list_primes.m \
  scripts/miscellaneous/ls.m \
  scripts/miscellaneous/ls_command.m \
  scripts/miscellaneous/menu.m \
  scripts/miscellaneous/mex.m \
  scripts/miscellaneous/mexext.m \
  scripts/miscellaneous/mkdir.m \
  scripts/miscellaneous/mkoctfile.m \
  scripts/miscellaneous/movefile.m \
  scripts/miscellaneous/namelengthmax.m \
  scripts/miscellaneous/news.m \
  scripts/miscellaneous/open.m \
  scripts/miscellaneous/orderfields.m \
  scripts/miscellaneous/pack.m \
  scripts/miscellaneous/parseparams.m \
  scripts/miscellaneous/perl.m \
  scripts/miscellaneous/python.m \
  scripts/miscellaneous/recycle.m \
  scripts/miscellaneous/rmappdata.m \
  scripts/miscellaneous/run.m \
  scripts/miscellaneous/setappdata.m \
  scripts/miscellaneous/setfield.m \
  scripts/miscellaneous/substruct.m \
  scripts/miscellaneous/swapbytes.m \
  scripts/miscellaneous/symvar.m \
  scripts/miscellaneous/tar.m \
  scripts/miscellaneous/tempdir.m \
  scripts/miscellaneous/tmpnam.m \
  scripts/miscellaneous/unix.m \
  scripts/miscellaneous/unpack.m \
  scripts/miscellaneous/untar.m \
  scripts/miscellaneous/unzip.m \
  scripts/miscellaneous/ver.m \
  scripts/miscellaneous/version.m \
  scripts/miscellaneous/what.m \
  scripts/miscellaneous/xor.m \
  scripts/miscellaneous/zip.m

scripts_miscellaneousdir = $(fcnfiledir)/miscellaneous

scripts_miscellaneous_DATA = $(scripts_miscellaneous_FCN_FILES)

scripts_miscellaneous_privatedir = $(fcnfiledir)/miscellaneous/private

scripts_miscellaneous_private_DATA = $(scripts_miscellaneous_PRIVATE_FCN_FILES)

FCN_FILES += \
  $(scripts_miscellaneous_FCN_FILES) \
  $(scripts_miscellaneous_PRIVATE_FCN_FILES)

PKG_ADD_FILES += scripts/miscellaneous/PKG_ADD

DIRSTAMP_FILES += scripts/miscellaneous/$(octave_dirstamp)
