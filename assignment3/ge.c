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


	// Allocate memory
	a = (float *) malloc(sizeof(float) * matrixSize * matrixSize);
	b = (float *) malloc(sizeof(float) * matrixSize);


	printf("Matrix Size: %d\n", matrixSize);
	printf("Thread Count: %d\n", thread_count);

	// Free memory
	free(a);
	free(b);
	return 0;
}