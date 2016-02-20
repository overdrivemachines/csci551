// Author: Dipen Chauhan
// Assignment 1: Parallel Numerical Integration with Open MPI
// Date Due: Wednesday, March 9, 11pm.
// Description: Find the minimum number of trapezoids that gives a correct 
// answer in 14 significant digits for the definite integral as described below
// Calculate the absolute relative true error.
// 

// integrate cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8 from 100 to 600
// Integrate[8 - 2 Cos[x/5] + Cos[x/3] + 5 Sin[x/4], {x, 100, 600}]
// 4003.7209001513268265929134113327386949159025889356124309131658087
// 4003.7209001513

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>	//	For DBL_MAX

double f(double x);

int main()
{
	double a = 100;	//	Lower Limit
	double b = 600;	//	Upper Limit
	double n = 1;	//	Total Trapezoids
	double h, x, sum = 0;
	double true_value = 4003.72090015132682659;

	printf("n, sum, relative true error\n");
	do
	{
		//	Calculate width of each trapeziod
		h = (b - a) / n;
		sum = 0;

		for (double i = 0; i <= n; i++)
		{
			x = a + i * h;
			sum = sum + f(x); 
		}

		sum = h * (sum - (f(a) / 2) - (f(b) / 2));

		printf("%.0f %f %.15f\n", n, sum, (true_value - sum) / true_value);

		n = n * 2;

	} while (fabs((true_value - sum) / true_value) > (0.5 * (10^(-14))));

	return EXIT_SUCCESS;
}

double f(double x)
{
	return (cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8); 
}