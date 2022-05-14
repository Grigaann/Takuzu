#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE_BEGINNER 4
#define SIZE_ADVANCED 8
#define BOOL int
#define TRUE 1
#define FALSE 0


int** from_static_to_dynamic(int size, int static_grid[size][size]);
int** copy_array(int size,int** original, int** copy);

//--------------

void rules();
void goal_of_the_game();

//             --PART 1--

void display(int size, int** grid);
int** generate_mask(int size, char manner);
int** apply_mask(int size, int** grid, int** mask);
int** generate_null_array(int size);
BOOL compare_arrays(int size, int** array1, int* *array2);

//--------------

void is_playing(int size, int** solution);

int** modify_grid(int size, int** grid_game, int** mask, int** solution, int* life_points);

int verification(int size, int** grid, BOOL need_help, int life_points);
int verify_row_count(int size, int** grid);
int verify_col_count(int size, int** grid);
int verify_row_originality(int size, int** grid);
int verify_col_originality(int size, int** grid);
int verify_row_coherence(int size, int** grid);
int verify_col_coherence(int size, int** grid);

//             --PART 2--

int** solve(int** grid);

//             --PART 3--


#endif //TAKUZU_TAKUZU_H