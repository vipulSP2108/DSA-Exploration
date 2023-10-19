#include <stdio.h>
#include <assert.h>

#include "test.h"

// enum {
//     NO = 0, /* No line */
//     RED = 1,
//     BLUE = 2
// };

int triangle[15][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,6},{1,3,10},{8,6,13},{1,10,3},{10,3,1},{8,13,6},{4,1,11},{5,8,11},{9,13,11},{14,10,11}};
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

void inisilize_board(board_t board){
    for(int i =0; i<15; i++){
        board[i] = '.';
    }
}

void print_board(board_t board){
    for (int i = 0; i < 15; ++i) {
        printf("board[%d] --> %c\n",i,board[i]); // wrong hua to cheak
    }
}

int has_lose(board_t board, player_t player)
{
    int count = 0;
    for (int i = 0; i<15; i++){
        if(board[triangle[i][0]] == player && board[triangle[i][1]] == player  && board[triangle[i][2]] == player){
            printf("%c loss\n", player);
            count = 1;
        }
    }
    return count;
}

int is_full(board_t board){
    int count = 0;
    for (int j = 0; j < 15; j++) {
        if (board[j] == '.'){
            return 0;
        }
    }
    return 1;
}

// typedef struct {
//     int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
//     int scoreß; /* -1 for loss, 0 for draw, 1 for win. */
// } move_t;

int best_move(int play, board_t board, player_t player){
    char priv_play = board[play];
    board[play] = player;
    for(int j = 0; j<3; j++){
        for(int i = 0; i<15; i++){
            if(triangle[i][j]==play){
                if((board[triangle[i][0]] != player && board[triangle[i][1]] != player) || (board[triangle[i][1]] != player && board[triangle[i][2]] != player) || (board[triangle[i][2]]!= player && board[triangle[i][0]] != player)){
                    board[play] = priv_play;
                    return 0;
                }
                if((board[triangle[i][0]] != player) || (board[triangle[i][1]] != player) || (board[triangle[i][2]] != player)){
                    board[play] = priv_play;
                    return -1;
                }
                else{
                    board[play] = priv_play;
                    return 1;
                }
            }
        }
    }
    board[play] = priv_play;
    return 21;
}

void computer_play(board_t board, player_t player){
    int complite_play = 0;
    int can_play = 200;
    int not_play = 200;
    for(int play = 0; play<15; play++){
        if(board[play] == '.'){
            if(best_move(play, board, player) == 0){
                board[play] = player;
                complite_play = 1;
                break;
            }
            else if (best_move(play, board, player) == -1){
                can_play = play;
            }
            else if (best_move(play, board, player) == 21){
                continue;
            }
            else{
                not_play = play;
            }
        }
    }
    if(complite_play== 0 && can_play != 200){
        board[can_play] = player;
    }
    else if(complite_play== 0 && can_play == 200){
        board[not_play] = player;
    }
}

int main()
{
    board_t board;
    player_t player;
    player_t computer;
    int triangle[15][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,6},{1,3,10},{8,6,13},{1,10,3},{10,3,1},{8,13,6},{4,1,11},{5,8,11},{9,13,11},{14,10,11}};
    char choose;
    int input;
    int user1_tens;
    int user1_ones;
    int count = 1;
    int temp;

    printf("Your choose between x and o : ");
    scanf("%c", &choose);
    player = choose;
    computer = 'x';
    if(choose == 'x'){
        computer = 'o';
    }
    inisilize_board(board);
    print_board(board);

    while (count == 1){
        // if ((has_lose(board, player) == 1) || (has_lose(board, computer) == 1)){ 
        //     break;
        // }
        // if (has_lose(board, player) == 1){     // problem aaye to comment out and above comment
        //     break;
        // }
        // if (has_lose(board, computer) == 1){
        //     break;
        // }
        printf("Your choice (format :X --> bet[0 to 14]) : ");
        scanf("%d", &input);
        if(board[input] == '.'){
            board[input] = player;

            if(is_full(board) == 1){
                printf("draw");
                break;
            }

            if ((has_lose(board, player) == 1)){ 
                printf("meeee");
                break;
            }
            computer_play(board, computer);
            if ((has_lose(board, computer) == 1)){ 
                break;
            }

            if(is_full(board) == 1){
                printf("draw");
                break;
            }
            print_board(board);
            printf("%c --> you\n",player);
            printf("%c --> computer\n",computer);
        }
        else{
            printf("already in use; no over write\n");
        }
    }
    return 0;
}
