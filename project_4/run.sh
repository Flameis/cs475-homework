#!/bin/bash

# Create or clear the results.csv file at the start
echo "NUMT,NUMCITIES,NUMCAPITALS,Performance" > results.csv

for n in 2 3 4 5 10 15 20 30 40 50
do
    g++ all04.cpp -ARRAYSIZE=$n -o proj04 -lm -fopenmp
    
    # Run the program and append output directly to results.csv
    ./all04 >> results.csv
done

echo "Results have been saved to results.csv"