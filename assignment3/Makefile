# From https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# The compiler
IC = icc

# Compiler flags
CFLAGS = -g -Wall -Wextra -std=c99 -openmp

ge: ge.c
	$(IC) $(CFLAGS) -o ge ge.c

clean:
	rm -f ./ge *.o *~