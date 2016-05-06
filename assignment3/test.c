#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>   

void Hello(void);  /* Thread function */

/*--------------------------------------------------------------------*/
int main(int argc, char* argv[]) 
{
	int thread_count = strtol(argv[1], NULL, 10); 
	//#  pragma omp parallel num_threads(thread_count) 

	printf("There are %d processors available\n", omp_get_num_procs());
	srand (time(NULL));
	#pragma omp parallel num_threads(thread_count) 
	Hello();


	int a = 10;
	int i;
	#pragma omp parallel for num_threads(thread_count) \
		default(none) private(i, a) shared(thread_count)
	for (i = 0; i < thread_count; ++i)
	{
		int my_rank = omp_get_thread_num();
		if (my_rank == 0)
			a = 20;
		else
			a = 30;
	}

	printf("a = %d\n", a);

   return 0; 
}  /* main */

/*-------------------------------------------------------------------
 * Function:    Hello
 * Purpose:     Thread function that prints message
 */
void Hello(void) {
   int my_rank = omp_get_thread_num();
   int thread_count = omp_get_num_threads();

   // sleep(rand()%60+30);
   printf("Hello from thread %d of %d\n", my_rank, thread_count);

}  /* Hello */
