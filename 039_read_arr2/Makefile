test: test.o
	gcc -o test test.o

test.o: test.c
	gcc -std=gnu99 -Wall -Werror -pedantic -c test.c

clean:
	rm -f *.o *~ test
