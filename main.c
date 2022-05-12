#include "takuzu.h"

int main() {
    int choice, subchoice, difficulty;
    int grid_size;
    int** mask_matrix;
    int ** grid_used;
    BOOL separation_displayed = FALSE, running = TRUE;

    int solution_4x4_spawn[SIZE_BEGINNER][SIZE_BEGINNER] = {0, 1, 0, 1,
                                                            1, 0, 0, 1,
                                                            1, 0, 1, 0,
                                                            0, 1, 1, 0};
    int ** solution_4x4 = from_static_to_dynamic(SIZE_BEGINNER,solution_4x4_spawn);

    int mask_grid_4x4_spawn[SIZE_BEGINNER][SIZE_BEGINNER] = {0, 0, 0, 0,
                                                             0, 1, 1, 0,
                                                             1, 0, 0, 0,
                                                             0, 0, 0, 0};
    int** mask_grid_4x4 = from_static_to_dynamic(SIZE_BEGINNER,mask_grid_4x4_spawn);

    int solution_8x8_spawn[SIZE_ADVANCED][SIZE_ADVANCED] = {0, 0, 1, 0, 1, 0, 1, 1,
                                                            0, 1, 0, 1, 0, 1, 0, 1,
                                                            1, 0, 1, 0, 0, 1, 1, 0,
                                                            0, 1, 1, 0, 1, 0, 1, 0,
                                                            1, 0, 0, 1, 1, 0, 0, 1,
                                                            1, 0, 1, 1, 1, 1, 0, 0,
                                                            0, 1, 0, 0, 1, 0, 1, 1,
                                                            1, 1, 0, 1, 0, 1, 0, 0};
    int** solution_8x8 = from_static_to_dynamic(SIZE_ADVANCED,solution_8x8_spawn);



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
                if (difficulty == 1){
                    grid_size = SIZE_BEGINNER;
                    grid_used = solution_4x4;
                }
                else {
                    grid_size = SIZE_ADVANCED;
                    copy_array(grid_size,solution_8x8,grid_used);
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
                        mask_matrix = generate_mask(grid_size, 'm');
                        display(grid_size, mask_matrix);
                        printf("Following the associated displayed matrix :\n");
                        break;
                    }
                    case 2: {
                        printf("Using the following grid :\n");
                        display(grid_size,grid_used);
                        printf("Has been applied the following mask :\n");
                        mask_matrix = generate_mask(grid_size, 'a');
                        display(grid_size, mask_matrix);
                        printf("To give the following resulting matrix :\n");
                        break;
                    }
                    case 3: {
                        mask_matrix = generate_mask(grid_size, 'a');
                        modify_grid(grid_size, solution_4x4);
                        break;
                    }
                }
            }
            case 4 : {
                //solve_grid();
                break;
            }
            case 5 : {
                do {
                    printf("Choose a difficulty (between 1 and 3)\n");
                    scanf("%d", &difficulty);
                } while (difficulty < 1 || difficulty > 2);
                if (difficulty == 1){
                    grid_size = SIZE_BEGINNER;
                    grid_used = solution_4x4;
                }
                else {
                    grid_size = SIZE_ADVANCED;
                    grid_used = solution_8x8;
                }
                //generate_grid(difficulty);
                break;
            }
            default :
                printf("Your choice isn't valid.");
        }
        separation_displayed = TRUE;
    }
    return 0;
}
