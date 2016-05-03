#! /bin/sh
rm -f *.o* combined-output.txt combined-error.txt
# qsub -v OMP_NUM_THREADS=4 -l select=1:ncpus=4 ./run.sh
qsub ./run.sh -F "1"
qsub ./run.sh -F "2"