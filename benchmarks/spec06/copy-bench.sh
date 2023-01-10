BENCHMARKS=$(cat BenchNames)
SPEC06_LOC=../ZendTo-TogvJX4aVJepjGp7/spec06

for bench in ${BENCHMARKS}; do
  # echo ${bench}
  echo "copying benchmark ${bench}"
  cp -r ${SPEC06_LOC}/${bench}/src ./${bench}
  
done