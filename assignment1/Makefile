# From https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# The compiler: gcc for C program
CC = gcc

# compiler flags:
#  -g 		adds debugging information to the executable file
#  -Wall	turns on most, but not all, compiler warnings
#  -Wextra	enables some extra warning flags that are not enabled by -Wall.
CFLAGS = -g -Wall -Wextra
FILES = ./serial ./parallel

all: $(FILES)

serial: serial.o
	$(CC) $(CFLAGS) -o serial serial.o

parallel: parallel.o
	$(CC) $(CFLAGS) -o parallel parallel.o

clean:
	rm -f $(FILES) *.o *~ 