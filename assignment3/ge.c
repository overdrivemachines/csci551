#ifndef DEBUG
#define DEBUG 0
#endif
#define debug_printf(fmt, ...) \
            do { if (DEBUG) printf(fmt, __VA_ARGS__); } while (0)
            
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void Gen_matrix(double ***A, double ***A_augmented, int matrixSize, int threadCount);
void Read_matrix(double ***A, double ***A_augmented, int matrixSize);
void swapRow(double **a, double **b);
void displayMatrix(double **a, int matrixSize);
void backSubstitution(double ***A_augmented, int matrixSize, int threadCount);
// void iSquaredNorm(double ***A, double **X, int matrixSize, int threadCount);


int main(int argc, char const *argv[])
{
	int matrixSize = strtol(argv[1], NULL, 10);
	int coreCount = omp_get_num_procs();
	int threadCount = strtol(argv[2], NULL, 10);
	double startTime, finishTime;
	double **a_augmented, **a;	// n x n Matrix as a 2D array
	double *bestRow; // used in partial pivoting
	double diagonalElement, bestElement, factor;
	int bestRowIndex = 0; // used in partial pivoting (index of row having greatest absolute value)
	int i, j, k;	// for loop counters
	double *x;	//	Solutions

	printf("Matrix Size: %d\n", matrixSize);
	printf("Number of Cores: %d\n", coreCount);

	#pragma omp parallel num_threads(threadCount)
	{
		if (omp_get_thread_num() == 0)
			printf("Thread Count: %d\n", omp_get_num_threads());
	}

	// Start Timer
	startTime = omp_get_wtime();

	// Allocate memory
	// a_augmented will be the augmented matrix
	a_augmented = (double **) malloc(matrixSize * sizeof(double *));
	// a will be the randomly generated matrix
	a = (double **) malloc(matrixSize * sizeof(double *));
	x = (double *) malloc(matrixSize * sizeof(double));
	
	if (DEBUG == 1)
		Read_matrix(&a, &a_augmented, matrixSize);
	else
		Gen_matrix(&a, &a_augmented, matrixSize, threadCount);

	// a will not be modified after this point
	// Only the a_augmented will be modified 

	// Display generated matrix:
	displayMatrix(a, matrixSize);

	for (i = 0; i < matrixSize - 1; ++i)
	{
		// Diagonal Element
		diagonalElement = a_augmented[i][i];
		// debug_printf("diagonalElement%d = %f\n", i, diagonalElement);

		// Find the best row (the one with the largest absolute value in the column being worked on)
		bestRowIndex = i;
		bestElement = diagonalElement;
		for (j = i + 1; j < matrixSize; ++j)
		{
			if (fabs(a_augmented[j][i]) > fabs(bestElement))
			{
				bestRowIndex = j;
				bestElement = a_augmented[j][i];
				// debug_printf("bestElement = %f\n", a_augmented[j][i]);
			}
		}

		// Swap the rows
		if (i != bestRowIndex)
		{
			// debug_printf("Row %d needs to be swapped with Row %d\n", i, bestRowIndex );
			swapRow(&a_augmented[i], &a_augmented[bestRowIndex]);	
			// Update the diagonal element
			diagonalElement = a_augmented[i][i];
			// debug_printf("diagonalElement%d = %f\n", i, diagonalElement);
			// displayMatrix(a_augmented, matrixSize);
		}

		// To make the diagonal element 1, divide the whole row with the diagonal element
		// debug_printf("Row %d = Row %d / %f\n", i, i, diagonalElement);
		for (j = 0; j < matrixSize + 1; ++j)
		{
			a_augmented[i][j] = a_augmented[i][j] / diagonalElement;
		}

		// Force the diagonal to be 1 (to avoid any roundoff errors in dividing above)
		a_augmented[i][i] = 1;
		diagonalElement = 1;

		// Annihilation: Zero all the elements in the row below the diagonal element
		for (j = i + 1; j < matrixSize; ++j)
		{
			factor = a_augmented[j][i];
			if (factor != 0)
			{
				// debug_printf("Row %d = Row %d - %f*Row %d\n", j, j, factor, i);
				for (k = i; k < matrixSize + 1; ++k)
				{
					a_augmented[j][k] = a_augmented[j][k] - factor * a_augmented[i][k];
				}
				// displayAugmentedMatrix(a, matrixSize);
			}			
		}
	}

	// Make the diagonal element of the last row 1
	a_augmented[matrixSize-1][matrixSize] = a_augmented[matrixSize-1][matrixSize] / a_augmented[matrixSize-1][matrixSize-1];
	a_augmented[matrixSize-1][matrixSize-1] = 1;

	// Display augmented matrix:
	displayMatrix(a_augmented, matrixSize);

	// Back substitution (parallelized)
	backSubstitution(&a_augmented, matrixSize, threadCount);

	displayMatrix(a_augmented, matrixSize);

	// Matrix X from augmented matrix:
	for (i = 0; i < matrixSize; ++i)
	{
		x[i] = a_augmented[i][matrixSize];
	}

	// Find I^2 norm
	// iSquaredNorm(a, x, matrixSize, threadCount);

	finishTime = omp_get_wtime();
	printf("Time taken = %f\n", finishTime - startTime);	

	// Free memory
	free(a);
	return 0;
}

void Gen_matrix(double ***A, double ***A_augmented, int matrixSize, int threadCount)
{
	double **a = *A;
	double **a_augmented = *A_augmented;
	int i, j; // Loop counters
	// struct drand48_data drand_buf;

	srand48(time(NULL));
	// Fill augmented matrix with random numbers in the range [-1.0e6, 1.0e6)
	
	// Parallelization may take more time
	// #pragma omp parallel for num_threads(threadCount) \
	// 	default(none) private(i, j, drand_buf) shared(a, matrixSize)
	for (i = 0; i < matrixSize; ++i)
	{
		// printf("My rank = %d i = %d\n", omp_get_thread_num(), i);
		// sleep(1);
		// Allocate memory
		a[i] = (double *) malloc((matrixSize+1) * sizeof(double));
		a_augmented[i] = (double *) malloc((matrixSize+1) * sizeof(double));
		for (j = 0; j < matrixSize + 1; ++j)
		{
			// generating random number
			// drand48() returns [0, 1)
			a[i][j] = -1.0e6 + drand48() * (2.0e6);
			a_augmented[i][j] = a[i][j];
			// a[i][j] = rand() % 10;
			// drand48_r (&drand_buf, &a[i][j]);
			// a[i][j] = a[i][j] * 2.0e6 - 1.0e6;
		}
	}
}

void Read_matrix(double ***A, double ***A_augmented, int matrixSize)
{
	double **a = *A;
	double **a_augmented = *A_augmented;
	int i, j; // Loop counters
	// Fill augmented matrix from standard input
	for (i = 0; i < matrixSize; ++i)
	{
		// Allocate memory
		a[i] = (double *) malloc((matrixSize+1) * sizeof(double));
		a_augmented[i] = (double *) malloc((matrixSize+1) * sizeof(double));
		for (j = 0; j < matrixSize + 1; ++j)
		{
			// Read input from user
			scanf("%lf", &a[i][j]);
			a_augmented[i][j] = a[i][j];
		}
	}
}

void swapRow(double **a, double **b)
{
	double *temp = *a;
	*a = *b;
	*b = temp;
}

void displayMatrix(double **a, int matrixSize)
{
	int i, j;
	for (i = 0; i < matrixSize; ++i)
	{
		for (j = 0; j < matrixSize + 1; ++j)
		{
			// printf("%.6e ", a[i*matrixSize + j]);
			printf("%2.2f ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void backSubstitution(double ***A_augmented, int matrixSize, int threadCount)
{
	double **a_augmented = *A_augmented;
	int i, j; // Loop counters
	double factor;

	for (i = matrixSize-1; i >= 0; --i)
	{
		factor = a_augmented[i][matrixSize];

		#pragma omp parallel for num_threads(threadCount) \
			default(none) private(j) shared(a_augmented, i, matrixSize, factor)
		for (j = 0; j < i; ++j)
		{
			a_augmented[j][matrixSize] = a_augmented[j][matrixSize] - factor * a_augmented[j][i];
			a_augmented[j][i] = 0;
		}
	}
}

// void iSquaredNorm(double ***A, double **X, int matrixSize, int threadCount)
// {
// 	double **a = *A;
// 	double *x = *X;
// 	int i, j; // Loop counters

// 	for (i = 0; i < matrixSize; ++i)
// 	{
// 		// a[i][matrixSize] = a[i][i] * 
// 	}
// }