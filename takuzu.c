#include "takuzu.h"
#include <stdio.h>

//int rules(case){}

void display(int grille[size][size]) {
    int line, col;
    for (line = 0; line < size; line++) {
        for (col = 0; col < size; col++) {
            printf("%d ", grille[line][col]);
            printf("\t");
        }
        printf("\n");
    }
}