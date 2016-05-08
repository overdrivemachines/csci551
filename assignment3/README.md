# PROJECT REPORT BY DIPEN CHAUHAN

## Objectives
- Implement a parallel version of Gaussian elimination with partial pivoting.
- Run timing tests and analyze speedup and efficiency.

# Pseudocode Showing Key Elements In The Parallelization Strategy

# Data Storage
Gaussian elimination is a method for solving matrix equations of the form
Ax = b where A is a Matrix, and x and b are vectors.

I used an array of array pointers to represent the augmented matrix.

# Exploiting Parallelism and Partitioning Data & Work

# Synchronization

# Justification for Implementation Choices

# Timings

Problem size n = 8000 was used to evaluate the performance of my implementation. Timing measurements for the combination of the elimination and back substitution phases of my implementation were collected.

| Cores |            |            |            |            |            |
|-------|------------|------------|------------|------------|------------|
| 1     | 570.318198 | 570.140426 | 642.862851 | 648.233734 | 648.171710 |
| 2     | 420.283759 | 421.882246 | 431.313673 | 432.813073 | 419.426101 |
| 5     | 248.244881 | 247.548421 | 241.307507 | 242.004513 | 241.986887 |
| 10    | 213.984610 | 213.856487 | 225.228781 | 224.865838 | 410.658996 |
| 20    | 410.105860 | 207.847415 | 208.121708 | 207.960084 | 207.947326 |
| 30    | 207.122235 | 410.145916 | 207.129673 | 219.694855 | 410.346868 |


# Speedup and Efficiency

Table of Speedup and Efficiency calculated from the minimums


Graph of Speedup


Graph of Efficiency
