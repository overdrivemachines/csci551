#! /bin/sh
cat *.o* >> combined-output.txt
cat *.e* >> combined-error.txt
rm -f *.o* *.e*