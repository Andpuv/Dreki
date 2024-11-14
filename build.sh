#!/bin/bash

CC="gcc"
CFLAGS="-Wall -g -D__DREKI_DEBUG__"
LDFLAGS=""

SOURCES="src/*.c src/cli/*.c src/core/*.c"
HEADERS="inc/*.h"
BINARY="-o bin/dreki-cli"

$CC $CFLAGS $SOURCES $LDFLAGS $BINARY
