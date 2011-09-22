all: square slow-square

square: square.c
	clang -O2 square.c -o square

slow-square: square.c
	clang square.c -o slow-square

time: square slow-square
	time ./square
	time ./slow-square
