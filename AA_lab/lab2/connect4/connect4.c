#include <stdio.h>
#include <stdlib.h>

typedef char board_t[4][5];
typedef char player_t;

// enum {
//     EMPTY = 0,
//     RED,
//     BLUE,
// };

int won(board_t board, player_t player){
    // row
    for(int row = 0; row<4; row++){
        int count = 0;
        // char comp;
        char comp = player;
        for(int col = 0; col<5; col++){
            // if (col == 0){
            //     comp = board[row][col];
            // }
            if (board[row][col] == comp){
                count++;
                if (count == 5){
                    return 1;
                }
            }
        }
    }

    // col
    for(int col = 0; col<5; col++){
        int count = 0;
        // char comp;
        char comp = player;
        for(int row = 0; row<4; row++){
            // if (row == 0){
            //     comp = board[row][col];
            // }
            if (board[row][col] == comp){
                 count++;
                if (count == 4){
                    return 1;
                }
            }
        }
    }

    //digonal
    int row  = 0;
    for(int col = 0; col<5; col++){
        // char comp = board[row][col];
        char comp = player;
        int count = 0;
        int cold = col;
        int rowd = row;
        if (col <= 5/2){                     //top-down digonal
            while(rowd<4 && cold<5){
                if (comp != board[rowd][cold]){
                    break;
                }
                rowd++;
                cold++;
                count++;
            }
            if(count == 4){
                return 1;
            }
        }
        else{                                //down-top digonal
            while(rowd<4 && cold>=0){
                if (comp != board[rowd][cold]){
                    break;
                }
                rowd++;
                cold--;
                count++;
            }
            if(count == 4){
                return 1;
            }
        }
    }
    return 0;
}

int is_full(board_t board)
{
    for(int row = 0; row<4; row++){
        for(int col = 0; col<5; col++){
            if(board[row][col] != 'X' && board[row][col] != 'O'){
                return 0;  // --> not full
                break;
            }
        }
    }
    return 1;
}

// typedef struct {
//     int col;
//     int score;
// } move_t;

// move_t best_move(board_t board, player_t player)
// {}

void print_board(board_t board)
{
    for(int row = 0; row<4; row++){
        for(int col = 0; col<5; col++){
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }

    for(int row = 0; row<4; row++){
        for(int col = 0; col<5; col++){
            printf("%d", row);
            printf("%d ", col);
        }
        printf("\n");
    }
}

void avi_space(board_t board, int stored_avi_space[2][5]){
    for (int cola = 0; cola<5; cola++){
        for (int rowa = 3; rowa>=0; rowa--){
            if (board[rowa][cola] == '.'){
                stored_avi_space[0][cola] = rowa;
                stored_avi_space[1][cola] = cola;
                
                break;
            }
            else{
                if(rowa == 3){
                    stored_avi_space[0][cola] = 21;
                    stored_avi_space[1][cola] = 21;
                }
            }
        }
    } 
}

void computer(board_t board,int stored_avi_space[2][5], player_t player){
    char comp_player = 'X';
    if (player == 'X'){
        comp_player = 'O';
    }
    int play = 0;
    int row = 0;
    if (play == 0){       // vertical check
        for (int i = 0; i<4; i++){
            int countj = 0;
            for (int j = 0; j<5; j++){
                if (board[i][j] == player){
                    countj++;
                }
                if (countj == 4){
                    for (j = 0; j<4; j++){
                        if (board[i][j] == '.'){
                            play++;
                            board[i][j] = comp_player;
                        }
                    }
                }
            }
        }
    }

    if (play == 0){
        //digonal
        row  = 0;
        for(int col = 0; col<5; col++){
            if (play != 0){
                break;
            }
            int count = 0;
            int cold = col;
            int rowd = row;
            if (col <= 5/2){                     //top-down digonal
            if (play != 0){
                break;
            }
            count = 0;
                while(rowd<4 && cold<5){
                    if (board[rowd][cold] == player){
                        count++;
                    }
                    rowd++;
                    cold++;
                }
                if(count == 3){
                    rowd = row;
                    cold = col;
                    while(rowd <4 && cold<5){
                        if (board[rowd][cold] == '.'){
                            board[rowd][cold] = comp_player;
                            play++;
                        }
                        rowd++;
                        cold++;
                    }
                }
            }
            else{                                //down-top digonal
                if (play != 0){
                    break;
                }
                count = 0;
                while(rowd<4 && cold>=0){
                    if (board[rowd][cold] == player){
                        count++;
                    }
                    rowd++;
                    cold--;
                }
                if(count == 3){
                    rowd = row;
                    cold = col;
                    while(rowd<4 && cold>=0){
                        if (board[rowd][cold] == '.'){
                            board[rowd][cold] = comp_player;
                            play++;
                        }
                        rowd++;
                        cold--;
                    }
                }
            }
        }
    }

    if (play == 0){     //easy cheak
        for (int col = 0; col<5; col++){
            row = stored_avi_space[0][col];
            if (row < 3 && board[row + 1][col] == player && row != 21){
                board[row][col] = comp_player;
                play++;
                break;
            }
        }
    }
}

// from my side
int correct_input(board_t board, player_t player, int stored_avi_space[2][5], int user1_row, int user1_col){

    // board[user1_row][user1_col] == '.' ? board[user1_row][user1_col] == player : printf("invalid input");
    
    for(int col = 0; col<5; col++){
        if(stored_avi_space[1][col] == user1_col && stored_avi_space[0][col] == user1_row){
            return 1;
        }
    }
    return 0;
}


int main()
{
    board_t board;
    player_t player;
    
    player = 'X';
    for(int row = 0; row<4; row++){
        for(int col = 0; col<5; col++){
            board[row][col] = '.';
        }
    }

    char input[3];
    int stored_avi_space[2][5];
    int user1_row;
    int user1_col;
    int count = 0;
    while (0 == 0){
        if (is_full(board) == 1){
            printf("      GAME OVER board Full");
            break;
        }

        // for first input only
        if (count == 0){
            printf("\n\nWELCOME to CONNECT 4\nRule:- \n always input from avalable spaces which are basicly base cases\n to win make 4 same X or O in vertical or digonal\n or make 5 same X or O in horizontal\n");
            printf("EXAMPLE :- \n avalable spaces 30 31 32 33 34\n");
        }
        else{
            print_board(board);
            printf("avalable spaces ");
            for (int cola = 0; cola<5; cola++){
                printf("%d%d ", stored_avi_space[0][cola], stored_avi_space[1][cola]);
            }
        }

        printf("Your choice (format :XX) is ");
        scanf("%2s", input);
        user1_row = input[0] - '0';
        user1_col = input[1] - '0';

        
        if(correct_input(board,player, stored_avi_space, user1_row, user1_col) == 1){
            board[user1_row][user1_col] = player;
        }
        else{
            printf("INVALID INPUT\n");
        }

        // for first input only
        if (count == 0){
            printf("GOOD \n          GAME START\n");
            count++;
        }

        avi_space(board, stored_avi_space);
        computer(board, stored_avi_space, player);
        avi_space(board, stored_avi_space);

        if (won(board, player) == 1){
            print_board(board);
            printf("       GAME OVER %c won",player);
            break;
        }
    }
    return 0;
}
