#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "square.h"

void test() {
    latin_square* my_square = malloc(sizeof(latin_square));
    init_latin_square("abcd", my_square);
    assert(col_is_filled(0, my_square) == 0);
    assert(row_is_filled(0, my_square) == 0);
    assert(col_is_valid(0, my_square) == 1);
    assert(row_is_valid(0, my_square) == 1);

    my_square->grid[0] = 'a';
    assert(col_is_filled(0, my_square) == 0);
    assert(row_is_filled(0, my_square) == 0);
    assert(col_is_valid(0, my_square) == 1);
    assert(row_is_valid(0, my_square) == 1);

    my_square->grid[1] = 'a';
    assert(col_is_filled(0, my_square) == 0);
    assert(row_is_filled(0, my_square) == 0);
    assert(col_is_valid(0, my_square) == 1);
    assert(row_is_valid(0, my_square) == 0);

    my_square->grid[1] = 'b';
    assert(col_is_filled(0, my_square) == 0);
    assert(row_is_filled(0, my_square) == 0);
    assert(col_is_valid(0, my_square) == 1);
    assert(row_is_valid(0, my_square) == 1);
    
    int i;
    for (i = 0; i < my_square->width; i++) {
        char* row_ptr = my_square->grid + i * my_square->width;
        memcpy(row_ptr, my_square->alphabet, 4);
        assert(row_is_filled(i, my_square) == 1);
        assert(row_is_valid(i, my_square) == 1);

        row_ptr[3] = '.';
        assert(row_is_filled(i, my_square) == 0);
        assert(row_is_valid(i, my_square) == 1);

        row_ptr[3] = 'd';
        row_ptr[0] = '.';
        assert(row_is_filled(i, my_square) == 0);
        assert(row_is_valid(i, my_square) == 1);

    }

    free(my_square->grid); 
    init_latin_square(my_square->alphabet, my_square);

    my_square->grid[0] = 'a';
    my_square->grid[4] = 'b';
    assert(col_is_filled(0, my_square) == 0);
    assert(col_is_valid(0, my_square) == 1);

    my_square->grid[8] = 'c';
    my_square->grid[12] = 'd';
    assert(col_is_filled(0, my_square) == 1);
    assert(col_is_valid(0, my_square) == 1);

    my_square->grid[0] = '.';
    assert(col_is_filled(0, my_square) == 0);
    assert(col_is_valid(0, my_square) == 1);

    my_square->grid[0] = 'a';
    my_square->grid[4] = 'a';
    my_square->grid[8] = 'a';
    my_square->grid[12] = 'a';
    assert(col_is_filled(0, my_square) == 1);
    assert(col_is_valid(0, my_square) == 0);

    latin_square* my_square_2 = malloc(sizeof(latin_square));
    init_latin_square("ab", my_square_2);
    my_square_2->grid = "abba";
    assert(square_complete(my_square_2));

    init_latin_square("abcd", my_square_2);
    solve_latin_square(my_square_2, false);
    assert(square_complete(my_square_2));
}

int main() {
    test();
    return 0;
}
