#! /bin/sh

mkdir -p build && gcc -Wall -std=c11 -o build/ncat src/ncat.c src/cnifti.c -Isrc -O2
