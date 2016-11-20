#! /bin/sh

set -e

SED=${SED:-sed}
EGREP=${EGREP:-egrep}

# Some stupid egreps don't like empty elements in alternation patterns,
# so we have to repeat ourselves because some stupid egreps don't like
# empty elements in alternation patterns.

DEFUN_PATTERN="^[ \t]*DEF(CONSTFUN|UN|UN_DLD|UNX|UNX_DLD)[ \t]*\\("

srcdir="$1"
if [ "$1" ]; then
  shift
fi

for arg
do
  if [ -f "$arg" ]; then
    file="$arg"
  else
    file="$srcdir/$arg"
  fi
  if [ -f "$file" ]; then
    if [ "`$EGREP -l "$DEFUN_PATTERN" $file`" ]; then
      echo "$file" | $SED "s,\\$srcdir/,,"
    fi
  fi
done
