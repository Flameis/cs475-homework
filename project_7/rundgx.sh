#!/bin/bash
#SBATCH -J Fourier
#SBATCH -A cs475-575
#SBATCH -p classmpitest
#SBATCH -N 8 # number of nodes
#SBATCH -n 8 # number of tasks
#SBATCH -o mpiproject.out
#SBATCH -e mpiproject.err
#SBATCH  --mail-type=BEGIN,END,FAIL
#SBATCH  --mail-user=scovell@oregonstate.edu
module load openmpi
mpic++ -o proj07 proj07.cpp -lm -fopenmp
for b in 4 8 12 16 32
do
        mpiexec -mca btl self,tcp -np $b ./proj07
done