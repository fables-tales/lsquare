all: square test

OBJS = square.o main.o test.o

$(OBJS): %.o: %.c
	clang -O2 -c $*.c

square: square.o main.o
	clang -O2 square.o main.o -o square

test: square.o test.o
	clang -O2 square.o test.o -o test

time: square
	time ./square

clean:
	rm -f *.o
	rm -f square
	rm -f test
