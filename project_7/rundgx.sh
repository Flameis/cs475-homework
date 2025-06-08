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

# Unset any user Perl environment to avoid breaking mpiexec
unset PERL5LIB
unset PERL_LOCAL_LIB_ROOT
unset PERL_MB_OPT
unset PERL_MM_OPT

mpic++ proj07.cpp -o proj07 -lm

for b in 4 8 12 16 32
do
    mpiexec -mca btl self,tcp -np $b ./proj07
done