#include "takuzu.h"


void rules(){
    printf("These are the rules of the Takuzu :\n");
    printf("- Each column and line have to contain the same number of 0 and 1\n"
           "- Columns or lines that are the same are forbidden\n"
           "- It can't have more than two of 1 or 0 nearby");
}

void goal_of_the_game(){
    printf("The goal of the game :\n");
    printf("- Fill the grid with the same amount of 0 and 1 on each column and line without any identical line or column and it can't have more than two 1 or 0 nearby.\n");
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

int** generate_mask(int size, char manner){
    int line,col;
    int** masked_grid = generate_null_array(size);
    for (line=0 ; line < size ; line++){
        for (col=0 ; col < size ; col++){
            if (manner == 'a'){
                masked_grid[line][col] = rand()%2;
            } else if (manner == 'm'){
                do {
                    printf("Enter 0 or 1 to be the value in line %d and column %d :\n", line, col);
                    scanf("%d", masked_grid[line][col]);
                } while (masked_grid[line][col] != 1 && masked_grid[line][col] != 0);
            }
        }
    }
    return masked_grid;
}

//----------------------------------------------------------------------------------------------------------------------


void is_playing(int size,int ** solution){
    int life_points = 3;
    int** mask = generate_mask(size, 'a');
    display(size,mask);
    printf("The above mask is applied to give the following playable matrix\n");
    int** grid_game = apply_mask(size,solution,mask);
    display(size,grid_game);
    while(compare_arrays(size,grid_game,solution) == FALSE){
        modify_grid(size,grid_game,mask,solution,&life_points);
        display(size,grid_game);
    }
    printf("YOU DID IT !");
}


int** modify_grid(int size, int** grid_game,int** mask,int** solution,int* life_points){
    int line_modif, column_modif, number_modif;
    BOOL need_help = FALSE;

    if(life_points<0)life_points=0;

    printf("Which one do you want to change ?\n");
    do {
        printf("Enter a line number (between 1 and %d) :", size);
        scanf("%d", &line_modif);
        line_modif--;
    } while (line_modif > size-1 || line_modif <0);

    do {
        printf("Enter a column number between 1 and %d :", size);
        scanf("%d", &column_modif);
        column_modif--;
    } while(column_modif>size-1 || column_modif<0);

    do{
        printf("With which number do you want to replace (1 or 0) ?\n");
        scanf("%d", &number_modif);
    } while (number_modif != 1 && number_modif != 0);
    int** test_modif = generate_null_array(size);
    copy_array(size,grid_game,test_modif);
    test_modif[line_modif][column_modif] = number_modif;

    do{
        printf("Do you want to have a hint ? (%d/3 remaining)\n", *life_points);
        scanf("%s", &need_help);
    } while (number_modif != 1 && number_modif != 0);

    if (verification(size,test_modif,need_help,*life_points)){
        if (test_modif[line_modif][column_modif] == solution[line_modif][column_modif]){
            grid_game[line_modif][column_modif] = number_modif;
            printf("This move is correct !\n");
        } else {
            printf("Valid move but incorrect !\n");
        }
    } else{
        printf("Your move is invalid.\n");
        life_points--;
    }
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

    //printf("%d %d %d %d %d %d",issue_row_count,issue_col_count,issue_col_originality,issue_row_originality,issue_col_coherence,issue_row_coherence);
    if (issue_row_count != -1){
        if (life_points > 0 && need_help){
            printf("At line %d : nb0 = %d & nb1 = %d\n",issue_row_count/100,(issue_row_count%100)/10,issue_row_count%10);
        }
        verification = FALSE;
    } else
    if (issue_col_count != -1){
        if (life_points > 0 && need_help){
            printf("At col %d : nb0 = %d & nb1 = %d\n",issue_col_count/100,(issue_col_count%100)/10,issue_col_count%10);
        }
        verification = FALSE;
    } else
    if (issue_row_originality != -1){
        if (life_points > 0 && need_help){
            printf("The line %d is identical to the line %d\n",issue_row_originality/10, issue_row_originality%10);
        }
        verification = FALSE;
    } else
    if (issue_col_originality != -1){
        if (life_points > 0 && need_help){
            printf("The column %d is identical to the column %d\n", issue_col_originality/10, issue_col_originality%10);
        }
        verification = FALSE;
    } else
    if(issue_row_coherence != -1){
        if (life_points > 0 && need_help){
            printf("The line %d contains a succession of too much 1s or 0s\n",issue_row_coherence);
        }
        verification = FALSE;
    } else
    if(issue_col_coherence != -1){
        if (life_points > 0 && need_help){
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
                printf("%d | %d",cpt_1,cpt_0);
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


int** solve(int** grid){
    //apply things
    return grid;
}



//======================================================================================================================
//-----------------------------------------------------PART 3-----------------------------------------------------------
//======================================================================================================================


//



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
    }
    return grid;
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
