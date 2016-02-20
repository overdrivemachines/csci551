// integrate cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8 from 100 to 600
// Integrate[8 - 2 Cos[x/5] + Cos[x/3] + 5 Sin[x/4], {x, 100, 600}]
// 4003.720900151326826592913

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>	//	For DBL_MAX

double f(double x);

int main()
{
	double a = 100;	//	Lower Limit
	double b = 600;	//	Upper Limit
	double n = 2;	//	Total Trapezoids
	double h, x, sum = 0;





	printf("hello world\n");
	printf("f(%f) = %f\n", a, f(a));
	printf("f(%f) = %f\n", b, f(b));

	//	Calculate width of each trapeziod
	h = (b - a) / n;

	for (double i = 0; i <= n; i++)
	{
		x = a + i * h;
		sum = sum + f(x); 
	}

	sum = h * (sum - (f(a) / 2) - (f(b) / 2));

	printf("Sum of trapeziods = %f\n", sum);

	return EXIT_SUCCESS;
}

double f(double x)
{
	return (cos(x/3) - 2*cos(x/5) + 5*sin(x/4) + 8); 
}