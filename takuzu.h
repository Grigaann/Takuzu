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
void rules();
void goal_of_the_game();
int beginner_level();
int intermediate_level();
int hard_level();
void modification_grid(int size, int grid[size][size]);

void display(int size, int** grid);
void display_masked(int size, int grid[size][size], int** mask);
int** masked_matrix(int size);

#endif //TAKUZU_TAKUZU_H