#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "square.h"

int main(int argc, const char* argv[]) {
    char* alphabet;

    if (argc == 2 && strcmp(argv[1], "-v") != 0) {
        alphabet = (char*) argv[1];
    } else if (argc == 3) {
        alphabet = (char*) argv[2];
    } else {
        alphabet = (char*) "abcdefghijklmnopqrstuvwxyz";
    } 

    bool verbose = (argc >= 2 && strcmp(argv[1], "-v") == 0);

    latin_square* my_square = malloc(sizeof(latin_square));
    init_latin_square(alphabet, my_square);
    solve_latin_square(my_square, verbose);
    if (!verbose) print_latin_square(my_square);
    return 0;
}
