// Author: Dipen Chauhan
// Assignment 1: Parallel Numerical Integration with Open MPI
// Date Due: Wednesday, March 9, 11pm.
// Description: Find the minimum number of trapezoids that gives a correct 
// answer in 14 significant digits for the definite integral as described below
// Calculate the absolute relative true error.
// URL: http://www.ecst.csuchico.edu/~judyc/1516S-csci551/assignments/02-integration.html
// 

// Function: integrate cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8 from 100 to 600
// Wolframalpha Input: Integrate[8 - 2 Cos[x/5] + Cos[x/3] + 5 Sin[x/4], {x, 100, 600}]
// Result: 4003.7209001513268265929134113327386949159025889356124309131658087
// Result: 4003.7209001513


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);
double integratef(int a, int b, unsigned int n);

int main()
{
	double a = 100;	//	Lower Limit
	double b = 600;	//	Upper Limit
	unsigned int n = 1;	//	Total Trapezoids (to be calculated)
	double sum;
	double max_arte = 0.5 * pow(10,-14);	//	Maximum Absolute Relative True Error
	double arte;	//	Calculated for every n
	double true_value = 4003.7209001513268265;	//	True value of integral (using 20 digits)

	// double allowed_error = 0.5 * pow(10,-14) * true_value;

	printf("True Value = %f\n", 4003.7209001513268265);
	printf("Max. Absolute Relative True Error = %.15f\n", max_arte);

	// Finding Error for different values of n
	do
	{
		sum = integratef(a, b, n);

		// Calculate absolute relative true error
		arte = fabs((true_value - sum) / true_value);

		printf("%d %f %5.19f\n", n, sum, arte);

		n = n * 2;

		// Loop ends when absolute true error is in range
	} while (arte > max_arte);


	// Print results

	printf("Number of Trapezoids n = %d\n", n);
	printf("True Value = %.19e\n", true_value);
	printf("Approximate Value = %.19e\n", sum);
	printf("True Error = %.19e\n", (true_value - sum));
	printf("Relative True Error = %.19e\n", (true_value - sum) / true_value);
	printf("Absolute Relative True Error = %.19e\n", arte);
	printf("Max Absolute Relative True Error = %.19e\n", max_arte);

	return EXIT_SUCCESS;
}

double f(double x)
{
	return (cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8); 
}

double integratef(int a, int b, unsigned int n)
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

