#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <google/profiler.h>
#include "square.h"

int main(int argc, const char* argv[]) {
    char* alphabet;

    bool verbose = false;
    if (argc == 2 && strcmp(argv[1], "-v") != 0) {
        alphabet = (char*) argv[1];
    } else if (argc == 3) {
        alphabet = (char*) argv[2];
        verbose = true;
    } else {
        alphabet = (char*) "abcdefghijklmnopqrstuvwxyz";
    }

//    char* alphabet = "abcdefghijklmnopqrstuvwxyz@";
//    bool verbose = false;


    latin_square* my_square = malloc(sizeof(latin_square));
    init_latin_square(alphabet, my_square);
    clock_t start = clock();
    #ifdef profile
    ProfilerStart("/tmp/bees.prof");
    #endif
    solve_latin_square(my_square, verbose);
    #ifdef profile
    ProfilerStop();
    #endif
    if (!verbose) print_latin_square(my_square);
    clock_t end = clock();
    return 0;
}
