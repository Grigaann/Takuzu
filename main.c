#include "takuzu.h"

int main() {
    int choice;

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

    printf("====================== \n"
           "        TAKUZU \n"
           "====================== \n");

    printf("What do you want to do ? (type the number) \n"
           "1 - rules of the game \n"
           "2 - goal of the game \n"
           "3 - beginner level \n"
           "4 - intermediate level \n"
           "5 - hard level \n");

    scanf("%d", &choice);

    switch(choice)
    {
        case 1 : rules();
            break;
        case 2 : goal_of_the_game();
            break;
        case 3 : beginner_level();
            break;
        case 4 : intermediate_level();
            break;
        case 5 : hard_level();
            break;
        default : printf("Your choice doesn't exist.");
    }

    do {
        printf("\n ===================================================== \n");
        printf("What do you want to do ? (type the number) \n"
               "1 - rules of the game \n"
               "2 - goal of the game \n"
               "3 - beginner level \n"
               "4 - intermediate level \n"
               "5 - hard level \n");

        scanf("%d", &choice);

        switch (choice) {
            case 1 :
                rules();
                break;
            case 2 :
                goal_of_the_game();
                break;
            case 3 :
                beginner_level();
                break;
            case 4 :
                intermediate_level();
                break;
            case 5 :
                hard_level();
                break;
            default :
                printf("Your choice doesn't exist.");
        }
    } while(choice == 1 || choice == 2);
    return 0;
}