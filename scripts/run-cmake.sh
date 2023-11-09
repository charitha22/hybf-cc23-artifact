#!/bin/bash
DIR=$(dirname $0)
cd ${DIR}/..

# lld is often faster but needs an existing llvm installation
LINKER=gold
#LINKER=lld

# Ninja is a bit faster than make. uncomment it if you have it
GNRTOR="Unix Makefiles"
#GNRTOR="Ninja"

cmake -G "$GNRTOR" -DLLVM_ENABLE_PROJECTS='clang' -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On -B build -DLLVM_TARGETS_TO_BUILD=X86 -DLLVM_INCLUDE_TESTS=OFF -DLLVM_USE_LINKER=$LINKER -DCMAKE_INSTALL_PREFIX=install llvm 
