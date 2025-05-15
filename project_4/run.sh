#!/bin/bash

# This script compiles the C++ program and runs it with different array sizes from 1K to 8M
echo "bSIMD,ARRAYSIZE,SPEEDUP" > results.csv

for n in 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 2097152 4194304 8388608
do
    # Compile the program with the current array size
    g++ -o proj04 proj04.cpp -lm -fopenmp -DARRAYSIZE=$n
    
    # Check if compilation was successful
    if [ $? -eq 0 ]; then
        # Run the program
        ./proj04 >> results.csv
    else
        echo "Compilation failed for array size $n"
    fi
done

echo "Results have been saved to results.csv"