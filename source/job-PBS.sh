#!/bin/bash
#PBS -N MyCode
#PBS -l select=1:ncpus=1:mem=300mb
#PBS -l walltime=100:00:00
#PBS -j oe
#PBS -o MyCode_$PBS_JOBID.out
#PBS -q queue_name   # <-- optional: use your site's queue name

# Move to the directory where qsub was invoked
cd "$PBS_O_WORKDIR" || exit 1

PREFIX=test #Outout file names
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

