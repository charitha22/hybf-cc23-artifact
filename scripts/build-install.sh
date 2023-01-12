#!/bin/bash
DIR=$(dirname $0)
cd ${DIR}/../build/
cmake --build . --target opt -j4
cmake --build . --target clang -j4
cmake --build . --target llvm-size -j4
cmake --build . --target llvm-link -j4
#cmake --build . --target install -j
cd ..
ln -s build install
