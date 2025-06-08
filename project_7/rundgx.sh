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

g++ -o proj07 proj07.cpp -lm -fopenmp
./proj07