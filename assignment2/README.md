# PROJECT REPORT

## Objectives
- Perform Matrix Multiplication, exploring the ijk forms.
- Experiment with the distribution of work and data.
- Collect and analyze empirical timing data.

## Form ijk

### Description of Partitioning Used
Rows in Array A were divided and sent to different processes. Rows are contigious in memory so when each process gets a row, we are taking advantage  Array B was broadcasted to all the processes. Each process then calculated the product. This resultant product was combined and assembled in the Master process (Process having rank 0).  

### Timings

Timings for n = 4800. Minimum times are shown in bold.

| \# Cores | Time (ms) |||||
|---|---|---|---|---|---|
| 1 | 6.482730e+02 | **6.301806e+02** | 6.356979e+02 | 6.456381e+02 | 7.743673e+02 |
| 4 | **1.688437e+02** | 2.879936e+02 | 1.690258e+02 | 4.463490e+02 | 4.340871e+02 |
| 8 | 1.507076e+02 | 8.573829e+01 | 1.481224e+02 | 1.501238e+02 | **8.384676e+01** |
| 12 | 1.680680e+02 | **5.729153e+01** | 1.549841e+02 | 1.055643e+02 | 1.364572e+02 |
| 16 | 8.083944e+01 | 4.353488e+01 | 8.154826e+01 | **4.346974e+01** | 4.352726e+01 |
| 20 | 1.255137e+02 | **6.140914e+01** | 1.166914e+02 | 6.164995e+01 | 6.147898e+01 |

### Speedup and Efficiency

Table of Speedup and Efficiecy calculated from the minimums

| \# Cores | Time (s) | Speedup | Efficiency |
|---|---|---|---|
| 1 | 6.301806e+02 | 1.000000E+00 | 1.000000E+00 |
| 4 | 1.688437e+02 | 3.732331E+00 | 9.330828E-01 |
| 8 | 8.384676e+01 | 7.515861E+00 | 9.394826E-01 |
| 12 | 5.729153e+01 | 1.099954E+01 | 9.166285E-01 |
| 16 | 4.346974e+01 | 1.449699E+01 | 9.060622E-01 |
| 20 | 6.140914e+01 | 1.026200E+01 | 5.131000E-01 |

Graph of Speedup

![Speedup ijk](https://drive.google.com/uc?export=download&id=0B1-D_TgyHJtMWUxCajgtVkNyY0U)

Graph of Efficiency

## Form ikj

### Description of Partitioning Used

### Timings

Timings for n = 4800

| \# Cores | Time (s) |||||
|---|---|---|---|---|---|
| 1 | 4.683063e+02 | **4.342753e+02** | 4.342853e+02 | 4.532983e+02 | 4.388923e+02 |
| 4 | 3.500120e+02 | **1.209488e+02** | 2.217803e+02 | 3.480561e+02 | 2.283204e+02 |
| 8 | 1.065374e+02 | **6.179089e+01** | 8.620827e+01 | 1.470618e+02 | 7.004955e+01 |
| 12 | 1.142936e+02 | 6.732175e+01 | 1.271251e+02 | **4.257176e+01** | 9.936750e+01 |
| 16 | 8.892981e+01 | 5.966556e+01 | 1.016866e+02 | **4.256988e+01** | 4.923188e+01 |
| 20 | 8.253640e+01 | 4.351649e+01 | 7.906707e+01 | 4.358732e+01 | **4.343979e+01** |

### Speedup and Efficiency
Table of Speedup and Efficiency calculated from the minimums

| \# Cores | Time (s) | Speedup | Efficiency |
|---|---|---|---|
| 1  | 4.342753E+02 | 1.000000E+00 | 1.000000E+00 | 
| 4  | 1.209488E+02 | 3.590571E+00 | 8.976428E-01 | 
| 8  | 6.179089E+01 | 7.028144E+00 | 8.785181E-01 | 
| 12 | 4.257176E+01 | 1.020102E+01 | 8.500849E-01 | 
| 16 | 4.256988E+01 | 1.020147E+01 | 6.375918E-01 | 
| 20 | 4.343979E+01 | 9.997178E+00 | 4.998589E-01 | 



Graph of Speedup
Graph of Efficiency

## Form kij

### Description of Partitioning Used

### Timings

Timings for n = 4800

| \# Cores | Time (ms) |||||
|---|---|---|---|---|---|
| 1 | 7.099131e+02 | 4.786510e+02 | **4.359557e+02** | 4.944320e+02 | 4.793248e+02 |
| 4 | 3.350564e+02 | 3.357620e+02 | **1.487389e+02** | 7.151192e+02 | 3.377234e+02 |
| 8 | 1.003718e+02 | 1.033585e+02 | 1.307396e+02 | **6.215207e+01** | 1.162265e+02 |
| 12 | 4.158095e+01 | 9.564934e+01 | 1.097120e+02 | **4.157000e+01** | 1.088340e+02 |
| 16 | 1.487026e+02 | **3.174097e+01** | 1.062930e+02 | 4.351300e+01 | 4.316432e+01 |
| 20 | 8.713193e+01 | 4.358498e+01 | 8.685583e+01 | **4.354816e+01** | 4.378311e+01 |

### Speedup and Efficiency
Table of Speedup and Efficiency calculated from the minimums

| \# Cores | Time (s) kij | Speedup | Efficiency |
|---|---|---|---|
| 1  | 4.359557E+02 | 1.000000E+00 | 1.000000E+00 | 
| 4  | 1.487389E+02 | 2.931013E+00 | 7.327533E-01 | 
| 8  | 6.215207E+01 | 7.014339E+00 | 8.767924E-01 | 
| 12 | 4.157000E+01 | 1.048727E+01 | 8.739389E-01 | 
| 16 | 3.174097E+01 | 1.373479E+01 | 8.584247E-01 | 
| 20 | 4.354816E+01 | 1.001089E+01 | 5.005443E-01 | 

Graph of Speedup
Graph of Efficiency

## Observations, Analysis and Conclusions