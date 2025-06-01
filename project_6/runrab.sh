#!/bin/bash
for t in 1024 4096 16384 65536 262144 1048576 2097152
do
    for b in 8 32 64 128 256
    do
        g++ -o proj06 proj06.cpp -lm -fopenmp -DATASIZE=$t -LOCALSIZE=$b
        ./proj06
    done
done