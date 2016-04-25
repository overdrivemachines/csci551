# From https://www.cs.swarthmore.edu/~newhall/unixhelp/howto_makefiles.html
# The compiler
IC = icc

# Compiler flags
CFLAGS = -g -Wall -Wextra -openmp -Ofast

ge: ge.c
	$(IC) $(CFLAGS) -o ge ge.c

debug: ge.c
	$(IC) $(CFLAGS) -DDEBUG=1 -o ge ge.c

test: test.c
	$(IC) $(CFLAGS) -o test test.c

clean:
	rm -f ./ge ./test *.o *~