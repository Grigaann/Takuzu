#include "takuzu.h"

void display(int size, int grille[size][size]){
    int line,col;
    for  (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++) {
            printf("%d\t", grille[line][col]);
        }
        printf("\n");
    }
}

int** masked_matrix(int size, int grille[size][size]){
    int line,col;
    int** grid = (int**) malloc(size*sizeof(int*));
    for (line=0 ; line < size ; line++){
        grid[line] = (int*) malloc(size*sizeof(int));
    }
    for (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++){
            grid[line][col] = rand()%2;
            printf("%d\t",grid[line][col]);
        }
        printf("\n");
    }
    return grid;
}


int rules()
{
    printf("These are the rules of the Takuzu : \n");
    printf("1 - Each column and line have to contain the same number of 0 and 1 \n"
           "2 - Columns or lines that are the same are forbidden \n"
           "3 - It can't have more than two of 1 or 0 nearby");
    return 0;
}

int goal_of_the_game()
{
    printf("The goal of the game : \n");
    printf("- Fill the grid with the same amount of 0 and 1 on each columns and lines without identical line or column and it can't have more than two of 1 or 0 nearby \n");
}

int modification_grid(size_of_the_grid)
{
    int line_modification, column_modification, number_modification;

    printf("Which one do you want to change ? : \n");
    printf("Line number : \n");
    scanf("%d", &line_modification);
    while(line_modification>size_of_the_grid || line_modification<1)
    {
        printf("Sorry the line is out of range. \n");
        printf("Please enter a new line number between 1 and %d: \n", size_of_the_grid);
        scanf("%d", &line_modification);
    }

    printf("Column number : \n");
    scanf("%d", &column_modification);
    while(column_modification>size_of_the_grid || column_modification<1)
    {
        printf("Sorry the column is out of range. \n");
        printf("Please enter a new column number between 1 and %d: \n", size_of_the_grid);
        scanf("%d", &column_modification);
    }

    printf("With which number do you want to modify (1 or 0) ? : \n");
    scanf("%d", number_modification);

    while(number_modification<0 || number_modification>1)
    {
        printf("Sorry you only can enter 1 or 0.");
        printf("With which number do you want to modify (ONLY 1 or 0) ? : \n");
        scanf("%d", number_modification);
    }



}

int beginner_level()
{
    int grid_4x4[SIZE_BEGINNER][SIZE_BEGINNER]=
            {{'0', '1', '0', '1'},
             {'1', '0', '0', '1'},
             {'1', '0', '1', '0'},
             {'0', '1', '1', '0'}
            };

    int mask_grid_4x4[SIZE_BEGINNER][SIZE_BEGINNER]=
            {{'*', '*', '0', '*'},
             {'*', '0', '0', '*'},
             {'1', '*', '*', '*'},
             {'*', '*', '*', '*'}
            };

    for (int i=0; i<SIZE_BEGINNER; i++)
    {
        printf("\t");
        for (int j=0; j<SIZE_BEGINNER; j++)
        {
            printf("%c", mask_grid_4x4[i][j]);
            printf("\t");
        }
        printf("\n");
    }

    BOOL verification;
    verification = 0;

    while (verification != 1)
    {
        modification_grid(SIZE_BEGINNER);
        for (int i=0; i<SIZE_BEGINNER; i++)
        {
            printf("\t");
            for (int j=0; j<SIZE_BEGINNER; j++)
            {
                printf("%c", mask_grid_4x4[i][j]);
                printf("\t");
            }
            printf("\n");
        }

        verification=1;
        return 0;
    }
    return 0;
}

int intermediate_level()
{
    return 0;
}

int hard_level()
{
    return 0;
}