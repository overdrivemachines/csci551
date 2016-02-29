// Author: Dipen Chauhan
// Assignment 1: Parallel Numerical Integration with Open MPI
// Date Due: Wednesday, March 9, 11pm.
// Description: Find the minimum number of trapezoids that gives a correct 
// answer in 14 significant digits for the definite integral as described below
// Calculate the absolute relative true error.
// URL: 
// 

// integrate cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8 from 100 to 600
// Integrate[8 - 2 Cos[x/5] + Cos[x/3] + 5 Sin[x/4], {x, 100, 600}]
// 4003.7209001513268265929134113327386949159025889356124309131658087
// 4003.7209001513
// Formula used: https://math.uc.edu/~halpern/calc2/ho/Errorfornumericalintegation.pdf
// Error = | (Integral(f(x))dx from a to b) - Sum of Trapezoid areas | <= M2 * ((b-a)^3) / (12*(n^2))


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double x);

int main()
{
	double a = 100;	//	Lower Limit
	double b = 600;	//	Upper Limit
	double n;	//	Total Trapezoids (to be calculated)
	double h, x, sum;
	double true_value = 4003.7209001513268265;	//	True value of integral (using 20 digits)
	// 					4003.720900151288788

	// Maxima of 2nd derivative of f(x)
	// maximize(d/dx(d/dx(cos(x/3)-2 cos(x/5)+5 sin(x/4)+8))) from 100 to 600
	double m2 = 0.4652207535280099905181060452713048790500;

	double allowed_error = 0.5 * pow(10,-14) * true_value;

	n = floor(sqrt(m2*pow((b-a), 3)/(12*allowed_error)));

	printf("Number of Trapezoids n = %.0f\n", n);


	// Calculate width of each trapeziod
	h = (b - a) / n;
	sum = 0;

	for (double i = 0; i <= n; i++)
	{
		x = a + i * h;
		sum = sum + f(x);
	}

	sum = h * (sum - (f(a) / 2) - (f(b) / 2));

	printf("True Value = %.15f\n", true_value);
	printf("Approximate Value = %.15f\n", sum);
	printf("True Error = %.15f\n", (true_value - sum));
	printf("Relative True Error = %.15f\n", (true_value - sum) / true_value);

	return EXIT_SUCCESS;
}

double f(double x)
{
	return (cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8); 
}

// Bruteforce way
// do
// {
// 	//	Calculate width of each trapeziod
// 	h = (b - a) / n;
// 	sum = 0;

// 	for (double i = 0; i <= n; i++)
// 	{
// 		x = a + i * h;
// 		sum = sum + f(x); 
// 	}

// 	sum = h * (sum - (f(a) / 2) - (f(b) / 2));

// 	printf("%.0f %f %.15f\n", n, sum, (true_value - sum) / true_value);

// 	n = n * 2;

// } while (fabs((true_value - sum) / true_value) > (0.5 * (10^(-14))));