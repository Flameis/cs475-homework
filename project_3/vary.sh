#!/bin/bash

# Create or clear the results.csv file at the start
echo "NUMT,NUMCAPITALS,Performance" > results.csv

for t in 1 2 4 6 8
do
    for n in 2 3 4 5 10 15 20 30 40 50
    do
        g++ proj03.cpp -DNUMT=$t -DNUMCAPITALS=$n -o proj03 -lm -fopenmp
        
        # Run the program and capture the output
        output=$(./proj03)
        
        # Extract the last line and append it to results.csv
        echo "$output" | tail -n 2 >> results.csv
    done
done