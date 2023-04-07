CFLAGS= -std=gnu99 -pedantic -Wall -Werror
subseq: maxSeq.o test-subseq.o
	gcc  -o subseq maxSeq.o test-subseq.o

maxSeq.o: maxSeq.c
	gcc $(CFLAGS) -c maxSeq.c

test-subseq.o: test-subseq.c
	gcc $(CFLAGS) -c test-subseq.c

clean:
	rm -f subseq *.o *~
