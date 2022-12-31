#!/bin/bash
DIR=$(dirname $0)
cd ${DIR}/../build/
cmake --build . --target opt -j
cmake --build . --target clang -j
cmake --build . --target llvm-size -j
#cmake --build . --target install -j
cd ..
ln -s build install
