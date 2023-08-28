#! /bin/sh

mkdir -p build && gcc -Wall -Wextra -Wpedantic -std=c11 -o build/ncat src/ncat.c -Isrc -O2
