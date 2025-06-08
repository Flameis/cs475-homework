#!/bin/bash
#SBATCH  -J  Proj07
#SBATCH  -A  cs475-575
#SBATCH  -p  classgputest
#SBATCH  --constraint=v100
#SBATCH  --gres=gpu:1
#SBATCH  -o  proj07.out
#SBATCH  -e  proj07.err
#SBATCH  --mail-type=BEGIN,END,FAIL
#SBATCH  --mail-user=scovell@oregonstate.edu

mpic++ -o proj07 proj07.cpp -lm -fopenmp
for b in 4 8 16 32 64
do
        mpiexec -mca btl self,tcp -np $b ./proj07
done