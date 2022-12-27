
cmake -DLLVM_ENABLE_PROJECTS='clang;compiler-rt;lld' -DCMAKE_BUILD_TYPE="Release" -DLLVM_ENABLE_ASSERTIONS=On -B build -DCMAKE_INSTALL_PREFIX=install llvm 

