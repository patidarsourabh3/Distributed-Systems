#!/usr/bin/env python3
import sys

m = int(sys.argv[1])
n = int(sys.argv[2])
p = int(sys.argv[3])

for line in sys.stdin:
    line = line.split("\t")
    row, col, val = line[1].split()
    if len(row)==1:
        row = "0"+row
    if len(col)==1:
        col = "0"+col
    if line[0]=='A':
        for k in range(p):
            s = str(k)
            if k<=9:
                s = "0"+s
            key = row+" "+s+" "+col+"\t"+ val
            print(key)
    else:
        for k in range(m):
            s = str(k)
            if k<=9:
                s = "0"+s
            key = s+" "+col+" "+row+"\t"+ val
            print(key)