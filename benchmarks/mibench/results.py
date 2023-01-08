#!/usr/bin/env python3
from pathlib import Path
import subprocess
import string
import sys

_HEX_DIGITS = set(string.hexdigits)

def is_hex(s):
    # if s is long, then it is faster to check against a set
    return all(c in _HEX_DIGITS for c in s)

def binarySize(filename):
    count = 0
    with open(filename) as f:
        for line in f:
            if ':' not in line:
                continue
            tmp = line.split(':')
            offset = tmp[0].strip()
            if not is_hex(offset):
                continue
            instruction = tmp[1].strip().split('\t')
            if not instruction:
                continue
            binary = instruction[0].strip().split()
            valid = all([is_hex(byte.strip()) for byte in binary])
            if valid:
                count += len(binary)
    return count

def main():
    bench = Path(sys.argv[1])
    sizeexec = sys.argv[2]
    ftypes = sys.argv[3:]
    for ftype in ftypes:
        filename = bench / 'build' / ftype
        pr = subprocess.run([sizeexec, str(filename)], check=True, stdout=subprocess.PIPE, universal_newlines=True)
        text_size = pr.stdout.split('\n')[1].split()[0]
        print(f'{bench}, {ftype}, {text_size}')

if __name__ == '__main__':
    main()
