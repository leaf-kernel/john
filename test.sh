#!/bin/bash
mkdir -p bin
gcc -o bin/simple example/simple.c john.c
./bin/simple
rm -rf bin