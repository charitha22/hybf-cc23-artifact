CLANG=../../install/bin/clang
LLOPT=../../install/bin/opt
SIZE=../../install/bin/llvm-size


BRFUSION="-mllvm -enable-brfusion=true -mllvm -run-brfusion-only=true -mllvm -run-cfm-only=false -mllvm -brfusion-dot=false -mllvm -brfusion-soa=false  -mllvm -func-merging-hyfm-nw=false  -mllvm -func-merging-hyfm-pa=true -mllvm -func-merging-debug=true -mllvm -func-merging-verbose=false"
CFMELDER="-mllvm -enable-brfusion=true -mllvm -run-brfusion-only=false -mllvm -run-cfm-only=true -mllvm -brfusion-dot=false -mllvm -brfusion-soa=false  -mllvm -func-merging-hyfm-nw=false  -mllvm -func-merging-hyfm-pa=true -mllvm -func-merging-debug=true -mllvm -func-merging-verbose=false"
HYBF="-mllvm -enable-brfusion=true -mllvm -run-brfusion-only=false -mllvm -run-cfm-only=false -mllvm -brfusion-dot=false -mllvm -brfusion-soa=false  -mllvm -func-merging-hyfm-nw=false  -mllvm -func-merging-hyfm-pa=true -mllvm -func-merging-debug=true -mllvm -func-merging-verbose=false"

FILE=cfm-better.c

echo "BASELINE"
$CLANG -Oz -mllvm -enable-brfusion=false $FILE -c -o $FILE.baseline.o 2>/dev/null
$CLANG -Oz -mllvm -enable-brfusion=false $FILE -emit-llvm -S -o $FILE.baseline.ll 2>/dev/null 
$LLOPT -dot-cfg $FILE.baseline.ll -o /dev/null 2>/dev/null
mv ".BF_cfb64_encrypt.dot" $FILE.baseline.dot
$SIZE $FILE.baseline.o

echo "SEME-FUSION"
$CLANG -Oz $BRFUSION $FILE -c -o $FILE.seme-fusion.o 2>/dev/null
$CLANG -Oz $BRFUSION $FILE -emit-llvm -S -o $FILE.seme-fusion.ll 2>/dev/null 
$LLOPT -dot-cfg $FILE.seme-fusion.ll -o /dev/null 2>/dev/null
mv ".BF_cfb64_encrypt.dot" $FILE.seme-fusion.dot
$SIZE $FILE.seme-fusion.o

echo "CFM-CS"
$CLANG -Oz $CFMELDER $FILE -c -o $FILE.cfm.o 2>/dev/null
$CLANG -Oz $CFMELDER $FILE -emit-llvm -S -o $FILE.cfm.ll 2>/dev/null  
$LLOPT -dot-cfg $FILE.cfm.ll -o /dev/null 2>/dev/null
mv ".BF_cfb64_encrypt.dot" $FILE.cfm.dot
$SIZE $FILE.cfm.o

echo "HYBF"
$CLANG -Oz $HYBF $FILE -c -o $FILE.hybf.o 2>/dev/null
$CLANG -Oz $HYBF $FILE -emit-llvm -S -o $FILE.hybf.ll 2>/dev/null
$LLOPT -dot-cfg $FILE.hybf.ll -o /dev/null 2>/dev/null
mv ".BF_cfb64_encrypt.dot" $FILE.hybf.dot
$SIZE $FILE.hybf.o

