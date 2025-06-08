#!/bin/bash
module load openmpi
mpic++ -o proj07 proj07.cpp -lm -fopenmp
for b in 4 8 12 16 32 48 64
do
        mpiexec -mca btl self,tcp -np $b ./proj07
done