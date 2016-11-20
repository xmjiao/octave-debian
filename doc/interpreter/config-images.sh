#! /bin/sh

set -e

AWK=${AWK:-awk}
SHELL=${SHELL:-/bin/sh}

if [ $# -eq 1 ]; then
  top_srcdir="$1"
else
  top_srcdir="../.."
fi

move_if_change="$top_srcdir/build-aux/move-if-change"

interp_dir=$top_srcdir/doc/interpreter

$AWK -v dir=doc/interpreter -f $interp_dir/images.awk < $interp_dir/images > $interp_dir/images.mk-t

$SHELL $move_if_change $interp_dir/images.mk-t $interp_dir/images.mk
