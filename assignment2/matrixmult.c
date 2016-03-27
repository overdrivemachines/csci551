/**
 * File: matrixmult.c
 * This program performs multiplication of 2 matrices of integers
 * using MPI.
 *
 * Author: Dipen Chauhan
 */

#include <stdio.h>
#include <mpi.h>

int main(void)
{
 	int comm_sz;	//	Total number of processes
 	int my_rank;	//	Rank of process
 	char form[4];	//	ijk | ikj | kij
 	char flag;		//	R - Random Generation | I - Input
 	int matrixSize;
 	int **a;		//	n x n Matrix
 	int **b;		//	n x n Matrix
 	int i, j;		//	Counters used in for loops
 	srand(time(NULL));


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
		scanf("%s", &form);

		// Input flag: R - Random generation of matrices | I - Input matrices
		scanf(" %c", &flag);

		// Input matrix size
		scanf("%d", &matrixSize);

		// Allocate memory for the matrices
		a = (int **) malloc(sizeof(int*) * matrixSize);
		b = (int **) malloc(sizeof(int*) * matrixSize);

		// Populate the matrices...
		if (flag == "I")
		{
			// Input A matrix
			for (i = 0; i < matrixSize; i++)
				for (j = 0; j < matrixSize; j++)
					scanf("%d", &a[i][j]);

			// Input B matrix
			for (i = 0; i < matrixSize; i++)
				for (j = 0; j < matrixSize; j++)
					scanf("%d", &b[i][j]);
		}
		else
		{
			for (i = 0; i < matrixSize; i++)
				for (j = 0; j < matrixSize; j++)
					{
						a[i][j] = rand() % 100;
						a[i][j] = rand() % 100;
					}

		}		

	}
 	
 	return 0;
}