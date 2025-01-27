#!/bin/bash
#SBATCH --job-name=MyCode
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
##SBATCH --ntasks=1
#SBATCH --mem=300mb
#SBATCH --time=100:00:00
Np=1
PREFIX=test
./main $PREFIX
#mpirun -np $Np ./main $PREFIX < /dev/null


