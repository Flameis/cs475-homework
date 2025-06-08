#!/bin/bash
#SBATCH -J Fourier
#SBATCH -A cs475-575
#SBATCH -p classmpitest
#SBATCH -N 8 # number of nodes
#SBATCH -n 8 # number of tasks
#SBATCH -o mpiproject.out
#SBATCH -e mpiproject.err
#SBATCH  --mail-type=END,FAIL
#SBATCH  --mail-user=scovell@oregonstate.edu

module load openmpi
for b in 1 2 4 6 8
do
        mpic++ proj07.cpp -o proj07 -lm
        mpiexec -mca btl self,tcp -np $b ./proj07
done