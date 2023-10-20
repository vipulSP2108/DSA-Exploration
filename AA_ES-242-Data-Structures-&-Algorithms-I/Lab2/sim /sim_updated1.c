#include <stdio.h>
#include <assert.h>

#include "test.h"
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */
int triangle[20][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,6},{1,3,10},{8,6,13},{4,1,11},{5,8,11},{9,13,11},{14,10,11},{0,7,3},{3,2,12},{4,2,13},{8,14,7},{0,6,2},{12,6,7},{5,10,7},{1,2,9}};

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

int has_lose(board_t board, player_t player){
    int count = 0;
    for (int i = 0; i<20; i++){   //trangle ke anda to 20
        if(board[triangle[i][0]] == player && board[triangle[i][1]] == player  && board[triangle[i][2]] == player){
            printf("%c loss\n", player);
            count = 1;
        }
    }
    return count;
}

void print_won(int won[15]){
    for(int i = 0; i<15; i++){
        printf("%d",won[i]);
    }
    printf("\n");
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

void best_move(board_t board, player_t player,int won[15]){
    int can_play_best = 200;
    int not_play_best = 200;
    for(int play = 0; play<15; play++){
        int count = 0;
        char priv_play = board[play];
        board[play] = player;
        for(int i = 0; i<20; i++){ //trangle ke anda to 20
            if((board[triangle[i][0]] == player && board[triangle[i][1]] == player && board[triangle[i][2]] == player)){
                count = 2;
                won[play] = 1;
                break;
            }
            else if((board[triangle[i][0]] == player && board[triangle[i][1]] == player) || (board[triangle[i][1]] == player && board[triangle[i][2]] == player) || (board[triangle[i][2]] == player && board[triangle[i][0]] == player)){
                count = 1;
                won[play] = -1;
            }
            else if((board[triangle[i][0]] != player) || (board[triangle[i][1]] != player) || (board[triangle[i][2]] != player)){
                won[play] = 0;
            }
        }
        if(count == 1){
            won[play] = -1;
        }
        board[play] = priv_play;
            
        if(board[play] != '.'){
            won[play] = 2;
        }
    }
}

// void computer_play(board_t board, player_t player, int won[15]){
int computer_play(board_t board, player_t player, int won[15]){
    int complite_play = 0;
    int can_play = 200;
    int not_play = 200;
    for (int i = 0; i<15; i++){
        // if(board[i] == '.'){
            if(won[i] == 0){
                complite_play = 1;
                // board[i] = player;
                // break;
                return i;
            }
            else if(won[i] == -1){
                can_play = i;
            }
            else if(won[i] == 1){
                not_play = i;
            }
        // }
    }
    if(complite_play == 0 && can_play != 200){
        // board[can_play] = player;
        return can_play;
    }
    else if(complite_play == 0 && can_play == 200){
        // board[not_play] = player;
        return not_play;
    }
    else{
        return 21;                       //warning geration
    }
}

int main()
{
    int won[15] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    board_t board;
    player_t player;
    player_t computer;
    int triangle[20][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,6},{1,3,10},{8,6,13},{4,1,11},{5,8,11},{9,13,11},{14,10,11},{0,7,3},{3,2,12},{4,2,13},{8,14,7},{0,6,2},{12,6,7},{5,10,7},{1,2,9}};
    char choose;
    int input;
    int user1_tens;
    int user1_ones;
    int count = 1;
    int temp;

    printf("\n\nWELCOME to SIM (Pencil Game)\nRule:- \n always input from spaces which are not used basicly '.' \n as over writting is not allowed\n to win you have to avoid making of triangle\n");
    printf("Your choose between x and o : ");
    scanf("%c", &choose);
    player = choose;
    computer = 'x';
    if(choose == 'x'){
        computer = 'o';
    }
    printf("\nGOOD \n          GAME START\n");
    inisilize_board(board);
    print_board(board);

    while (count == 1){
        printf("Your choice (format :X --> bet[0 to 14]) : ");
        scanf("%d", &input);
        if(board[input] == '.'){
            board[input] = player;

            if(is_full(board) == 1){
                printf("draw");
                break;
            }

            if ((has_lose(board, player) == 1)){ 
                printf("       GAME OVER %c won\n",computer);
                printf("         **YOU LOST**\n    BETTER LUCK NEXT TIME");
                break;
            }

            // print_won(won);
            best_move(board,computer,won);
            // print_won(won);
            int comp_play = computer_play(board,computer,won);
            board[comp_play] = computer;
            
            if ((has_lose(board, computer) == 1)){ 
                printf("       GAME OVER %c won\n",player);
                printf("         **YOU WON**\n    COME AGAIN NEXT TIME");
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
