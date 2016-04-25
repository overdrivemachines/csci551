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

void Gen_matrix(double ***A, int matrixSize, int threadCount);
void Read_matrix(double ***A, int matrixSize);
void swapRow(double **a, double **b);
void displayAugmentedMatrix(double **a, int matrixSize);
void backSubstitution(double ***A, int matrixSize, int threadCount);


int main(int argc, char const *argv[])
{
	int matrixSize = strtol(argv[1], NULL, 10);
	int coreCount = omp_get_num_procs();
	int threadCount = strtol(argv[2], NULL, 10);
	double startTime, finishTime;
	// int thread_count;
	double **a;	// n x n Matrix as a 1D array
	double *bestRow; // used in partial pivoting
	double diagonalElement, bestElement, factor;
	int bestRowIndex = 0; // used in partial pivoting (index of row having greatest absolute value)
	int i, j, k;	// for loop counters

	printf("Matrix Size: %d\n", matrixSize);
	printf("Number of Cores: %d\n", coreCount);
	printf("Thread Count: %d\n", threadCount);

	// Allocate memory
	// a will be the augmented matrix
	a = (double **) malloc(matrixSize * sizeof(double *));

	startTime = omp_get_wtime();
	if (DEBUG == 1)
		Read_matrix(&a, matrixSize);
	else
		Gen_matrix(&a, matrixSize, threadCount);

	finishTime = omp_get_wtime();
	printf("Time taken to generate matrix = %f\n", finishTime - startTime);

	exit(0);

	// Display augmented matrix:
	displayAugmentedMatrix(a, matrixSize);

	for (i = 0; i < matrixSize - 1; ++i)
	{
		// Diagonal Element
		diagonalElement = a[i][i];
		debug_printf("diagonalElement%d = %f\n", i, diagonalElement);

		// Find the best row (the one with the largest absolute value in the column being worked on)
		bestRowIndex = i;
		bestElement = diagonalElement;
		for (j = i + 1; j < matrixSize; ++j)
		{
			if (fabs(a[j][i]) > fabs(bestElement))
			{
				bestRowIndex = j;
				bestElement = a[j][i];
				// debug_printf("bestElement = %f\n", a[j][i]);
			}
		}

		// Swap the rows
		if (i != bestRowIndex)
		{
			debug_printf("Row %d needs to be swapped with Row %d\n", i, bestRowIndex );
			swapRow(&a[i], &a[bestRowIndex]);	
			// Update the diagonal element
			diagonalElement = a[i][i];
			debug_printf("diagonalElement%d = %f\n", i, diagonalElement);
			displayAugmentedMatrix(a, matrixSize);
		}

		// To make the diagonal element 1, divide the whole row with the diagonal element
		debug_printf("Row %d = Row %d / %f\n", i, i, diagonalElement);
		for (j = 0; j < matrixSize + 1; ++j)
		{
			a[i][j] = a[i][j] / diagonalElement;
		}

		// Force the diagonal to be 1 (to avoid any roundoff errors in dividing above)
		// a[i][i] = 1;
		// diagonalElement = 1;

		// Zero all the elements in the row below the diagonal element
		for (j = i + 1; j < matrixSize; ++j)
		{
			factor = a[j][i];
			if (factor != 0)
			{
				debug_printf("Row %d = Row %d - %f*Row %d\n", j, j, factor, i);
				for (k = i; k < matrixSize + 1; ++k)
				{
					a[j][k] = a[j][k] - factor * a[i][k];
				}
				displayAugmentedMatrix(a, matrixSize);
			}			
		}
	}

	// Last row
	a[matrixSize-1][matrixSize] = a[matrixSize-1][matrixSize] / a[matrixSize-1][matrixSize-1];
	a[matrixSize-1][matrixSize-1] = 1;

	// Display augmented matrix:
	displayAugmentedMatrix(a, matrixSize);


	// Back substitution
	backSubstitution(&a, matrixSize, threadCount);

	displayAugmentedMatrix(a, matrixSize);


	// Free memory
	free(a);
	return 0;
}

void Gen_matrix(double ***A, int matrixSize, int threadCount)
{
	double **a = *A;
	int i, j; // Loop counters
	srand(time(NULL));
	srand48(time(NULL));
	// Fill augmented matrix with random numbers in the range [-1.0e6, 1.0e6)
	#pragma omp parallel for num_threads(threadCount) \
		default(none) private(i, j) shared(a, matrixSize)
	for (i = 0; i < matrixSize; ++i)
	{
		// printf("My rank = %d i = %d\n", omp_get_thread_num(), i);
		// sleep(1);
		a[i] = (double *) malloc((matrixSize+1) * sizeof(double));
		for (j = 0; j < matrixSize + 1; ++j)
		{
			// generating random number
			// drand48() returns [0, 1)
			a[i][j] = -1.0e6 + drand48() * (2.0e6);
			// a[i][j] = rand() % 10;
		}
	}
}

void Read_matrix(double ***A, int matrixSize)
{
	double **a = *A;
	int i, j; // Loop counters
	// Fill augmented matrix from standard input
	for (i = 0; i < matrixSize; ++i)
	{
		a[i] = (double *) malloc((matrixSize+1) * sizeof(double));
		for (j = 0; j < matrixSize + 1; ++j)
		{
			// Read input from user
			scanf("%lf", &a[i][j]);
		}
	}
}

void swapRow(double **a, double **b)
{
	double *temp = *a;
	*a = *b;
	*b = temp;
}

void displayAugmentedMatrix(double **a, int matrixSize)
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

void backSubstitution(double ***A, int matrixSize, int threadCount)
{
	double **a = *A;
	int i, j; // Loop counters
	double factor;

	for (i = matrixSize-1; i >= 0; --i)
	{
		factor = a[i][matrixSize];

		#pragma omp parallel for num_threads(threadCount) \
			default(none) private(j) shared(a, i, matrixSize, factor)
		for (j = 0; j < i; ++j)
		{
			a[j][matrixSize] = a[j][matrixSize] - factor * a[j][i];
			a[j][i] = 0;
		}
	}
}