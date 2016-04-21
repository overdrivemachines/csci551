#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	int matrixSize = strtol(argv[1], NULL, 10);
	int thread_count = strtol(argv[2], NULL, 10);
	double **a;	// n x n Matrix as a 1D array
	double diagonalElement;
	int bestRow = 0;

	int i, j, k;	// for loop counters

	printf("Matrix Size: %d\n", matrixSize);
	printf("Thread Count: %d\n", thread_count);

	// Allocate memory
	// a will be the augmented matrix
	a = (double **) malloc(matrixSize * sizeof(double *));

	srand(time(NULL));
	srand48(time(NULL));

	// Fill augmented matrix with random numbers in the range [-1.0e6, 1.0e6)
	for (i = 0; i < matrixSize; ++i)
	{
		a[i] = (double *) malloc((matrixSize+1) * sizeof(double));
		for (j = 0; j < matrixSize + 1; ++j)
		{
			if (rand() % 2 == 0)
				a[i][j] = drand48() * 1.0e6;
			else
				a[i][j] = -1 * drand48() * 1.0e6;
		}		
	}

	// Display augmented matrix:
	for (i = 0; i < matrixSize; ++i)
	{
		for (j = 0; j < matrixSize + 1; ++j)
		{
			// printf("%.6e ", a[i*matrixSize + j]);
			printf("%f ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	// For each column, annihilate below the diagonal
	// for (i = 0; i < matrixSize - 1; ++i)
	// {
	// 	// For each row j below row i
	// 	for (j = i + 1; j < matrixSize; ++j)
	// 	{
	// 		temp = a[i*matrixSize + i];
	// 		for (k = 0; i < matrixSize; ++i)
	// 		{
	// 			a[j*matrixSize + k] = a[j*matrixSize + k] - (temp / a[i*matrixSize + i]) * a[i*matrixSize + k];
	// 		}
	// 	}
		
	// }


	for (i = 0; i < matrixSize - 1; ++i)
	{
		// Diagonal Element
		diagonalElement = a[i][i];

		// Find the best row (the one with the largest absolute value in the column being worked on)
		bestRow = i;
		for (j = i + 1; j < matrixSize; ++j)
		{
			if (a[j][i] > diagonalElement)
				bestRow = j;
		}

		// Swap the rows
		

		for (j = 0; j < matrixSize+1; ++j)
			a[i*matrixSize + j] = a[i*matrixSize + j] / diagonalElement;

		printf("diagonalElement = %f\n", diagonalElement);
		for (j = i + 1; j < matrixSize; ++j)
		{
			for (k = 0; k < matrixSize + 1; ++k)
			{
				// a[j*matrixSize + k] = a[j*matrixSize + k] - ;
			}
		}
	}

	// Display augmented matrix:
	// for (i = 0; i < matrixSize; ++i)
	// {
	// 	for (j = 0; j < matrixSize + 1; ++j)
	// 	{
	// 		// printf("%.6e ", a[i*matrixSize + j]);
	// 		printf("%f ", a[i*matrixSize + j]);
	// 	}
	// 	printf("\n");
	// }
	// printf("\n");
	

	// Free memory
	free(a);
	return 0;
}