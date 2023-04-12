#!/usr/bin/env python3
import sys

state_seats = 0
total_seats = 0
state_party = 0
six_per_poll = 0
p = int(sys.argv[1])

for line in sys.stdin:
    line = line.split()
    percen = (int(line[1]) / int(line[2])) * 100
    if percen > p:
        state_seats +=1
    if percen >= 6:
        six_per_poll += 1
    total_seats += int(percen/p)
    if int(line[3])==1:
        state_party +=1

if state_party>=4 or state_seats>=3 or (six_per_poll >=4 and total_seats>=4):
    print("YES")
else:
    print("NO")