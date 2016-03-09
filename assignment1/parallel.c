#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>     /* For MPI functions, etc */

double f(double x);
double integrate(double a, double b, double n);

int main(void)
{
	int comm_sz; /* Number of processes    */
	int my_rank; /* My process rank        */
	double a = 100;	//	Lower Limit - will change with user input
	double b = 600;	//	Upper Limit - will change with user input
	double n = 33554432;	//	Total Trapezoids - will change with user input
	int iparams[3]; // Params for Integration: a, b and n
	double h;	//	Width of each trapezoid
	double sum;	//	Global sum of all trapezoid areas
	
	/* Start up MPI */
	MPI_Init(NULL, NULL); 

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0)
	{
		printf("Enter a, b and n\n");
		scanf("%lf %lf %lf", &a, &b, &n);
		iparams[0] = a;
		iparams[1] = b;
		iparams[2] = n;
	}

	MPI_Bcast(iparams, 3, MPI_INT, 0, MPI_COMM_WORLD);
	// printf("%d: %f %f %f\n", my_rank, iparams[0], iparams[1], iparams[2]);

	// Calculate width of each trapezoid
	h = (b - a) / n;

	double local_a, local_b, local_n, local_sum;

	local_n = h / comm_sz;	// Number of trapezoids for each process
	local_a = a + my_rank*local_n; // Left boundary for each process
	local_b = local_a + local_n*h;	// Right boundary for each process

	printf("Process %d: %f - %f\n", my_rank, local_a, local_b);

	local_sum = 0;


	MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (my_rank == 0)
	{
		printf("Total Sum = %f\n", sum);
	}

	

	/* Shut down MPI */
   MPI_Finalize(); 
   return 0;
}

double f(double x)
{
	return (cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8); 
}

double integratef(double a, double b, double n)
{
	double h, x, sum;

	//	Calculate width of each trapeziod
	h = (b - a) / (double) n;
	sum = 0;

	// Add the areas of all the trapezoids
	// for (double i = 0; i <= n; i++)
	// {
	// 	x = a + i * h;
	// 	sum = sum + f(x); 
	// }

	// The first and last terms need to be halved
	// sum = h * (sum - (f(a) / 2) - (f(b) / 2));

	// Textbook way...
	sum = (f(a) + f(b)) / 2.0;
	for (unsigned int i = 1; i <= n-1; i++)
	{
		x = a + i * h;
		sum += f(x); 
	}
	sum = h * sum;

	return sum;
}