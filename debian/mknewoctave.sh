#! /bin/bash

OCT=octave-2.0.11.93

cd $HOME/debian

[ -d $OCT/debian ] || exit 0

mv -v $OCT/debian .
rm -rf $OCT
tar xfz Sources/octave/${OCT}.tar.gz
mv -v debian $OCT

[ -d $OCT/debian ] || exit 0
echo "Done."
