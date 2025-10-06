#!/bin/bash
#SBATCH --job-name=MyCode
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
##SBATCH --ntasks=1
#SBATCH --mem=300M
#SBATCH --time=100:00:00
#SBATCH --output=MyCode_%j.out
#SBATCH --error=MyCode_%j.err

# === Job configuration ===
Np=1
PREFIX=test

# === Load any required modules (optional) ===
# module load gcc/12.1.0

# === Run your executable ===
./main "$PREFIX"

# === Uncomment this for profiling ===
# gprof ./main gmon.out > Profile-Report.txt

# === Compress output ===
cd ./output || exit 1  # safer: exit if cd fails
tar -cjvf "${PREFIX}.tar.bz2" "${PREFIX}".*  # quotes prevent globbing issues
mkdir -p ./Results  # ensure Results exists
mv "${PREFIX}.tar.bz2" ./compressed/.

# === Clean up ===
rm -f "${PREFIX}".*  # -f avoids "no such file" errors

exit 0

