#!/bin/bash

# This script compiles the C++ program and runs it with different array sizes from 1K to 8M
for n in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388608
do
    # echo "ARRAYSIZE,SUMN,SUMS,MEGAMULTS,MEGAMULTADDS,SPEEDUP" > results.csv

    t=$n * $n
    g++ proj04.cpp -ARRAYSIZE=$t proj04 -lm -fopenmp
    
    ./proj04 >> results.csv
done

echo "Results have been saved to results.csv"