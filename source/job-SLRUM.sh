#!/bin/bash
#SBATCH --job-name=MyCode
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
##SBATCH --ntasks=1
#SBATCH --mem=300M
#SBATCH --time=00:01:00
#SBATCH --output=MyCode_%j.out
#SBATCH --error=MyCode_%j.err

#Outout file names
PREFIX=test2 
./main "$PREFIX"
#mpiexec -n 32 ./main $PREFIX 

#Compresse the output data 
if [ -d ../output ]; then
  cd ../output

  # Create archive inside output/
  tar -cjvf "${PREFIX}.tar.bz2" "${PREFIX}".* 2>/dev/null || true

  # Remove everything starting with PREFIX.* except the tarball itself
  find . -maxdepth 1 -type f -name "${PREFIX}.*" ! -name "${PREFIX}.tar.bz2" -delete
else
  echo "Warning: output/ directory not found — skipping compression step."
fi

exit 0

