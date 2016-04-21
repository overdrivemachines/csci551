#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	int matrixSize = strtol(argv[1], NULL, 10);
	int thread_count = strtol(argv[2], NULL, 10);
	float *a;	// n x n Matrix as a 1D array
	float *b;	// n-vector

	int i, j;

	printf("Matrix Size: %d\n", matrixSize);
	printf("Thread Count: %d\n", thread_count);

	// Allocate memory
	a = (float *) malloc(sizeof(float) * matrixSize * matrixSize);
	b = (float *) malloc(sizeof(float) * matrixSize);


	// Fill Matrix A with random numbers
	for (i = 0; i < matrixSize*matrixSize; ++i)
	{		
		if (i % 2 == 0)
			a[i] = drand48();
		else
			a[i] = -1 * drand48();
	}

	// Fill Vector b with random numbers
	for (i = 0; i < matrixSize; ++i)
	{		
		if (i % 2 == 0)
			b[i] = drand48();
		else
			b[i] = -1 * drand48();
	}

	// Display Matrix A:
	for (i = 0; i < matrixSize; ++i)
	{
		for (j = 0; j < matrixSize; ++j)
		{
			printf("%.6e ", a[i*matrixSize + j]);
		}
		printf("\n");
	}
	printf("\n");

	// Display Vector B:
	for (i = 0; i < matrixSize; ++i)
	{
		printf("%.6e\n", b[i]);
	}


	

	// Free memory
	free(a);
	free(b);
	return 0;
}