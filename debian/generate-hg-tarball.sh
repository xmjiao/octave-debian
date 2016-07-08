#!/bin/sh

### Generate a tarball from the upstream Mercurial repository
### Copyright (C) 2016 Rafael Laboissiere

### This script can be called from anywhere and will generate a
### tarball following the naming convention:
### octave_<version>~hg.<date>.<revision>.orig.tar.xz

cleanup(){
    [ -n "$tmpdir" -a -d "$tmpdir" ] && rm -rf $tmpdir
}
trap "cleanup" 1 2 3 13 15

tmpdir=$(mktemp -d)
curdir=$(pwd)
date=$(date +%Y%m%d)

hg clone http://www.octave.org/hg/octave $tmpdir
cd $tmpdir

./bootstrap
./configure
make all
make dist-xz

hgnum=$(hg identify --num)
version=$(./configure -V | head -n 1 | perl -ne '/([\d.]+)/;print $1')
tarball=octave_${version}~hg.${date}.${hgnum}.orig.tar.xz

ls *.tar.xz
pwd
mv *.tar.xz $curdir/$tarball

cd $curdir

[ -f $tarball ]					\
    && echo "Created upstream tarball $tarball"	\
    || echo "Creation of hg tarball failed"

cleanup

