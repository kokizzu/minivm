#!/usr/bin/env bash

cd $(dirname $0)
cd ..

mkdir -p build/bench/png

rm -f build/bench/png/*

python3 test/graph.py

montage -geometry x480 build/bench/png/*.png build/bench/out.png
