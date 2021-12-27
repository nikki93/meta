#!/bin/bash

set -e

PLATFORM="macOS"
CLANG="clang++"
TIME="time"
TIME_TOTAL="time"
EXE=""

if [[ -f /proc/version ]]; then
  if grep -q Linux /proc/version; then
    PLATFORM="lin"
    TIME="time --format=%es\n"
    TIME_TOTAL="time --format=total\t%es\n"
  fi
  if grep -q Microsoft /proc/version; then
    PLATFORM="win"
    CLANG="clang++.exe"
    EXE=".exe"
  fi
fi
CLANG="$TIME $CLANG"

$CLANG -std=c++20 -Wall -O3 -Iexample -o output example.cc
if [[ -f output ]]; then
  ./output || true
  rm output
fi
exit 1
