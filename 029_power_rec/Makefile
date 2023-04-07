CFLAGS= -std=gnu99 -pedantic -Wall -Werror
myPower: power.o test-power.o
	gcc -o myPower power.o test-power.o

power.o: power.c
	gcc $(CFLAGS) -c  power.c

test-power.o: test-power.c
	gcc $(CFLAGS) -c  test-power.c

clean:
	rm -f *.o  *~
