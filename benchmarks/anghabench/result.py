import sys

with open(sys.argv[1]) as f:
  for line in f:
    if 'Number of instructions' in line:
        print(line.split()[0])
