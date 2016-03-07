#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>     /* For MPI functions, etc */

int main(void)
{
	int comm_sz; /* Number of processes    */
	int my_rank; /* My process rank        */

	/* Start up MPI */
	MPI_Init(NULL, NULL); 

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);


	/* Shut down MPI */
   MPI_Finalize(); 
   return 0;
}

double f(double x)
{
	return (cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8); 
}