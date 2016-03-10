# Project Report

## Value of n used
3920000

## How we arrived at this value of n?
I used the Trapezoidal Rule to approximate the area between the graph of the function. I divided the interval on the x-axis into n equal subintervals. I then approximated the area lying between the graph and each subinterval by a trapezoid whose base is the subinterval. The areas of the trapezoids were added up which gave me the approximate area under the curve. I calculated the area for different number of trapezoids. I started off with 1, 2, 4, 8, 16, etc trapezoids where the number of trapezoids doubled each iteration. Also for each iteration, the Absolute Relative True Error was calculated. The interation was stopped when the Absolute Relative True Error was less than 0.5e-14. The number of trapezoids were 33554432 when the Absolute Relative True Error fell below 0.5e-14. I felt I could get a smaller number so instead of doubling the number of trapezoids every iteration, I experimented a little and incremented the number of trapezoids by 560000. The program found a smaller number of trapezoids - 3920000.

## Absolute Relative True Error using 3920000 Trapezoids
6.8148708997564173782e-16

## Tables of Timings from all runs
Timings for parallel code. a = 100, b = 600, n = 3920000.

| \# Processes | Time (ms) |||||
|---|---|---|---|---|---|
| 1 process | 4.764011e-01 | 4.770048e-01 | **4.655771e-01** | 4.971199e-01 | 5.249851e-01 |
| 2 processes | **2.511709e-01** | 2.512050e-01 | 2.511780e-01 | 2.795460e-01 | 2.512329e-01 |
| 8 processes | 7.840300e-02 | 7.854414e-02 | 7.836819e-02 | 7.712007e-02 | **7.627106e-02** |
| 14 processes | 4.826713e-02 | 4.745913e-02 | 8.894110e-02 | 1.115181e-01 | **4.330182e-02** |
| 20 processes | 3.651309e-02 | 3.339100e-02 | **3.145099e-02** | 3.252006e-02 | 3.380013e-02 |


## Table of Minimum Timings and Calculated Speedup and Efficiency

| \# Processes (p) | Min Time (in ms) | Speedup SU(p) = T<sub>1</sub>/T<sub>p</sub> | Efficiency ef(p) = SU(p)/p |
|---|---|---|---|
| 1 process    | 4.655771e-01 | *n/a*     | *n/a* |
| 2 processes  | 2.511709e-01 |  1.853627 | 0.926813 |
| 8 processes  | 7.627106e-02 |  6.104243 | 0.763030 |
| 14 processes | 4.330182e-02 | 10.751906 | 0.767993 |
| 20 processes | 3.145099e-02 | 14.803257 | 0.740163 |


## A graph of Speedup
![](https://drive.google.com/uc?export=download&id=0B1-D_TgyHJtMSFZ1SFdYc1A2WU0)

## A graph of Efficiency
![](https://drive.google.com/uc?export=download&id=0B1-D_TgyHJtMcjBETzVCclc3eEU)


## Conclusions
For a fixed problem size, Speedup increases as the number of processes increase and seems like it would plateau. On the other hand, Efficiency decreases as the number of processes increase and it then seems to hold steady.

## Experiments in Scaled Speedup, Results, Conclusions 

Scaled Speedup Table using 20 processes. a = 100, b = 600.

|  Task Size | Time (ms) |||||
|---:|---|---|---|---|---|
|     10,000 | 2.058029e-03 | **1.780033e-03** | 1.857996e-03 | 1.970053e-03 | 1.799107e-03 |
|  1,000,000 | 9.440899e-03 | **8.408070e-03** | 8.939981e-03 | 8.759975e-03 | 9.773970e-03 |
| 10,000,000 | 7.965493e-02 | 7.963109e-02 | 8.531904e-02 | 8.485007e-02 | **7.739592e-02** |
| 30,000,000 | **2.200050e-01** | 2.228291e-01 | 2.157710e-01 | 2.288949e-01 | 2.266889e-01 |
| 80,000,000 | 5.956919e-01 | 5.681348e-01 | 6.266172e-01 | **5.355589e-01** | 5.937741e-01 |
| 200,000,000 | **1.314811e+00** | 1.317947e+00 | 1.389248e+00 | 1.346352e+00 | 1.456730e+00 |


|   Task Size | Time (ms)    | Speedup    |
|---:|---|---|
|      10,000 | 1.780033e-03 |      *n/a* |
|   1,000,000 | 8.408070e-03 |   4.723547 |
|  10,000,000 | 7.739592e-02 |  43.480048 |
|  30,000,000 | 2.200050e-01 | 123.596023 |
|  80,000,000 | 5.355589e-01 | 300.870209 |
| 200,000,000 | 1.314811e+00 | 738.644171 |