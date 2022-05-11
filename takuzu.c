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


void display(int size, int** grid){
    int line,col;
    for  (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++) {
            printf("%d\t", grid[line][col]);
        }
        printf("\n");
    }
}

void display_masked(int size, int grid[size][size], int** mask){
    int line,col;
    for  (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++) {
            if (mask[line][col] == 1){
                printf("%d\t", grid[line][col]);}
            else{
                printf("*\t");
            }
        }
        printf("\n");
    }
}

int** masked_matrix(int size){
    int line,col;
    int** masked_grid = (int**) malloc(size*sizeof(int*));
    for (line=0 ; line < size ; line++){
        masked_grid[line] = (int*) malloc(size*sizeof(int));
    }
    for (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++){
            masked_grid[line][col] = rand()%2;
        }
    }
    return masked_grid;
}


void modification_grid(int size, int grid[size][size]){
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
    if (TRUE){
        for (int i=0 ; i<SIZE_BEGINNER ; i++){
            printf("\t");
            for (int j=0 ; j<SIZE_BEGINNER ; j++)
                //printf("%c\t", mask_grid_4x4[i][j]);
            printf("\n");
        }
    }
    verification = TRUE;
}

int beginner_level(){
    int grid_4x4[SIZE_BEGINNER][SIZE_BEGINNER]=
            {0, 1, 0, 1,
             1, 0, 0, 1,
             1, 0, 1, 0,
             0, 1, 1, 0
            };

    int mask_grid_4x4[SIZE_BEGINNER][SIZE_BEGINNER]=
            {0, 0, 0, 0,
             0, 1, 1, 0,
             1, 0, 0, 0,
             0, 0, 0, 0
            };
    //display_masked(SIZE_BEGINNER,grid_4x4[SIZE_BEGINNER][SIZE_BEGINNER],mask_grid_4x4[SIZE_BEGINNER][SIZE_BEGINNER]);
}

int intermediate_level(){
    return 0;
}

int hard_level(){
    return 0;
}