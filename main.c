#include <stdlib.h>
#include "square.h"

int main() {
    latin_square* my_square = malloc(sizeof(latin_square));
    init_latin_square("abcdefghijlkmnopqrstuvwxyz", my_square);
    solve_latin_square(my_square);
    return 0;
}
