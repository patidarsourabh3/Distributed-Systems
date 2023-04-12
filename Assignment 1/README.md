
# Assignment No. 1

## Problem 1: Mandelbrot Set
    - The total time complexity - O((n*m*k)/np)
    - The total message complexity - O(np)
    - The space requirements -  O(n*m)

    Here,
    n*m - Matrix size 
    k - no of iterations
    np - number of process

#### Input -    
    16 16 1000

#### Output -
    0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
    0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 
    0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 
    0 0 0 0 0 1 1 1 1 1 1 1 0 0 0 0 
    0 0 0 1 0 1 1 1 1 1 1 1 0 0 0 0 
    0 0 1 1 1 1 1 1 1 1 1 1 0 0 0 0 
    0 0 1 1 1 1 1 1 1 1 1 1 0 0 0 0 
    0 0 0 1 0 1 1 1 1 1 1 1 0 0 0 0 
    0 0 0 0 0 1 1 1 1 1 1 1 0 0 0 0 
    0 0 0 0 0 0 1 1 1 1 1 0 0 0 0 0 
    0 0 0 0 0 0 1 1 1 1 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
    0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0

#### Performance Metric -
| No. of process | real  | user  | sys |
| ------- | --- | --- | --- |
| 1 | 0m0.952s | 0m0.059s | 0m0.180s| 
| 2 | 0m0.879s | 0m0.584s | 0m0.061s| 
| 3 | 0m1.074s | 0m0.796s | 0m0.852s| 
| 4 | 0m0.787s | 0m0.727s | 0m0.511s| 
| 5 | 0m1.115s | 0m1.842s | 0m1.237s| 
| 6 | 0m1.179s | 0m1.904s | 0m1.249s| 
| 7 | 0m1.005s | 0m1.398s | 0m1.203s| 
| 8 | 0m1.032s | 0m1.579s | 0m1.296s| 
| 9 | 0m0.864s | 0m1.112s | 0m1.169s| 
| 10 | 0m0.848s | 0m1.201s | 0m1.047s| 
| 11 | 0m0.912s | 0m1.139s | 0m1.237s| 
| 12 | 0m0.929s | 0m1.269s | 0m1.194s| 


## Problem 2: Tony Stark and Pym Particles

    - The total time complexity - O((t*k*k))/np
    - The total message complexity - O((t*m)/np)
    - The space requirements - O(k)

    t - no. of iterations
    k - no. of particles
    np - no. of processes
    m - number of columns in grid

 #### Input - 

    10 12 16 100
    0 1 R
    2 1 L
    3 3 U
    9 9 L
    6 8 D
    4 8 L
    7 3 R
    5 6 U
    0 1 U
    2 1 D
    3 3 R
    9 9 U
    6 8 L
    4 8 D
    7 3 U
    5 6 R

#### Output - 

    0 6 L
    0 9 D
    2 11 U
    3 3 R
    3 6 L
    3 7 D
    4 10 D
    5 3 R
    5 4 D
    6 4 U
    7 5 U
    7 9 R
    7 10 R
    8 6 L
    9 1 D
    9 10 R

#### Performance Metric -

| No. of process | real  | user  | sys |
| ------- | --- | --- | --- |
| 1 | 0m0.413s | 0m0.065s | 0m0.083s| 
| 2 | 0m1.534s | 0m1.232s | 0m0.093s| 
| 3 | 0m2.146s | 0m1.836s | 0m1.721s| 
| 4 | 0m1.815s | 0m1.824s | 0m1.929s| 
| 5 | 0m1.240s | 0m1.107s | 0m1.268s| 
| 6 | 0m0.994s | 0m1.819s | 0m0.937s| 
| 7 | 0m0.968s | 0m0.886s | 0m0.944s| 
| 8 | 0m1.236s | 0m1.077s | 0m1.402s| 
| 9 | 0m1.200s | 0m0.922s | 0m1.333s| 
| 10 | 0m1.444s | 0m1.266s | 0m1.835s| 
| 11 | 0m1.233s | 0m1.180s | 0m1.362s| 
| 12 | 0m1.308s | 0m1.329s | 0m1.612s| 


### Problem 3: Jar of Words

    - The total time complexity - O((n*n*n)/np)
    - The total message complexity -O(n*n*n/(np*np))
    - The space requirements - O(n*n)

    n - number of key, frequency pairs
    np -number of processes

#### Input -

    8
    5 7
    3 6
    7 5
    6 17
    1 16
    4 8
    2 13
    8 28

#### Output - 
    238
    2 6 4 2 4 0 8 6
#### Performance Metric -

| No. of process | real  | user  | sys |
| ------- | --- | --- | --- |
| 1 | 0m0.464s | 0m0.101s | 0m0.095s |
| 2 | 0m1.338s | 0m1.048s | 0m0.076s |
| 3 | 0m1.272s | 0m0.915s | 0m0.947s |
| 4 | 0m0.970s | 0m0.788s | 0m0.850s |
| 5 | 0m1.059s | 0m0.862s | 0m1.112s
| 6 | 0m0.971s | 0m0.804s | 0m1.066s |
| 7 | 0m0.956s | 0m0.824s | 0m1.097s |
| 8 | 0m0.956s | 0m0.788s | 0m1.011s |
| 9 | 0m0.929s | 0m0.825s | 0m1.007s
| 10 |	0m0.973s | 0m0.864s | 0m1.117s|
| 11 | 0m0.941s | 0m0.818s | 0m1.006s |
| 12 | 0m1.497s | 0m1.378s | 0m2.096s |