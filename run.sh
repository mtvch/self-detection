#!/bin/bash
mkdir -p build
cmake -S src -B build
cd build && make && cd ..
./build/lab1 $1 $2 $3 $4 $5