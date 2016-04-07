/**
 * File: matrixmult.c
 * Purpose: This program performs multiplication of 2 matrices of integers
 * 			using MPI.
 * Input: 	<form> 	- ijk | ikj | kij
 * 			<flag> 	- R - Random generation | I - Input matrices
 * 			<n>		- Matrix size n x n
 * 			<A>		- n x n Matrix in row major order
 * 			<B>		- n x n Matrix in row major order
 * Output: 	Time taken to do the matrix multiplication.
 * 			Product of the matrices (AB) *
 * Author:	Dipen Chauhan
 * URL:		http://www.ecst.csuchico.edu/~judyc/1516S-csci551/assignments/03-matrixmultiplcation.html
 *
 * MPI Basics: http://www.ecst.csuchico.edu/~judyc/1516S-csci551/notes/07-mpi-basics.html
 * MPI Comm: http://www.ecst.csuchico.edu/~judyc/1516S-csci551/notes/09-mpi-integration.html
 * MPI Comm: http://www.ecst.csuchico.edu/~judyc/1516S-csci551/notes/11-mpi-communication.html
 * MPI Scatter: http://mpitutorial.com/tutorials/mpi-scatter-gather-and-allgather/
 * Matrix Mult: http://www.ecst.csuchico.edu/~judyc/1516S-csci551/notes/13-blas.html
 * https://computing.llnl.gov/tutorials/mpi/samples/C/mpi_mm.c
 * http://blog.speedgocomputing.com/2010/08/parallelizing-matrix-multiplication_17.html
 * https://www.cs.rochester.edu/~scott/458/notes/06-MPI.pdf
 * http://www.mpich.org/static/docs/v3.1/www3/MPI_Scatterv.html
 *
 * Sample Runs:
 * $ echo "ijk R 3" | ./matrixmult
 * $ echo "ijk R 3" | mpirun -n 3 ./matrixmult
 * $ echo "ijk I 3 1 2 3 4 5 6 7 8 9 4 0 8 7 1 1 0 4 9" | mpirun -n 3 ./matrixmult
 * Output:
 * 18 14 37
 * 51 29 91
 * 84 44 145
 * 
 */

#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>  // rand(), srand()
#include <time.h>    // time()
#include <string.h>

void printMatrix(int *m, int matrixSize);

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
	int i, j, k;	//	Counters used in for loops
	double start_time, finish_time;

	/* Start up MPI */
	MPI_Init(NULL, NULL); 

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	// Process 0 reads from standard input
	if (my_rank == 0)
	{		
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
		else // Populate the matrices if R flag is selected by user
		{
			srand(time(NULL));
			for (i = 0; i < matrixSize * matrixSize; i++)
			{
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

	// Broadcast matrixSize from process 0 to all processes
	MPI_Bcast(&matrixSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// Broadcast form from process 0 to all processes
	MPI_Bcast(&form, 4, MPI_CHAR, 0, MPI_COMM_WORLD);

	if (my_rank != 0)
	{
		b = (int *) malloc(sizeof(int) * matrixSize * matrixSize);
		c = (int *) malloc(sizeof(int) * matrixSize * matrixSize);
	}

	// Broadcast array 'b' from process 0 to all processes
	MPI_Bcast(b, matrixSize * matrixSize, MPI_INT, 0, MPI_COMM_WORLD);

	// Number of elements of array 'a' each process will have
	int *elementsPerProc = (int *) malloc(sizeof(int) * comm_sz);
	int *displacements = (int *) malloc(sizeof(int) * comm_sz);

	for (i = 0; i < comm_sz; i++)
	{
		// Find number of rows
		elementsPerProc[i] = matrixSize / comm_sz;
		// Number of elements = number of rows * elements per row
		elementsPerProc[i] = elementsPerProc[i] * matrixSize;
	}
	int unassignedRows = matrixSize % comm_sz;
	if (unassignedRows != 0)
	{
		// Assigning the unassignmed rows to processors
		for (i = 0; i < unassignedRows; i++)
			elementsPerProc[i] += matrixSize;

	}

	// Calculate displacements (will be used in MPI_Scatterv)
	displacements[0] = 0;
	for (i = 1; i < comm_sz; i++)
		displacements[i] = displacements[i - 1] + elementsPerProc[i - 1]; 

	// Printing the displacements...
	// if (my_rank == 0)
	// {
	// 	for (i = 0; i < comm_sz; i++)
	// 		printf("%d:%d ", i, displacements[i]);
	// 	printf("\n");
	// }
	
	// int elementsPerProc = matrixSize * matrixSize / comm_sz;
	int *local_a = (int *) malloc(sizeof(int) * elementsPerProc[my_rank]);
	int *local_c = (int *) malloc(sizeof(int) * elementsPerProc[my_rank]);
	
	// Send chunks of array 'a' from process 0 to all processes and store them in local_a
	// MPI_Scatter(a, elementsPerProc, MPI_INT, local_a, elementsPerProc, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatterv(a, elementsPerProc, displacements, MPI_INT, local_a, elementsPerProc[my_rank], MPI_INT, 0, MPI_COMM_WORLD);

	// Print elements each process is receiving...
	// for (i = 0; i < elementsPerProc[my_rank]; i++)
	// 	printf("%d:local_a[%d]=%d\n", my_rank, i, local_a[i]);
	
	
	int rows = elementsPerProc[my_rank] / matrixSize;
	int sum = 0;

	if (strcmp(form, "ijk") == 0)
	{
		for (i = 0; i < rows; i++)
		{
			for (j = 0; j < matrixSize; j++)
			{
				sum = 0;
				for (k = 0; k < matrixSize; k++)
				{
					sum += local_a[i * matrixSize + k] * b[k * matrixSize + j];
				}

				local_c[i * matrixSize + j] = sum;

				// printf("%d:local_c[%d]=%d\n", my_rank, i * matrixSize + j, local_c[i * matrixSize + j]);
			}
		}
	}
	else if (strcmp(form, "ikj") == 0)
	{
		for (i = 0; i < rows; i++)
		{
			for (k = 0; k < matrixSize; k++)
			{
				sum = 0;
				for (j = 0; j < matrixSize; j++)
				{
					sum += local_a[i * matrixSize + k] * b[k * matrixSize + j];
				}
				local_c[i * matrixSize + k] = sum; 

			}
		}
	}
	else if (strcmp(form, "kij") == 0)
	{
		for (k = 0; k < matrixSize; k++)
		{
			for (i = 0; i < rows; i++)
			{
				sum = 0;
				for (j = 0; j < matrixSize; j++)
				{
					sum += local_a[i * matrixSize + k] * b[k * matrixSize + j];
				}
				local_c[k * matrixSize + i] = sum;  
				printf("%d:local_c[%d]=%d\n", my_rank, k * matrixSize + i, local_c[k * matrixSize + i]);
			}
		}
	}

	// MPI_Gather(local_c, elementsPerProc, MPI_INT, c, elementsPerProc, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Gatherv(local_c, elementsPerProc[my_rank], MPI_INT, c, elementsPerProc, displacements, MPI_INT, 0, MPI_COMM_WORLD);

	// Display output
	if (my_rank == 0)
	{
		// Record the Finish Time
		finish_time = MPI_Wtime();

		printf("running on %d processors\n", comm_sz);
		printf("elapsed time = %.6e seconds\n", finish_time - start_time);
		printf("A:\n");
		printMatrix(a, matrixSize);
		printf("B:\n");
		printMatrix(b, matrixSize);
		printf("C:\n");
		printMatrix(c, matrixSize);
	}
 	
 	free(a);
 	free(b);
 	free(c);
 	free(elementsPerProc);
 	free(displacements);
 	free(local_a);
 	free(local_c);
 	/* Shut down MPI */
	MPI_Finalize();
 	return 0;
}

/**
 * Prints the contents of a Matrix
 * @param int* m 			The matrix that will be printed
 * @param int matrixSize	Size of the matrix
 */
void printMatrix(int *m, int matrixSize)
{
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
			printf("%d ", m[i*matrixSize + j]);
		printf("\n");
	}
}