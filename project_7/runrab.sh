#!/bin/bash
module load openmpi
mpic++ -o proj07 proj07.cpp -lm -fopenmp
for b in 1 2 4 6 8
do
        mpiexec -mca btl self,tcp -np $b ./proj07
done