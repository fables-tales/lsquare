#include <stdlib.h>
#include <string.h>
#include "square.h"

int main(int argc, const char* argv[]) {
    latin_square* my_square = malloc(sizeof(latin_square));
    init_latin_square("abcdefghijlkmnopqrstuvwxyz1234567890", my_square);
    bool verbose = (argc >= 2 && strcmp(argv[1], "-v") == 0);
    solve_latin_square(my_square, verbose);
    if (!verbose) print_latin_square(my_square);
    return 0;
}
