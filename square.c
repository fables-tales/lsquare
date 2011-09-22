#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>


typedef struct _latin_square {
    unsigned width;
    char* grid;  
    char* alphabet;
} latin_square;

const unsigned buffer_size = 1024;

char* read_file(char* filename) {
    char* buffer = (char*)(malloc(sizeof(char) * buffer_size));
    unsigned buf_len = buffer_size;
    unsigned n = 0;
    FILE* f_ptr = fopen(filename, "r");
    while (!feof(f_ptr)) {
        unsigned raw_char = fgetc(f_ptr);
        if (raw_char == -1) break;
        else {
            char real_char = (char)raw_char;
            buffer[n++] = real_char;
        }

    }
    return buffer;

}

void strip(char* string) {
    unsigned i = 0;
    for (i = 0; i < strlen(string); i++) {
        if (string[i] == '\n' || string[i] == ' ') {
            strcpy(string + i, string + i + 1);
        }
    }
}

void init_latin_square(char* alphabet, latin_square* square) {
    square->width = strlen(alphabet);
    square->grid = malloc(sizeof(char) * square->width * square->width);
    memset(square->grid, '.', square->width * square->width);
    square->alphabet = alphabet;
}

static char get_char_at(latin_square* square, unsigned x, unsigned y) {
    return square->grid[x + (square->width * y)];
}

bool row_is_filled(unsigned row, latin_square* square) {
    char* row_ptr = square->grid + row * square->width;
    int i;
    for (i = 0; i < square->width; i++) {
        if (row_ptr[i] == '.') return false;
    }

    return true;
}

bool col_is_filled(unsigned col, latin_square* square) {
    int i;
    for (i = 0; i < square->width; i++) {
        char* row_ptr = square->grid + i * square->width;
        if (row_ptr[col] == '.') return false;
    }

    return true;
}

bool row_is_valid(unsigned row, latin_square* square) {
    char* row_ptr = square->grid + row * square->width;
    unsigned c_count1, c_count2;
    char c_char1, c_char2;
    for (c_count1 = 0; c_count1 < square->width; c_count1++) {
        c_char1 = row_ptr[c_count1];
        if (c_char1 != '.') {
            for (c_count2 = 0; c_count2 < square->width; c_count2++) {
                c_char2 = row_ptr[c_count2];
                if (c_char2 != '.' && c_count1 != c_count2 && c_char1 == c_char2) {
                    return false;
                }

            }

        }

    }

    return true;

}

bool col_is_valid(unsigned col, latin_square* square) {
    unsigned r_count1, r_count2;
    char r_char1, r_char2;
    for (r_count1 = 0; r_count1 < square->width; r_count1++) {
        r_char1 = get_char_at(square, col, r_count1);

        if (r_char1 != '.') {

            for (r_count2 = 0; r_count2 < square->width; r_count2++) {
                r_char2 = get_char_at(square, col, r_count2);

                if (r_char2 != '.' && r_count1 != r_count2 && r_char1 == r_char2) return false;
            }

        }

    }

    return true;
}

void print_latin_square(latin_square* square) {
    unsigned i = 0;
    unsigned j = 0;
    unsigned width = square->width;
    for (j = 0; j < width; j++) {
        char* row = square->grid + (j * width);
        for (i = 0; i < width; i++) {
            putchar(row[i]);
            putchar(' ');
        }

        putchar('\n');
    }
}

void test();

bool square_complete(latin_square* square) {
    int i;
    for (i = 0; i < square->width; i++) {
        if (!(col_is_filled(i, square) &&
              row_is_filled(i, square) &&
              row_is_valid(i, square) &&
              col_is_valid(i, square))) return false;
    }

    return true;
}

void solve_latin_square(latin_square* square);


int main() {
    test();
    latin_square* my_square = malloc(sizeof(latin_square));
    init_latin_square("abcdefghijlkmnopqrstuvwxyz", my_square);
    solve_latin_square(my_square);
    return 0;
}

void reset_row(unsigned row, latin_square* square) {
    char* row_ptr = square->grid + row * square->width;
    memset(row_ptr, '.', square->width);
}

void randomize_char(latin_square* square, unsigned x, unsigned y) {
    square->grid[y * square->width + x] = square->alphabet[rand() % square->width];
}

void solve_latin_square(latin_square* square) {
    unsigned working_row = 0;
    unsigned charpos = 0; 
    unsigned tries = 0;
    int i;
    while (!square_complete(square)) {
        putchar('\r');
        randomize_char(square, charpos, working_row);     
        char* row_ptr = square->grid + working_row * square->width;
        for (i = 0; i < square->width; i++) {
            putchar(row_ptr[i]);
            putchar(' ');
        }
        fflush(stdout);
        if (row_is_valid(working_row, square) && col_is_valid(charpos, square)) {
           tries = 0; 

           if (++charpos == square->width) {
               charpos = 0;
               working_row += 1;
               putchar('\n');
               fflush(stdout);
           }

        } else if (tries++ >= 100) {
            reset_row(working_row, square);
            charpos = 0;
        }
    }
}

void test() {
    latin_square* my_square = malloc(sizeof(latin_square));
    init_latin_square("abcd", my_square);
    print_latin_square(my_square);
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
}


