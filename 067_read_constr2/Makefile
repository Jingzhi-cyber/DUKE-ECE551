code: code.o
	g++ -o code code.o

code.o: code.cpp code.h
	g++ -std=gnu++98 -Wall -Werror -pedantic -c code.cpp

clean:
	rm -f *~ *.o code
