/**
 * File: matrixmult.c
 * This program performs multiplication of 2 matrices of integers
 * using MPI.
 *
 * Author: Dipen Chauhan
 */

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()

int main(void)
{
 	int comm_sz;	//	Total number of processes
 	int my_rank;	//	Rank of process
 	char form[4];	//	ijk | ikj | kij
 	char flag;		//	R - Random Generation | I - Input
 	int matrixSize;
 	int *a;			//	n x n Matrix as a 1D array
 	int *b;			//	n x n Matrix as a 1D array
 	int *c;			//	n x n Matrix as a 1D array (this is where we store the result)
 	int i, j;		//	Counters used in for loops
 	double start_time, finish_time;


 	/* Start up MPI */
	MPI_Init(NULL, NULL); 

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0)
	{
		// Read from standard input
		
		// Input form: ijk | ikj | kij 
		scanf("%s", form);

		// Input flag: R - Random generation of matrices | I - Input matrices
		scanf(" %c", &flag);

		// Input matrix size
		scanf("%d", &matrixSize);

		// Allocate memory for the matrices
		// https://www.cs.swarthmore.edu/~newhall/unixhelp/C_arrays.html
		a = (int *) malloc(sizeof(int) * matrixSize * matrixSize);
		b = (int *) malloc(sizeof(int) * matrixSize * matrixSize);
		c = (int *) malloc(sizeof(int) * matrixSize * matrixSize);

		// Populate the matrices...
		if (flag == 'I')
		{
			// Input A matrix
			for (i = 0; i < matrixSize * matrixSize; i++)
					scanf("%d", &a[i]);

			// Input B matrix
			for (i = 0; i < matrixSize * matrixSize; i++)
					scanf("%d", &b[i]);
		}
		else
		{
			srand(time(NULL));
			for (i = 0; i < matrixSize * matrixSize; i++)
			{
				rand();
				a[i] = rand() % 100;
				b[i] = rand() % 100;
			}
		}
	}

	// Synchronization
	MPI_Barrier(MPI_COMM_WORLD);
	if (my_rank == 0)
	{
		// Record the Start Time
		start_time = MPI_Wtime();
	}

	// Perform Calculation here..


	// Display output
	if (my_rank == 0)
	{
		// Record the Finish Time
		finish_time = MPI_Wtime();

		printf("running on %d processors\n", comm_sz);
		printf("elapsed time = %.6e seconds\n", finish_time - start_time);
		printf("A:\n");
		for (i = 0; i < matrixSize; i++)
		{
			for (j = 0; j < matrixSize; j++)
				printf("%d ", a[i*matrixSize + j]);
			printf("\n");
		}
		printf("B:\n");
		for (i = 0; i < matrixSize; i++)
		{
			for (j = 0; j < matrixSize; j++)
				printf("%d ", b[i*matrixSize + j]);
			printf("\n");
		}

		free(a);
		free(b);
	}	
 	
 	/* Shut down MPI */
	MPI_Finalize();
 	return 0;
}