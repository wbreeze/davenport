#!/bin/sh

export BASE_DIR="`dirname $0`"

if test -z "$IS_MAKE_TEST"; then
  top_dir="$BASE_DIR/.."
  make -C $top_dir || exit 1
fi

if test -z "$CUTTER"; then
  CUTTER="cutter"
fi

$CUTTER -s $BASE_DIR "$@" $BASE_DIR
