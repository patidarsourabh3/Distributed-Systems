#!/usr/bin/env python3
import sys
d = {}

for line in sys.stdin:
    state, votes, total_votes, state_party = line.split()
    if state not in d:
        d[state] = [0,0,0]
    d[state][0] += int(votes)
    d[state][1] += int(total_votes)
    if state_party == "YES":
        d[state][2] = 1

for k, v in d.items():
    print(k+" "+str(v[0])+" "+str(v[1])+" "+str(v[2]))

