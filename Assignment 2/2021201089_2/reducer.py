#!/usr/bin/env python3
import sys

multiply_d = {}
add_d = {}
m = 0
p = 0
for line in sys.stdin:
    key, value = line.split("\t")
    if key in multiply_d:
        multiply_d[key] *= int(value)
        temp_key = key.split()
        temp_key = temp_key[0:2]
        m = max(m, int(temp_key[0]))
        p = max(p, int(temp_key[1]))
        temp_key = ' '.join(temp_key)
        if temp_key in add_d:
            add_d[temp_key] += multiply_d[key]
        else:
            add_d[temp_key] = multiply_d[key]
    else:
        multiply_d[key] = int(value)

ans = []
temp = []
for i in range(m+1):
    temp = []
    for j in range(p+1):
        temp.append(0)
    ans.append(temp)  

for k, v in add_d.items():
    i, j = map(int, k.split())
    ans[i][j] = v

for i in range(m+1):
    for j in range(p+1):
        print(ans[i][j], end =" ")
    print()   
