#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H
#include <stdio.h>
#include <stdlib.h>
#define SIZE_BEGINNER 4
#define SIZE_INTERMEDIATE 6
#define SIZE_HARD 8
#define BOOL int
#define TRUE 1
#define FALSE 0

void grid();
int rules();
int goal_of_the_game();
int beginner_level();
int intermediate_level();
int hard_level();
int modification_grid();

void display(int size, int grille[size][size]);
int** masked_matrix(int size, int grille[size][size]);

#endif //TAKUZU_TAKUZU_H