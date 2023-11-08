#include <stdio.h>

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

void avi_space(board_t board){
    for (int cola = 0; cola<5; cola++){
        for (int rowa = 3; rowa>=0; rowa--){
            if (board[rowa][cola] == '.'){
                printf("%d%d " , rowa, cola);
                // printf("%d", rowa);
                break;
            }
        }
    } 
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

    int user1_row;
    int user1_col;
    char input[3];
    while (0 == 0){


        print_board(board);

        if (is_full(board) == 1){
            printf("Full");
            break;
        }
        
        printf("\navalable spaces ");
        avi_space(board);
        printf("and Your choice (format :XX) is ");
        scanf("%2s", input);
        user1_row = input[0] - '0';
        user1_col = input[1] - '0';
        // scanf("%d %d",&user1_row, &user1_col);
        // printf("%d", user1_row);
        // printf("%d", user1_col);
        board[user1_row][user1_col] = 'X';

        if (won(board, player) == 1){
            print_board(board);
            printf("%c won",player);
            break;
        }
    }
    return 0;
}
