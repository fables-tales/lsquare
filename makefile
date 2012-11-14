all: square test

OBJS = square.o main.o test.o

$(OBJS): %.o: %.c
	gcc -O2 -c $*.c

square: square.o main.o
	gcc -O2 square.o main.o -o square

test: square.o test.o
	gcc -O2 square.o test.o -o test

prof-square:
	gcc -g -O2 -Wl,-no_pie -c main.c -o main.o -Dprofile
	gcc -g -O2 -Wl,-no_pie -c square.c -o square.o -Dprofile
	gcc -g -O2 -Wl,-no_pie square.o main.o -lprofiler -o prof-square
	rm main.o square.o

time: square
	time ./square

clean:
	rm -f *.o
	rm -f square prof-square
	rm -f test
