#ifndef TAKUZU_TAKUZU_H
#define TAKUZU_TAKUZU_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE_BEGINNER 4
#define SIZE_ADVANCED 8
#define BOOL int
#define TRUE 1
#define FALSE 0


int** copy_array(int size,int** original, int** copy);

//   --------------

void rules();
void goal_of_the_game();


//             --PART 1--


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


int** solve(int size, int** grid);
int** auto_complete_row_double(int size, int** grid);
int** auto_complete_col_double(int size, int** grid);
int** auto_complete_row_sandwich(int size, int** grid);
int** auto_complete_col_sandwich(int size, int** grid);
int** auto_complete_row_originality(int size, int** grid);
int** auto_complete_col_originality(int size, int** grid);
int** auto_complete_row(int size, int** grid);
int** auto_complete_col(int size, int** grid);


//             --PART 3--


int** generate_grid(int size, char manner);

//   --------------


void display(int size, int** grid);
int** generate_mask(int size, char manner);
int** apply_mask(int size, int** grid, int** mask);
int** generate_null_array(int size);
BOOL compare_arrays(int size, int** array1, int** array2);
int count_occurrences(int size, int const* array, int nb_sought);


#endif //TAKUZU_TAKUZU_H