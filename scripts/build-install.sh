#!/bin/bash
DIR=$(dirname $0)
cd ${DIR}/../build/
cmake --build . --target opt  --target clang --target llvm-size -j
cmake --build . --target install -j
