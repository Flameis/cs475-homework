#!/bin/bash

# Create or clear the results.csv file at the start
echo "NUMT,NUMCITIES,NUMCAPITALS,Performance" > results.csv

for t in 1 2 4 6 8
do
    for n in 2 3 4 5 10 15 20 30 40 50
    do
        g++ proj03.cpp -DNUMT=$t -DNUMCAPITALS=$n -o proj03 -lm -fopenmp
        
        # Run the program and append output directly to results.csv
        ./proj03 >> results.csv
    done
done

echo "Results have been saved to results.csv"