# Project Report

## Value of n used
3920000

## How we arrived at this value of n?
I used the Trapezoidal Rule to approximate the area between the graph of the function. I divided the interval on the x-axis into n equal subintervals. I then approximated the area lying between the graph and each subinterval by a trapezoid whose base is the subinterval. The areas of the trapezoids were added up which gave me the approximate area under the curve. I calculated the area for different number of trapezoids. I started off with 1, 2, 4, 8, 16, etc trapezoids where the number of trapezoids doubled each iteration. Also for each iteration, the Absolute Relative True Error was calculated. The interation was stopped when the Absolute Relative True Error was less than 0.5e-14. The number of trapezoids were 33554432 when the Absolute Relative True Error fell below 0.5e-14. I felt I could get a smaller number so instead of doubling the number of trapezoids every iteration, I experimented a little and incremented the number of trapezoids by 560000. The program found a smaller number of trapezoids - 3920000.

## Absolute Relative True Error using 3920000 Trapezoids
6.8148708997564173782e-16

## Tables of Timings from all runs
Timings for parallel code as a single process. a = 100, b = 600, n = 3920000
| 4.764011e-01 |
|--------------|
| 4.770048e-01 |
| 4.655771e-01 |
| 4.971199e-01 |
| 5.249851e-01 |

## Table of Minimum Timings and Calculated Speedup and Efficiency
## A graph of Speedup
## A graph of Efficiency
## Conclusions
## Experiments in Scaled Speedup, Results, Conclusions 