#! /bin/sh
rm -f *.o* combined-output.txt combined-error.txt
# qsub -v OMP_NUM_THREADS=4 -l select=1:ncpus=4 ./run.sh
qsub ./run.sh -F "1"
qsub ./run.sh -F "2"
qsub ./run.sh -F "5"
qsub ./run.sh -F "10"
qsub ./run.sh -F "20"
qsub ./run.sh -F "30"