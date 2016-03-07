#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>     /* For MPI functions, etc */

double f(double x);
double integrate(int a, int b, int n);

int main(void)
{
	int comm_sz; /* Number of processes    */
	int my_rank; /* My process rank        */
	int iparams[3];

	/* Start up MPI */
	MPI_Init(NULL, NULL); 

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0)
	{
		printf("Enter a, b and n\n");
		scanf("%d %d %d", &iparams[0], &iparams[1], &iparams[2]);

		// printf("%d %d %d\n", iparams[0], iparams[1], iparams[2]);
		
	}

	MPI_Bcast(iparams, 3, MPI_INT, 0, MPI_COMM_WORLD);
	printf("%d: %d %d %d\n", my_rank, iparams[0], iparams[1], iparams[2]);	

	/* Shut down MPI */
   MPI_Finalize(); 
   return 0;
}

double f(double x)
{
	return (cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8); 
}

double integrate(int a, int b, int n)
{
	double h, x, sum;

	//	Calculate width of each trapeziod
	h = (b - a) / (double) n;
	sum = 0;

	// Add the areas of all the trapezoids
	for (double i = 0; i <= n; i++)
	{
		x = a + i * h;
		sum = sum + f(x); 
	}

	// The first and last terms need to be halved
	sum = h * (sum - (f(a) / 2) - (f(b) / 2));

	return sum;
}