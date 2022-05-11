#include "takuzu.h"

int main() {
    int choice;
    int** maske;
    BOOL cpt = FALSE, running = TRUE;

    int grid[SIZE_BEGINNER][SIZE_BEGINNER] = {0,0,1,1,
                                              1,0,0,1,
                                              1,1,0,0,
                                              0,1,1,0};

    int GRID[SIZE_HARD][SIZE_HARD] = {0,0,1,0,1,0,1,1,
                                      0,1,0,1,0,1,0,1,
                                      1,0,1,0,0,1,1,0,
                                      0,1,1,0,1,0,1,0,
                                      1,0,0,1,1,0,0,1,
                                      1,0,1,1,0,1,0,0,
                                      0,1,0,0,1,0,1,1,
                                      1,1,0,1,0,1,0,0};
    printf( "\n              ========================\n"
                  "                       TAKUZU\n"
                  "              ========================\n\n");
    while (running){
        if (cpt)
            printf("\n===========================================\n");

        printf("What do you want to do ? (type the number)\n"
               "1 - Rules of the game\n"
               "2 - Goal of the game\n"
               "3 - Beginner level\n"
               "4 - Intermediate level\n"
               "5 - Hard level\n"
               "0 - Exit");

        scanf("%d", &choice);

        switch (choice) {
            case 0:
                running = FALSE;
                break;
            case 1 :
                rules();
                break;
            case 2 :
                goal_of_the_game();
                break;
            case 3 :
                maske = masked_matrix(SIZE_BEGINNER);
                display(SIZE_BEGINNER,maske);
                printf("\nHere is the playable matrix:\n\n");
                display_masked(SIZE_BEGINNER,grid,maske);
                //beginner_level();
                break;
            case 4 :
                intermediate_level();
                break;
            case 5 :
                hard_level();
                break;
            default :
                printf("Your choice isn't valid.");
        }
        cpt = TRUE;
    }
    return 0;
}