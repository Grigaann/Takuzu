#include "takuzu.h"


void rules(){
    printf("These are the rules of the Takuzu :\n");
    printf("- Each column and line have to contain the same number of 0 and 1\n"
           "- Columns or lines that are the same are forbidden\n"
           "- It can't have more than two of 1 or 0 nearby\n\n");
}

void goal_of_the_game(){
    printf("The goal of the game :\n");
    printf("- Fill the grid with the same amount of 0 and 1 on each column and line without any identical line or column and it can't have more than two 1 or 0 nearby.\n\n");
}


//======================================================================================================================
//-----------------------------------------------------PART 1-----------------------------------------------------------
//======================================================================================================================


int** apply_mask(int size, int** solution, int** mask){
    int line,col;
    int** grid_game = generate_null_array(size);
    for  (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++) {
            if (mask[line][col] == 1){
                grid_game[line][col] = solution[line][col];
            }
            else{
                grid_game[line][col] = -1;
            }
        }
    }
    return grid_game;
}


//----------------------------------------------------------------------------------------------------------------------

int** generate_mask(int size, char manner){
    int line,col;
    int** masked_grid = generate_null_array(size);
    for (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++){
            if (manner == 'a'){
                masked_grid[line][col] = rand()%2;
            } else if (manner == 'm'){
                do {
                    printf("Enter 0 or 1 to be the value in line %d and column %d :\n", line+1, col+1);
                    scanf("%d", &masked_grid[line][col]);
                } while (masked_grid[line][col] != 1 && masked_grid[line][col] != 0);
            }
        }
    }
    return masked_grid;
}


void is_playing(int size,int ** solution){
    int life_points = 3;
    int** mask = generate_mask(size, 'a');
    printf("Here is your Takuzu grid :\n");
    int** grid_game = apply_mask(size,solution,mask);
    display(size,grid_game);
    while(compare_arrays(size,grid_game,solution) == FALSE){
        modify_grid(size, grid_game, mask, solution,&life_points);
        display(size,grid_game);
    }
    printf("YOU DID IT !");
}

int** modify_grid(int size, int** grid_game,int** mask, int** solution,int* life_points){
    int line_modif, column_modif, number_modif;
    char heeeelp;
    BOOL need_help = FALSE;

    if (*life_points > 0){
        do{
            printf("Do you want to have a hint, y or n ? (%d/3 remaining)\n", *life_points);
            scanf("%s", &heeeelp);
        } while (heeeelp != 'y' && heeeelp != 'n');
        if (heeeelp == 'y'){
            need_help = 1;
        }
        else {
            need_help = 0;
        }
    }
    printf("Which one do you want to change ?\n");
    do {
        printf("Enter a line number (between 1 and %d) :", size);
        scanf("%d", &line_modif);
        line_modif--;
    } while (line_modif > size-1 || line_modif <0);

    do {
        printf("Enter a column number (between 1 and %d) :", size);
        scanf("%d", &column_modif);
        column_modif--;
    } while(column_modif>size-1 || column_modif<0);

    do{
        printf("With which number do you want to replace (1 or 0) ?\n");
        scanf("%d", &number_modif);
    } while (number_modif != 1 && number_modif != 0);

    if (mask[line_modif][column_modif] != 1){
        grid_game[line_modif][column_modif] = number_modif;

        if (verification(size,grid_game,need_help, *life_points)){
            if (grid_game[line_modif][column_modif] == solution[line_modif][column_modif]){
                if(need_help == TRUE){
                    printf("This move is correct !\n");
                }
            } else if(need_help == TRUE){
                printf("Valid move but incorrect !\n");
            }
        }
        else if(need_help == TRUE){
            printf("Your move is invalid.\n");
        }
        if(need_help == TRUE){
            (*life_points)--;
            if(*life_points<0)(*life_points)=0;
        }
    }else
        printf("You cannot change a value that was originally displayed !\n");
    return grid_game;
}

int verification(int size, int** grid, BOOL need_help, int life_points){
    BOOL verification = TRUE;
    int issue_row_count = verify_row_count(size, grid);
    int issue_row_originality = verify_row_originality(size,grid);
    int issue_row_coherence = verify_row_coherence(size,grid);
    int issue_col_count = verify_col_count(size,grid);
    int issue_col_originality = verify_col_originality(size,grid);
    int issue_col_coherence = verify_col_coherence(size,grid);


    if (issue_row_count != -1){
        if (life_points > 0 && need_help==TRUE){
            printf("At line %d : nb0 = %d & nb1 = %d\n",issue_row_count/100,(issue_row_count%100)/10,issue_row_count%10);
        }
        verification = FALSE;
    } else
    if (issue_col_count != -1){
        if (life_points > 0 && need_help==TRUE){
            printf("At col %d : nb0 = %d & nb1 = %d\n",issue_col_count/100,(issue_col_count%100)/10,issue_col_count%10);
        }
        verification = FALSE;
    } else
    if (issue_row_originality != -1){
        if (life_points > 0 && need_help==TRUE){
            printf("The line %d is identical to the line %d\n",issue_row_originality/10, issue_row_originality%10);
        }
        verification = FALSE;
    } else
    if (issue_col_originality != -1){
        if (life_points > 0 && need_help==TRUE){
            printf("The column %d is identical to the column %d\n", issue_col_originality/10, issue_col_originality%10);
        }
        verification = FALSE;
    } else
    if(issue_row_coherence != -1){
        if (life_points > 0 && need_help==TRUE){
            printf("The line %d contains a succession of too much 1s or 0s\n",issue_row_coherence);
        }
        verification = FALSE;
    } else
    if(issue_col_coherence != -1){
        if (life_points > 0 && need_help==TRUE){
            printf("The column %d contains a succession of too much 1s or 0s\n",issue_col_coherence);
        }
        verification = FALSE;
    }return verification;
}


int verify_row_count(int size, int** grid){
    int line,col;
    for  (line=0 ; line < size ; line++){
        int cpt_0 = 0,cpt_1 = 0;
        for (col=0 ; col < size ; col++) {
            if (grid[line][col] == 1)
                ++cpt_1;
            if (grid[line][col] == 0)
                ++cpt_0;
        }
        if(cpt_0 > size/2 || cpt_1> size/2){
            return (line+1)*100 + (cpt_0)*10 + cpt_1;
        }
    }
    return -1;
}

int verify_col_count(int size, int** grid){
    int line,col;
    for  (col = 0 ; col < size ; col++){
        int cpt_0 = 0,cpt_1 = 0;
        for (line = 0 ; line < size ; line++) {
            if (grid[line][col] == 1)
                ++cpt_1;
            if (grid[line][col] == 0)
                ++cpt_0;
        }
        if(cpt_0 > size/2 || cpt_1> size/2){
            return (col+1)*100 + (cpt_0)*10 + cpt_1;
        }
    }
    return -1;
}

int verify_row_originality(int size, int** grid){
    int line,other_line,col,identical;
    for (line = 0 ; line < size ; line++){
        for (other_line = line+1 ; other_line < size ; other_line++){
            identical = 0;
            for  (col = 0 ; col < size ; col++){
                if (grid[line][col] == -1){
                    col = size;
                } else if (grid[line][col] == grid[other_line][col]){
                    identical++;
                }
            }
            if (identical == size){
                return (line+1)*10 + (other_line+1);
            }
        }
    }
    return -1;
}

int verify_col_originality(int size, int** grid){
    int line,col,other_col,identical;
    for (col = 0 ; col < size ; col++){
        for (other_col = col+1 ; other_col < size ; other_col++){
            identical = 0;
            for  (line = 0 ; line < size ; line++){
                if (grid[line][col] == -1){
                    line = size;
                } else if (grid[line][col] == grid[line][other_col]){
                    identical++;
                }
            }
            if (identical == size) {
                return (col+1)*10 + (other_col+1);
            }
        }
    }
    return -1;
}

int verify_row_coherence(int size, int** grid) {
    int line, col;
    for (line = 0; line < size; line++) {
        int cpt_1 = 0, cpt_0 = 0;
        for (col = 0; col < size; col++) {
            if (grid[line][col] == 1) {
                cpt_1++;
                cpt_0 = 0;
            } else if (grid[line][col] == 0) {
                cpt_0++;
                cpt_1 = 0;
            } else {
                cpt_0 = 0;
                cpt_1 = 0;
            }
            if (cpt_0 == 3 || cpt_1 == 3){
                return line+1;
            }
        }
    }
    return -1;
}

int verify_col_coherence(int size, int** grid){
    int line,col;
    for  (col = 0 ; col < size ; col++){
        int cpt_1=0,cpt_0=0;
        for (line = 0 ; line < size ; line++) {
            if (grid[line][col] == 1){
                cpt_1++;
                cpt_0 = 0;
            } else if (grid[line][col] == 0) {
                cpt_0++;
                cpt_1 = 0;
            } else {
                cpt_0 = 0;
                cpt_1 = 0;
            }
            if (cpt_0 == 3 || cpt_1 == 3){
                return col+1;
            }
        }
    }
    return -1;
}


//======================================================================================================================
//-----------------------------------------------------PART 2-----------------------------------------------------------
//======================================================================================================================


int** solve(int size, int** grid){
    int line,col;
    BOOL done = FALSE;
    while (done == FALSE){
        sleep(size/2);

        if (auto_complete_row(size,grid) != 0){
            display(size, grid);
        }else if (auto_complete_col(size,grid) != 0){
            display(size, grid);
        }else if (auto_complete_col_double(size,grid) != 0){
            display(size, grid);
        }else if (auto_complete_row_double(size,grid) != 0){
            display(size, grid);
        }else if (auto_complete_row_sandwich(size,grid) != 0){
            display(size, grid);
        }else if (auto_complete_col_sandwich(size,grid) != 0){
            display(size, grid);
        }else if (auto_complete_row_originality(size,grid) != 0){
            display(size, grid);
        }else if (auto_complete_col_originality(size,grid) != 0){
            display(size, grid);
        }
        else{
            printf("Sorry, the grid cannot be solved from this point.\n");
            return 0;
        }
        done = TRUE;
        for (line=0;line<size;line++){
            for (col=0;col<size;col++){
                if (grid[line][col] == -1)
                    done = FALSE;
            }
        }
    }
    return grid;
}

int** auto_complete_row_double(int size, int** grid){
    int line,col;
    for (line=0;line<size;line++){
        for (col=0;col<size-1;col++){
            if (col<size-2 && (grid[line][col] != -1 && grid[line][col+1] == grid[line][col])){
                if (grid[line][col+2] == -1){
                    printf("We can place a %d (line : %d, col : %d) otherwise we would have more than two successive %ds on this line.\n", (grid[line][col]+1)%2, line+1, col+3, grid[line][col]);
                    grid[line][col+2] = (grid[line][col]+1)%2;
                    return grid;
                }
                if (col > 0 && grid[line][col-1] == -1){
                    printf("We can place a %d (line : %d, col : %d) otherwise we would have more than two successive %ds on this line.\n", (grid[line][col]+1)%2, line+1, col, grid[line][col]);
                    grid[line][col-1] = (grid[line][col]+1)%2;
                    return grid;
                }
            }

        }
    }
    return 0;
}

int** auto_complete_col_double(int size, int** grid){
    int line,col;
    for (col=0;col<size;col++){
        for (line=0;line<size-1;line++){
            if (line < size-2 && (grid[line][col] != -1 && grid[line+1][col] == grid[line][col])){
                if (grid[line+2][col] == -1){
                    printf("We can place a %d (line : %d, col : %d) otherwise we would have more than two successive %ds on this column.\n", (grid[line][col]+1)%2, line+3, col+1, grid[line][col]);
                    grid[line+2][col] = (grid[line][col]+1)%2;
                    return grid;
                }
                if (line > 0 && grid[line-1][col] == -1){
                    printf("We can place a %d (line : %d, col : %d) otherwise we would have more than two successive %ds on this column.\n", (grid[line][col]+1)%2, line, col+1, grid[line][col]);
                    grid[line-1][col] = (grid[line][col]+1)%2;
                    return grid;
                }
            }
        }
    }
    return 0;
}

int** auto_complete_row_sandwich(int size, int** grid){
    int line,col;
    for (line=0;line<size;line++){
        for (col=0;col<size-2;col++){
            if (grid[line][col] != -1 && grid[line][col+1] == -1 && grid[line][col+2] == grid[line][col]){
                printf("We can place a %d (line : %d, col : %d) otherwise we would have more than two successive %ds on this line.\n", (grid[line][col]+1)%2, line+1, col+2, grid[line][col]);
                grid[line][col+1] = (grid[line][col]+1)%2;
                return grid;
            }
        }
    }
    return 0;
}

int** auto_complete_col_sandwich(int size, int** grid){
    int line,col;
    for (col=0;col<size;col++){
        for (line=0;line<size-2;line++){
            if (grid[line][col] != -1 && grid[line+1][col] == -1 && grid[line+2][col] == grid[line][col]){
                printf("We can place a %d (line : %d, col : %d) otherwise we would have more than two successive %ds on this column.\n", (grid[line][col]+1)%2, line+2, col+1, grid[line][col]);
                grid[line+1][col] = (grid[line][col]+1)%2;
                return grid;
            }
        }
    }
    return 0;
}

int** auto_complete_row_originality(int size, int** grid){
    int line,other_line,col,place;
    BOOL okay = TRUE;
    for (line=0 ; line < size ; line++){
        if (count_occurrences(size,grid[line],-1) == 2){
            for (other_line=0 ; other_line<size ; other_line++){
                if (count_occurrences(size,grid[other_line],-1) == 0){
                    for (col=0 ; col<size ; col++){
                        if (grid[line][col] != -1 && grid[line][col] != grid [other_line][col]) {
                            okay=FALSE;
                        }
                    }
                    if (okay == TRUE){
                        for (place=0 ; place<size; place++){
                            if (grid[line][place] == -1){
                                printf("We can place a %d (line : %d, col : %d) for this line to be different from line %d.\n", (grid[other_line][place] + 1) %2, line+1, place+1, other_line+1);
                                grid[line][place] = (grid[other_line][place] + 1) %2;
                                return grid;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int** auto_complete_col_originality(int size, int** grid){
    int col,other_col,line,place;
    BOOL okay = TRUE;
    for (col=0 ; col < size ; col++){
        int* gather_col_val = (int*) malloc(size*sizeof(int));
        for (int temp = 0 ; temp<size; temp++){
            gather_col_val[temp] = grid[temp][col];
        }
        if (count_occurrences(size,gather_col_val,-1) == 2){
            for (other_col=0 ; other_col<size ; other_col++){
                int* gather_other_col_val = (int*) malloc(size*sizeof(int));
                for (int temp = 0 ; temp<size; temp++){
                    gather_other_col_val[temp] = grid[temp][other_col];
                }
                if (count_occurrences(size,gather_other_col_val,-1) == 0){
                    for (line=0 ; line<size ; line++){
                        if (grid[line][other_col] != -1 && grid[line][col] != grid [line][other_col]){
                                okay=FALSE;
                            }
                        if (okay == TRUE){
                            for (place=0 ; place<size; place++){
                                if (grid[place][col] == -1){
                                    printf("We can place a %d (line : %d, col : %d) for this column to be different from column %d.\n", (grid[place][other_col] + 1) %2, place+1, col+1, other_col+1);
                                    grid[place][col] = (grid[place][other_col] + 1) %2;
                                    free(gather_col_val);
                                    free(gather_other_col_val);
                                    return grid;
                                }
                            }
                        }
                    }
                }
                free(gather_other_col_val);
            }
            free(gather_col_val);
        }
    }
    return 0;
}

int** auto_complete_row(int size, int** grid){
    int line,col,nb_sought;
    for (line=0 ; line<size ; line++){
        for (nb_sought = 0 ; nb_sought < 2 ; nb_sought++){
            if (count_occurrences(size,grid[line],nb_sought) == size/2 && count_occurrences(size,grid[line],-1) > 0){
                for (col=0 ; col<size ; col++){
                    if (grid[line][col] == -1){
                        grid[line][col] = (nb_sought+1)%2;
                    }
                }
                printf("We can complete the line %d with %ds to respect the equality between 1s and 0s on this row.\n", line+1, (nb_sought+1)%2);
                return grid;
            }
        }
    }
    return 0;
}

int** auto_complete_col(int size, int** grid){
    int line,col,nb_sought;
    for (col=0 ; col<size ; col++){
        int* gather_col_val = (int*) malloc(size*sizeof(int));
        for (int temp = 0 ; temp<size; temp++){
            gather_col_val[temp] = grid[temp][col];
        }
        for (nb_sought = 1 ; nb_sought < 3 ; nb_sought++){
            if (count_occurrences(size,gather_col_val,nb_sought) == size/2 && count_occurrences(size,gather_col_val,-1) > 0){
                for (line=0 ; line<size ; line++){
                    if (grid[line][col] == -1){
                        grid[line][col] = (nb_sought+1)%2;
                    }
                }
                printf("We can complete the column %d with %ds to respect the equality between 1s and 0s on this column.\n", col+1, (nb_sought+1)%2);
                return grid;
            }
        }
        free(gather_col_val);
    }
    return 0;
}


//======================================================================================================================
//-----------------------------------------------------PART 3-----------------------------------------------------------
//======================================================================================================================

int** generate_grid(int size,char manner){
    int too_long, picked;
    BOOL explanations, valid = FALSE;
    int** grid = generate_null_array(size);

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

    for (int line = 0; line < size; line++){
        too_long = 0;
        valid = FALSE;

        while(!valid && too_long != 10){
            if (size==4) picked = rand()%6;
            else picked = rand()%29;
            for (int col = 0; col < size; col++) {
                if (size == 4){
                    grid[line][col] = valid_rows_4x4[picked][col];
                }else {
                    grid[line][col] = valid_rows_8x8[picked][col];
                }
            }

            if (manner == 'd'){
                display(size, grid);
                explanations = 1;
            }
            else explanations = 0;

            if (verification(size, grid, explanations, 1)){
                if (manner == 'd'){
                    printf("The row is valid.\n");}
                valid = TRUE;}

            if (manner == 'd') {
                sleep(size/2-1);
                printf("        ---------\n");
            }

            if (valid == FALSE) {
                for (int col = 0; col < size; col++)
                    grid[line][col] = -1;
                ++too_long;
            }
            if(too_long == 15){
                grid = generate_null_array(size);
                line = -1;
                if (manner == 'd')
                    printf("The grid seems hard, let's roll back a bit\n");
            }
        }
    }
    return grid;
}



//----------------------------------------------UNAVOIDABLE FUNCTIONS---------------------------------------------------


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

int** generate_null_array(int size){
    int line;
    int** grid = (int**) malloc(size*sizeof(int*));
    for (line=0 ; line < size ; line++){
        grid[line] = (int*) malloc(size*sizeof(int));
        for (int col = 0 ; col < size ; col++) {
            grid[line][col] = -1;
        }
    }
    return grid;
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

BOOL compare_arrays(int size, int** array1, int** array2){
    int line,col;
    for (line=0 ; line < size ; line++){
        for (col=0 ; col<size ; col++){
            if (array1[line][col] != array2[line][col] || array1[line][col]==-1 || array2[line][col] == -1)
                return FALSE;
        }
    }
    return TRUE;
}

int count_occurrences(int size, int const* array, int nb_sought){
    int count=0;
    for (int index=0 ; index<size ; index++){
        if (array[index] == nb_sought){
            count++;
        }
    }
    return count;
}