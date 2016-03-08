# Project Report

## Value of n used
33554432

## How we arrived at this value of n?
I used the Trapezoidal Rule to approximate the area between the graph of the function. I divided the interval on the x-axis into n equal subintervals. I then approximated the area lying between the graph and each subinterval by a trapezoid whose base is the subinterval. I calculated the integral value by adding up the areas up for n = 1, 2, 4, 8 ... trapezoids. For each iteration, the Absolute Relative True Error was calculated. The interation was stopped when the Absolute Relative True Error was less than 0.5e-14. The number of trapezoids were 33554432 when the Absolute Relative True Error fell below 0.5e-14.

## Absolute Relative True Error using 33554432 Trapezoids
6.8148708997564173782e-16

## Tables of Timings from all runs
## Table of Minimum Timings and Calculated Speedup and Efficiency
## A graph of Speedup
## A graph of Efficiency
## Conclusions
## Experiments in Scaled Speedup, Results, Conclusions 