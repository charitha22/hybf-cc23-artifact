DIR=$(dirname $0)
cd ${DIR}/../build/
make opt clang
make install
