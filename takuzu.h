#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H
#include <stdio.h>
#include <stdlib.h>
#define SIZE_BEGINNER 4
#define SIZE_ADVANCED 8
#define BOOL int
#define TRUE 1
#define FALSE 0


int** from_static_to_dynamic(int size, int static_grid[size][size]);
int** copy_array(int size,int** original, int** copy);

void rules();
void goal_of_the_game();


void display(int size, int** grid);
int** generate_mask(int size, char manner);
int** generate_null_array(int size);


void modify_grid(int size, int** grid);

int verification(int size, int** grid,int** mask, int pos_i, int pos_j, int number);
int verify_row_count(int size, int** grid);
int verify_col_count(int size, int** grid);
int verify_row_originality(int size, int** grid);
int verify_col_originality(int size, int** grid);
int verify_row_coherence(int size, int** grid);
int verify_col_coherence(int size, int** grid);


#endif //TAKUZU_TAKUZU_H