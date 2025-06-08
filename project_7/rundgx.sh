#!/bin/bash
#SBATCH -J Fourier
#SBATCH -A cs475-575
#SBATCH -p classmpitest
#SBATCH -N 8
#SBATCH -n 8
#SBATCH -o mpiproject.out
#SBATCH -e mpiproject.err
#SBATCH --mail-type=END,FAIL
#SBATCH --mail-user=scovell@oregonstate.edu

module load openmpi
for b in 4 8 12 16 32
do
    mpic++ proj07.cpp -o proj07 -lm
    mpiexec -mca btl self,tcp -n $b ./proj07
done