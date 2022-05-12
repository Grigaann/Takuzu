#include "takuzu.h"


void rules(){
    printf("These are the rules of the Takuzu :\n");
    printf("1 - Each column and line have to contain the same number of 0 and 1\n"
           "2 - Columns or lines that are the same are forbidden\n"
           "3 - It can't have more than two of 1 or 0 nearby");
}

void goal_of_the_game(){
    printf("The goal of the game :\n");
    printf("- Fill the grid with the same amount of 0 and 1 on each column and line without any identical line or column and it can't have more than two 1 or 0 nearby.\n");
}

int** generate_null_array(int size){
    int line;
    int** grid = (int**) malloc(size*sizeof(int*));
    for (line=0 ; line < size ; line++){
        grid[line] = (int*) malloc(size*sizeof(int));
    }
    return grid;
}

void display(int size, int** grid){
    int line,col;
    for  (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++) {
            if (grid[line][col] == -1){
                printf("*\t");
            } else{
                printf("%d\t", grid[line][col]);
            }
        }
        printf("\n");
    }
}

int** apply_mask(int size, int** grid, int** mask){
    int line,col;
    int** grid_game = generate_null_array(size);
    for  (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++) {
            if (mask[line][col] == 1){
                grid_game[line][col] = grid[line][col];
            }
            else{
                grid_game[line][col] = -1;
            }
        }
    }
    return grid_game;
}

int** generate_mask(int size, char manner){
    int line,col;
    int** masked_grid = generate_null_array(size);
    for (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++){
            if (manner == 'a')
                masked_grid[line][col] = rand()%2;
            else if (manner == 'm'){
                do {
                    printf("Enter 0 or 1 to be the value in line %d and column %d :\n", line, col);
                    scanf("%d", &masked_grid[line][col]);
                } while (masked_grid[line][col] != 1 && masked_grid[line][col] != 0);
            }
        }
    }
    return masked_grid;
}


void modify_grid(int size, int** grid){
    BOOL verification = FALSE;
    int line_modif, column_modif, number_modif;

    printf("Which one do you want to change ?\n");
    printf("Line number :\n");
    scanf("%d", &line_modif);
    while(line_modif>size || line_modif<1){
        printf("Sorry the line is out of range.\n");
        printf("Please enter a new line number between 1 and %d :\n", size);
        scanf("%d", &line_modif);
    }

    printf("Column number : \n");
    scanf("%d", &column_modif);
    while(column_modif>size || column_modif<1){
        printf("Sorry, the column is out of range.\n");
        printf("Please enter a new column number between 1 and %d :", size);
        scanf("%d", &column_modif);
    }

    printf("With which number do you want to replace (1 or 0) ?\n");
    scanf("%d", &number_modif);

    while(number_modif<0 || number_modif>1){
        printf("Sorry you only can enter 1 or 0.");
        printf("With which number do you want to replace (ONLY 1 or 0) ?\n");
        scanf("%d", number_modif);
    }
}

int verification(int size, int** grid,int** mask, int pos_i, int pos_j, int number){
    BOOL verification = TRUE;
    if (!verify_row_count(size, grid)){
        verification = FALSE;
    }
    if (!verify_col_count(size, grid)){
        verification = FALSE;
    }
    if (!verify_row_originality(size, grid)){
        verification = FALSE;
    }
    if (!verify_col_originality(size, grid)){
        verification = FALSE;
    }
    if(!verify_row_coherence(size,grid)){
        verification = FALSE;
    }
    if(!verify_col_coherence(size,grid)){
        verification = FALSE;
    }
    return verification;
}

int verify_row_count(int size, int** grid){
    int line,col;
    BOOL verif = TRUE;
    for  (line=0 ; line < size ; line++){
        int cpt_0 = 0,cpt_1 = 0;
        for (col=0 ; col < size ; col++) {
            if (grid[line][col] == 1)
                cpt_1++;
            if (grid[line][col] == 0)
                cpt_0++;
            if(cpt_0 > size/2 || cpt_1> size/2){
                    printf("Invalid move ! At line %d : nb0 = %d & nb1 = %d\n",line+1,cpt_0,cpt_1);
                    verif = FALSE;
            }
        }
    }
    return verif;
}


int verify_col_count(int size, int** grid){
    int line,col;
    BOOL verif = TRUE;
    for  (col = 0 ; col < size ; col++){
        int cpt_0 = 0,cpt_1 = 0;
        for (line = 0 ; line < size ; line++) {
            if (grid[line][col] == 1)
                cpt_1++;
            if (grid[line][col] == 0)
                cpt_0++;
            if(cpt_0 > size/2 || cpt_1> size/2){
                printf("Invalid move ! At col %d : nb0 = %d & nb1 = %d\n",col+1,cpt_0,cpt_1);
                verif = FALSE;
            }
        }
    }
    return verif;
}

int verify_row_originality(int size, int** grid){
    int line,other_line,col,identical;
    BOOL verif = TRUE;
    for (line = 0 ; line < size ; line++){
        for (other_line = line+1 ; other_line < size ; other_line++){
            identical = 0;
            for  (col = 0 ; col < size ; col++){
                if (grid[line][col] == grid[other_line][col]){
                    identical++;
                }
            }
            if (identical == size){
                printf("Invalid move ! The line %d is identical to the line %d\n",line+1,other_line+1);
                verif = FALSE;
            }
        }
    }
    return verif;
}

int verify_col_originality(int size, int** grid){
    int line,col,other_col,identical;
    BOOL verif = TRUE;
    for (col = 0 ; col < size ; col++){
        for (other_col = col+1 ; other_col < size ; other_col++){
            identical = 0;
            for  (line = 0 ; line < size ; line++) {
                if (grid[line][col] == grid[line][other_col]) {
                    identical++;
                }
            }
            if (identical == size) {
                printf("Invalid move ! The column %d is identical to the column %d\n", col+1, other_col+1);
                verif = FALSE;
            }
        }
    }
    return verif;
}

int verify_row_coherence(int size, int** grid) {
    BOOL verif = TRUE;
    int line, col, cpt_1 = 0, cpt_0 = 0;
    for (line = 0; line < size; line++) {
        for (col = 0; col < size; col++) {
            if (grid[line][col] == 1) {
                cpt_1++;
                cpt_0 = 0;
            }
            if (grid[line][col] == 0) {
                cpt_0++;
                cpt_1 = 0;
            }
            if (cpt_0 == 3 || cpt_1 == 3){
                printf("The line %d contains a succession of too much 1s or 0s",line);
                verif = FALSE;
            }
        }
    }
    return verif;
}

int verify_col_coherence(int size, int** grid){
    BOOL verif = TRUE;
    int line,col;
    for  (col = 0 ; col < size ; col++){
        int cpt_1=0,cpt_0=0;
        for (line = 0 ; line < size ; line++) {
            if (grid[line][col] == 1){
                cpt_1++;
                cpt_0 = 0;
            }
            if (grid[line][col] == 0){
                cpt_0++;
                cpt_1 = 0;
            }
            if (cpt_0 == 3 || cpt_1 == 3){
                printf("The column %d contains a succession of too much 1s or 0s\n",col+1);
                verif = FALSE;
            }
        }
    }
    return verif;
}




int** from_static_to_dynamic(int size, int static_grid[size][size]){
    int line,col;
    int** dynamic_grid = (int**) malloc(size*sizeof(int*));
    for (line=0 ; line < size ; line++){
        dynamic_grid[line] = (int*) malloc(size*sizeof(int));
        for (col=0 ; col<size ; col++){
            dynamic_grid[line][col] = static_grid[line][col];
        }
    }
    return dynamic_grid;
}

int** copy_array(int size,int** original, int** copy){
    int line,col;
    for (line=0 ; line < size ; line++){
        for (col=0 ; col<size ; col++){
            copy[line][col] = original[line][col];
        }
    }
    return copy;
}
