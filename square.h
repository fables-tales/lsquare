#ifndef _square_h
#define _square_h

#include <stdbool.h>

typedef struct _latin_square {
    unsigned width;
    char* grid;  
    char* orig_grid;
    char* alphabet;
} latin_square;

void init_latin_square(char*, latin_square*);

void print_latin_square(latin_square*);

bool square_complete(latin_square*);

void solve_latin_square(latin_square*, bool);

bool col_is_filled(unsigned, latin_square*);

bool row_is_filled(unsigned, latin_square*);

bool col_is_valid(unsigned, latin_square*);

bool row_is_valid(unsigned, latin_square*);

#endif
