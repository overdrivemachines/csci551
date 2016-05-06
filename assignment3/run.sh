#!/bin/sh
### script to run one job

### Set the job name
#PBS -N GaussianElimination

### Join the standard output and standard error streams
#PBS -j oe

### Specify wallclock time required for this job, hhh:mm:ss
#PBS -l walltime=00:15:00

### set directory for job execution
### EDIT THIS FOR YOUR LOGIN AND PATH
cd ~jch-s04/assignment3

### record the date, then time your executable program
date
/usr/bin/time ./ge "8000" "$1"
