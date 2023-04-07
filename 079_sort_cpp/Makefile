sortLines: sortLines.o
	g++ -o sortLines sortLines.o

sortLines.o: sortLines.cpp
	g++ -std=gnu++98 -Wall -Werror -pedantic -c sortLines.cpp

clean:
	rm -f *~ *.o sortLines
