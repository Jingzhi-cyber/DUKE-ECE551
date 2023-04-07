test: test.o
	gcc -o test test.o

test.o: test.c
	gcc -std=gnu99 -pedantic -Wall -Werror -c test.c

clean:
	rm -f test *.o *~
