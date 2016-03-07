# From https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# The compiler: gcc for C program
CC = gcc
MC = mpicc

# compiler flags:
#  -g 		adds debugging information to the executable file
#  -Wall	turns on most, but not all, compiler warnings
#  -Wextra	enables some extra warning flags that are not enabled by -Wall.
#  -lm		include the math library
CFLAGS = -g -Wall -Wextra -std=c99
FILES = ./serial ./parallel

all: $(FILES)

serial: serial.c
	$(CC) $(CFLAGS) -o serial serial.c -lm

parallel: parallel.c
	$(MC) $(CFLAGS) -o parallel parallel.c -lm

clean:
	rm -f $(FILES) *.o *~ 