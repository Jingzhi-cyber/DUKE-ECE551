all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4

cyoa-step1: cyoa-step1.o cyoa.o
	g++ -o cyoa-step1 cyoa-step1.o cyoa.o


cyoa-step2: cyoa-step2.o cyoa.o
	g++ -o cyoa-step2 cyoa-step2.o cyoa.o

cyoa-step3: cyoa-step3.o cyoa.o
	g++ -o cyoa-step3 cyoa-step3.o cyoa.o

cyoa-step4: cyoa-step4.o cyoa.o
	g++ -o cyoa-step4 cyoa-step4.o cyoa.o

cyoa-step1.o: cyoa-step1.cpp
	g++ -std=gnu++98 -Werror -Wall -pedantic -c cyoa-step1.cpp

cyoa-step2.o: cyoa-step2.cpp
	g++ -std=gnu++98 -Werror -Wall -pedantic -c cyoa-step2.cpp

cyoa-step3.o: cyoa-step3.cpp
	g++ -std=gnu++98 -Werror -Wall -pedantic -c cyoa-step3.cpp

cyoa-step4.o: cyoa-step4.cpp
	g++ -std=gnu++98 -Werror -Wall -pedantic -c cyoa-step4.cpp

cyoa.o: cyoa.cpp
	g++ -std=gnu++98 -Werror -Wall -pedantic -c cyoa.cpp

clean:
	rm -f *~ *.o cyoa-step1  cyoa-step2 cyoa-step3 cyoa-step4
