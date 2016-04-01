# From https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# The compiler
MC = mpicc

# compiler flags:
#  -g 		adds debugging information to the executable file
#  -Wall	turns on most, but not all, compiler warnings
#  -Wextra	enables some extra warning flags that are not enabled by -Wall.
CFLAGS = -g -Wall -Wextra -std=c99

matrixmult: matrixmult.c
	$(MC) $(CFLAGS) -o matrixmult matrixmult.c

clean:
	rm -f ./matrixmult *.o *~