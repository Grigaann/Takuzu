#include "takuzu.h"

int valid_rows_4x4[6][4] = {0, 0, 1, 1,
                            0, 1, 0, 1,
                            1, 0, 1, 0,
                            1, 1, 0, 0,
                            1, 0, 0, 1,
                            0, 1, 1, 0};


int valid_rows_8x8[30][8] = {0, 0, 1, 0, 1, 0, 1, 1,
                             0, 0, 1, 0, 1, 1, 0, 1,
                             0, 0, 1, 1, 0, 0, 1, 1,
                             0, 0, 1, 1, 0, 1, 0, 1,
                             0, 0, 1, 1, 0, 1, 1, 0,
                             0, 1, 0, 0, 1, 1, 0, 1,
                             0, 1, 0, 0, 1, 0, 1, 1,
                             0, 1, 0, 1, 0, 1, 0, 1,
                             0, 1, 0, 1, 1, 0, 0, 1,
                             0, 1, 0, 1, 1, 0, 1, 0,
                             0, 1, 1, 0, 0, 1, 0, 1,
                             0, 1, 1, 0, 0, 1, 1, 0,
                             0, 1, 1, 0, 1, 0, 0, 1,
                             0, 1, 1, 0, 1, 0, 1, 0,
                             0, 1, 1, 0, 1, 1, 0, 0,
                             1, 0, 0, 1, 0, 0, 1, 1,
                             1, 0, 0, 1, 0, 1, 0, 1,
                             1, 0, 0, 1, 0, 1, 1, 0,
                             1, 0, 0, 1, 1, 0, 0, 1,
                             1, 0, 0, 1, 1, 0, 1, 0,
                             1, 0, 1, 0, 0, 1, 0, 1,
                             1, 0, 1, 0, 0, 1, 1, 0,
                             1, 0, 1, 0, 1, 0, 1, 0,
                             1, 0, 1, 1, 0, 0, 1, 0,
                             1, 0, 1, 1, 0, 1, 0, 0,
                             1, 1, 0, 0, 1, 0, 0, 1,
                             1, 1, 0, 0, 1, 0, 1, 0,
                             1, 1, 0, 0, 1, 1, 0, 0,
                             1, 1, 0, 1, 0, 0, 1, 0,
                             1, 1, 0, 1, 0, 1, 0, 0};

int main() {
    int choice, subchoice, difficulty;
    int grid_size, limit;
    int** mask_matrix;
    int** solution;
    int** grid_game;
    char explained;
    BOOL separation_displayed = FALSE, running = TRUE;
    srand(time(NULL));



    printf("\n              ========================\n"
           "                       TAKUZU\n"
           "              ========================\n\n");
    while (running) {
        if (separation_displayed)
            printf("\n===========================================\n");

        printf("What do you want to do ? (type the number)\n"
               "1 - Rules of the game\n"
               "2 - Goal of the game\n"
               "3 - Solve a grid\n"
               "4 - Let a grid be solved automatically\n"
               "5 - Generate a new Takuzu grid\n"
               "0 - Exit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 0:
                running = FALSE;
                printf("\nSee you soon\n");
                break;
            case 1 :
                rules();
                break;
            case 2 :
                goal_of_the_game();
                break;
            case 3 : {
                do {
                    printf("Choose a difficulty (between 1 and 2)\n");
                    scanf("%d", &difficulty);
                } while (difficulty < 1 || difficulty > 2);
                if (difficulty == 1) {
                    grid_size = SIZE_BEGINNER;
                } else {
                    grid_size = SIZE_ADVANCED;
                }
                do {
                    printf("Now what do you want to do ?\n"
                           "1 - Enter a mask manually\n"
                           "2 - Automatically generate a mask\n"
                           "3 - Play\n");
                    scanf("%d", &subchoice);
                } while (subchoice < 1 || subchoice > 3);
                switch (subchoice) {
                    case 1: {
                        solution = generate_grid(grid_size,'h');
                        mask_matrix = generate_mask(grid_size, 'm');
                        printf("Here is what you've entered :\n");
                        display(grid_size, mask_matrix);
                        printf("And below is a random associated matrix :\n");
                        grid_game = apply_mask(grid_size,solution,mask_matrix);
                        //copy_array(grid_size, apply_mask(grid_size, solution, mask_matrix), grid_game);
                        display(grid_size, grid_game);
                        break;
                    }
                    case 2: {
                        printf("Using the following random grid :\n");
                        solution = generate_grid(grid_size,'h');
                        display(grid_size, solution);
                        printf("Has been applied the following mask :\n");
                        mask_matrix = generate_mask(grid_size, 'a');
                        display(grid_size, mask_matrix);
                        printf("To give the following resulting matrix :\n");
                        display(grid_size, apply_mask(grid_size, solution, mask_matrix));
                        break;
                    }
                    case 3: {
                        is_playing(grid_size, generate_grid(grid_size, 'h'));
                        break;
                    }
                    default:
                        printf("");
                }
                break;
            }
            case 4 : {
                do {
                    printf("Choose a difficulty (between 1 and 2)\n");
                    scanf("%d", &difficulty);
                } while (difficulty < 1 || difficulty > 2);
                if (difficulty == 1) {
                    grid_size = SIZE_BEGINNER;
                } else {
                    grid_size = SIZE_ADVANCED;
                }
                printf("There will be a %d seconds cooldown between each step\n", grid_size/2);
                sleep(1);
                solution = generate_grid(grid_size,'h');
                mask_matrix = generate_mask(grid_size, 'a');
                grid_game = generate_null_array(grid_size);
                printf("Here is the initial grid :\n");
                copy_array(grid_size, apply_mask(grid_size, solution, mask_matrix), grid_game);
                display(grid_size, grid_game);
                if (solve(grid_size, grid_game))
                    printf("\nWork done.\n");
                break;
            }
            case 5 : {
                do {
                    printf("Now what do you want to do ?\n"
                           "1 - Generate a random grid\n"
                           "2 - Display all valid rows\n");
                    scanf("%d", &subchoice);
                } while (subchoice < 1 || subchoice > 2);
                do {
                    printf("Choose a difficulty (between 1 and 2)\n");
                    scanf("%d", &difficulty);
                } while (difficulty < 1 || difficulty > 2);
                if (difficulty == 1) {
                    grid_size = SIZE_BEGINNER;
                    limit = 6;
                } else {
                    grid_size = SIZE_ADVANCED;
                    limit = 29;
                }
                switch (subchoice) {
                    case 1: {
                        do {
                            printf("Choose a whether you want the details or not ('d' for display or 'h' for hidden)\n");
                            scanf("%s", &explained);
                        } while (explained != 'd' && explained != 'h');
                        grid_game = generate_grid(grid_size, explained);
                        if (explained=='h')
                            display(grid_size,grid_game);
                        printf("\nThe above grid is a good one.\n");
                        break;
                    }
                    case 2: {
                        printf("Here is the list of all the valid combinations for a %dx%d grid :\n",grid_size,grid_size);
                        for (int broutille = 0; broutille < limit; broutille++) {
                            for (int broutillebis = 0; broutillebis < grid_size; broutillebis++) {
                                if (difficulty == 1)
                                    printf("\t%d", valid_rows_4x4[broutille][broutillebis]);
                                else
                                    printf("\t%d", valid_rows_8x8[broutille][broutillebis]);
                            }
                            printf("\n");
                        }
                        break;
                    }
                    default:
                        printf("You're not supposed to see that...\n");
                }
                break;
            }
            default :
                printf("See you soon\n");
        }
        separation_displayed = TRUE;
        sleep(2);
    }
    return 0;
}