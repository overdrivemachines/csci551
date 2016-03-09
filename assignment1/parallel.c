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
	double a, b, n;
	double integrationParams[3];	// Holds Lower Bound, Upper Bound and Number of Trapezoids
	double h;	//	Width of each trapezoid
	double sum;	//	Global sum of all trapezoid areas
	double start_time, finish_time;
	
	/* Start up MPI */
	MPI_Init(NULL, NULL); 

	/* Get the number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

	/* Get my rank among all the processes */
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if (my_rank == 0)
	{
		printf("Enter a, b and n\n");
		scanf("%lf %lf %lf", &integrationParams[0], &integrationParams[1], &integrationParams[2]);
		printf("Running on %d cores.\n", comm_sz);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	if (my_rank == 0)
	{
		// Record the Start Time
		start_time = MPI_Wtime();
	}

	// Sending a, b and n to all the processes
	MPI_Bcast(integrationParams, 3, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	a = integrationParams[0];
	b = integrationParams[1];
	n = integrationParams[2];

	// printf("%d: %f %f %f\n", my_rank, integrationParams[0], integrationParams[1], integrationParams[2]);

	// Calculate width of each trapezoid
	h = (b - a) / (double) n;

	double local_a, local_b, local_n, local_sum;

	local_n = h / comm_sz;	// Number of trapezoids for each process
	local_a = a + my_rank*local_n; // Left boundary for each process
	local_b = local_a + local_n*h;	// Right boundary for each process

	// printf("Process %d:\n", my_rank);
	// printf("Width of Each Trapezoid = %f\n", h);
	printf("Process %d: %f: %f - %f\n", my_rank, local_n, local_a, local_b);

	local_sum = 0;


	MPI_Reduce(&local_sum, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

	if (my_rank == 0)
	{
		// Record the Finish Time
		finish_time = MPI_Wtime();

		printf("Elapsed time = %.6e\n", finish_time - start_time);
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