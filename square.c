#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>
#include "square.h"

const unsigned buffer_size = 1024;

const char placeholder_char = '.'; 

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
    //fill the grid with placeholder characters, this is used in other tests
    //to check whether the grid is full of real characters
    memset(square->grid, placeholder_char, square->width * square->width);
    
    square->alphabet = alphabet;
}

static char get_char_at(latin_square* square, unsigned x, unsigned y) {
    return square->grid[x + (square->width * y)];
}

bool row_is_filled(unsigned row, latin_square* square) {
    char* row_ptr = square->grid + row * square->width;
    int i;
    for (i = 0; i < square->width; i++) {
        if (row_ptr[i] == placeholder_char) return false;
    }

    return true;
}

bool col_is_filled(unsigned col, latin_square* square) {
    int i;
    for (i = 0; i < square->width; i++) {
        char* row_ptr = square->grid + i * square->width;
        if (row_ptr[col] == placeholder_char) return false;
    }

    return true;
}

bool row_is_valid(unsigned row, latin_square* square) {
    char* row_ptr = square->grid + row * square->width;
    unsigned c_count1, c_count2;
    char c_char1, c_char2;
    for (c_count1 = 0; c_count1 < square->width; c_count1++) {
        c_char1 = row_ptr[c_count1];
        if (c_char1 != placeholder_char) {
            for (c_count2 = 0; c_count2 < square->width; c_count2++) {
                c_char2 = row_ptr[c_count2];
                if (c_char2 != placeholder_char && c_count1 != c_count2 && c_char1 == c_char2) {
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

        if (r_char1 != placeholder_char) {

            for (r_count2 = 0; r_count2 < square->width; r_count2++) {
                r_char2 = get_char_at(square, col, r_count2);

                if (r_char2 != placeholder_char && r_count1 != r_count2 && r_char1 == r_char2) return false;
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

static void reset_row(unsigned row, latin_square* square) {
    char* row_ptr = square->grid + row * square->width;
    memset(row_ptr, placeholder_char, square->width);
}

static void randomize_char(latin_square* square, unsigned x, unsigned y) {
    square->grid[y * square->width + x] = square->alphabet[rand() % square->width];
}

void solve_latin_square(latin_square* square, bool verbose) {
    unsigned working_row = 0;
    unsigned charpos = 0; 
    unsigned tries = 0;
    int i;
    //seed the random number generator so we get different squares each time
    srand(clock());
    while (!square_complete(square)) {
        //reset the last printed line
        if (verbose) putchar('\r');

        //set the current char at charpos to a random one from the alphabet
        randomize_char(square, charpos, working_row);     
        //print the current row
        if (verbose) {
            char* row_ptr = square->grid + working_row * square->width;
            for (i = 0; i < square->width; i++) {
                putchar(row_ptr[i]);
                putchar(' ');
            }
            fflush(stdout);
        }

        //if the row is valid move to the next row
        if (row_is_valid(working_row, square) && col_is_valid(charpos, square)) {
           tries = 0; 

           if (++charpos == square->width) {
               charpos = 0;
               working_row += 1;
               if (verbose) {
                   putchar('\n');
                   fflush(stdout);
               }
           }
        //if we've tried lots of different values reset the whole row
        } else if (tries++ >= 100) {
            reset_row(working_row, square);
            charpos = 0;
        }
    }
}



