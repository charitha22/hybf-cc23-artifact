

CLANG=../../install/bin/clang
LLOPT=../../install/bin/opt
SIZE=../../install/bin/llvm-size


BRFUSION="-mllvm -enable-brfusion=true -mllvm -run-brfusion-only=true -mllvm -run-cfm-only=false -mllvm -brfusion-dot=false -mllvm -brfusion-soa=false  -mllvm -func-merging-hyfm-nw=false  -mllvm -func-merging-hyfm-pa=true -mllvm -func-merging-debug=true -mllvm -func-merging-verbose=false"
CFMELDER="-mllvm -enable-brfusion=true -mllvm -run-brfusion-only=false -mllvm -run-cfm-only=true -mllvm -brfusion-dot=false -mllvm -brfusion-soa=false  -mllvm -func-merging-hyfm-nw=false  -mllvm -func-merging-hyfm-pa=true -mllvm -func-merging-debug=true -mllvm -func-merging-verbose=false"
HYBF="-mllvm -enable-brfusion=true -mllvm -run-brfusion-only=false -mllvm -run-cfm-only=false -mllvm -brfusion-dot=false -mllvm -brfusion-soa=false  -mllvm -func-merging-hyfm-nw=false  -mllvm -func-merging-hyfm-pa=true -mllvm -func-merging-debug=true -mllvm -func-merging-verbose=false"

if test -f BenchNames; then
  ALL_FILES=$(cat BenchNames)
else
  ALL_FILES=$(find . -name "*.c")
fi


OUTPUTFILE=results.csv
:>$OUTPUTFILE

for FILE in $ALL_FILES; do
  rm -f baseline.ll cfm.ll seme-fusion.ll hybf.ll

  #echo "BASELINE"
  #$CLANG -Oz -mllvm -enable-brfusion=false $FILE -c -o $FILE.baseline.o 2>/dev/null
  $CLANG -Oz -mllvm -enable-brfusion=false $FILE -emit-llvm -S -o baseline.ll 2>/dev/null
  if test -f baseline.ll; then
    $LLOPT -instcount -stats baseline.ll -o /dev/null 2>tmp.txt
    echo "$FILE,baseline,$(python3 result.py tmp.txt)" >> $OUTPUTFILE
  fi

  #echo "SEME-FUSION"
  #$CLANG -Oz $BRFUSION $FILE -c -o $FILE.seme-fusion.o 2>/dev/null
  $CLANG -Oz $BRFUSION $FILE -emit-llvm -S -o seme-fusion.ll 2>/dev/null 
  if test -f seme-fusion.ll; then
    $LLOPT -instcount -stats seme-fusion.ll -o /dev/null 2>tmp.txt
    echo "$FILE,SEME-Fusion,$(python3 result.py tmp.txt)" >> $OUTPUTFILE
  fi

  #echo "CFM-CS"
  #$CLANG -Oz $CFMELDER $FILE -c -o $FILE.cfm.o 2>/dev/null
  $CLANG -Oz $CFMELDER $FILE -emit-llvm -S -o cfm.ll 2>/dev/null  
  if test -f cfm.ll; then
    $LLOPT -instcount -stats cfm.ll -o /dev/null 2>tmp.txt
    echo "$FILE,CFM-CS,$(python3 result.py tmp.txt)" >> $OUTPUTFILE
  fi

  #echo "HYBF"
  #$CLANG -Oz $HYBF $FILE -c -o $FILE.hybf.o 2>/dev/null
  $CLANG -Oz $HYBF $FILE -emit-llvm -S -o hybf.ll 2>/dev/null
  if test -f hybf.ll; then
    $LLOPT -instcount -stats hybf.ll -o /dev/null 2>tmp.txt
    echo "$FILE,HyBF,$(python3 result.py tmp.txt)" >> $OUTPUTFILE
  fi

done

rm -f tmp.txt
rm -f baseline.ll cfm.ll seme-fusion.ll hybf.ll

#python3 plot-2-versions.py $OUTPUTFILE cfmelder cfmelder-brfusion-hyfm-pa
python3 plot-2-versions.py $OUTPUTFILE CFM-CS HyBF

