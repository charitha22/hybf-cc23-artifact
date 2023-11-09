#!/bin/bash
# Download and use a precompiled binary distribution

wget https://github.com/Kitware/CMake/releases/download/v3.21.4/cmake-3.21.4-linux-x86_64.tar.gz
tar xf cmake-3.21.4-linux-x86_64.tar.gz
rm -f cmake-3.21.4-linux-x86_64.tar.gz
export PATH=$(realpath cmake-3.21.4-linux-x86_64/bin):$PATH
