#include "takuzu.h"
#include "stdio.h"

int main() {
    //srand(time(NULL));
    int choice_menu;
    int grid[size][size] = {0,0,1,1,
                      1,0,0,1,
                      1,1,0,0,
                      0,1,1,0};

    int GRID[SIZE][SIZE] = {0,0,1,0,1,0,1,1,
                      0,1,0,1,0,1,0,1,
                      1,0,1,0,0,1,1,0,
                      0,1,1,0,1,0,1,0,
                      1,0,0,1,1,0,0,1,
                      1,0,1,1,0,1,0,0,
                      0,1,0,0,1,0,1,1,
                      1,1,0,1,0,1,0,0};
    printf("Menu :\n"
           "1) I want to complete the grid myself\n"
           "2) Let the computer help me\n"
           "3) Generate a solved Takuzu grid\n");
    scanf("%d", &choice_menu);
    if (choice_menu == 1){
        display(grid);
    }

    return 0;
}
