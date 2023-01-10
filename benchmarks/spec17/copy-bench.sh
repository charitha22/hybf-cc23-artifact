BENCHMARKS=$(cat BenchNames)
SPEC17_LOC=../ZendTo-TogvJX4aVJepjGp7/spec17

for bench in ${BENCHMARKS}; do
  # echo ${bench}
  echo "copying benchmark ${bench}"
  cp -r ${SPEC17_LOC}/${bench}/src ./${bench}
  
done