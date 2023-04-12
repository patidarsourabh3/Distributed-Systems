# Assignment No. 2

### Directory Structure
      ├── 2021201089
      │   ├── 2021201089_1
      │   │   ├── mapper.py
      │   │   ├── reducer.py
      │   │   └── runner_script.py
      │   ├── 2021201089_2
      │   │   ├── mapper.py
      │   │   ├── reducer.py
      │   │   └── runner_script.py
      │   └── README.md


### How to execute the code
To run the code use command,
```
python3 runner_script.py <jar file> <input txt file> <hdfs input directory> <hdfs output directory> <Mapper Reducer file directory>
```
Example - 
```
python3 runner_script.py /opt/hadoop-3.2.4/share/hadoop/tools/lib/hadoop-streaming-3.2.4.jar input.txt /tmp/input/ /tmp/output/ ./
```

### Question 1 - National Party or Not

```
Input : 
4
15
5
A A1 100 2000 NO
B A1 150 1500 NO
C F1 200 1800 YES
D D1 1500 2000 YES
E E1 1200 2400 NO

The runner_script will modify the input the input given below form:

A1 100 2000 NO
A1 150 1500 NO
F1 200 1800 YES
D1 1500 2000 YES
E1 1200 2400 NO

Than mapper will take the above as input as club all the state information in one.

A1 250 3500 0
F1 200 1800 1
D1 1500 2000 1
E1 1200 2400 0

Final reducer will check the criteria and based on the criteria fulfilled or not it will return "YES" or "NO".

```
### Question 2 - Matrix Multiplication 
 
```
Input : 
2 2
1 3
2 4
2 2
4 2
3 1

The runner_script will modify the input the input given below form:

A	0 0 1
A	0 1 3
A	1 0 2
A	1 1 4
B	0 0 4
B	0 1 2
B	1 0 3
B	1 1 1

Than mapper will make key value pair and this key value pair will got to reducer as input.

00 00 00        1
00 01 00        1
00 00 01        3
00 01 01        3
01 00 00        2
01 01 00        2
01 00 01        4
01 01 01        4
00 00 00        4
01 00 00        4
00 01 00        2
01 01 00        2
00 00 01        3
01 00 01        3
00 01 01        1
01 01 01        1

Final reducer will multiply the elements with same key and add the elements with same first 2 element of key and finally we will get the multiplied matrix.

13 5 
20 8
```

