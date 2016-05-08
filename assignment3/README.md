# PROJECT REPORT BY DIPEN CHAUHAN

## Objectives
- Implement a parallel version of Gaussian elimination with partial pivoting.
- Run timing tests and analyze speedup and efficiency.

# Pseudocode Showing Key Elements In The Parallelization Strategy

### Gaussian Elimination with Partial Pivoting on A:

	for i=0...n-1

		Pivoting:
		find p > i such that |a[p][i]| > |a[j][i]| for j > i
		Switch a[p] with a[i]

		Elimination:

	end

	Back Substitution:



# Data Storage

Gaussian elimination is a method for solving matrix equations of the form
Ax = b where A is a Matrix, and x and b are vectors.

I used an array of pointers to an array of doubles to represent the augmented matrix. For example if the matrix size was 4, my program would have an array of 4 points each to an array of 5 doubles. 

To calculate the I2 norm, I had to store matrix A separately as an array of pointers to an array of doubles, the solution x as an array of doubles and b also as an array of doubles.

I chose to store my matrix as an array of pointers to an array of doubles because it would be easy to swap rows during partial pivoting. All we have to do is interchange the addresses the pointers are pointing to.

# Exploiting Parallelism and Partitioning Data & Work

Parallelization was used in 2 sections of my code:

1) Annihilation - During each iteration of the annihilation process, the rows are divided among threads that subtract the row containing the pivot element from the row they are assigned. The number of rows needed to be computed is reduced by one after each iteration.
2) Back Substitution - During each iteration the rows are divided among threads. Each thread back substitutes with one variable during each iteration. The number of rows needed to be computed is reduced by one after each iteration.

# Synchronization

Synchronization happens (all the threads join) automatically at the end of the block following my a #pragma omp parallel statements.

# Justification for Implementation Choices

As mentioned earlier, I chose to store my matrix as an array of pointers to an array of doubles because it would be easy to swap rows during partial pivoting. All we have to do is interchange the addresses the pointers are pointing to.

# Timings

Problem size n = 8000 was used to evaluate the performance of my implementation. Timing measurements for the combination of the elimination and back substitution phases of my implementation were collected.

| # Cores | Time (s)           |||||
|-------|------------|------------|------------|------------|------------|
| 1     | 570.318198 | **570.140426** | 642.862851 | 648.233734 | 648.171710 |
| 2     | 420.283759 | 421.882246 | 431.313673 | 432.813073 | **419.426101** |
| 5     | 248.244881 | 247.548421 | **241.307507** | 242.004513 | 241.986887 |
| 10    | 213.984610 | **213.856487** | 225.228781 | 224.865838 | 410.658996 |
| 20    | 410.105860 | **207.847415** | 208.121708 | 207.960084 | 207.947326 |
| 30    | **207.122235** | 410.145916 | 207.129673 | 219.694855 | 410.346868 |


# Speedup and Efficiency

Table of Speedup and Efficiency calculated from the minimums


Graph of Speedup


Graph of Efficiency
