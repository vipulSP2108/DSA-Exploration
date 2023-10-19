#include <stdio.h>
#include <assert.h>

#include "test.h"

/*
 * The status of a line.
 */
enum {
    NO = 0, /* No line */
    RED = 1,
    BLUE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */
int triangle[15][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,6},{1,3,10},{8,6,13},{1,10,3},{10,3,1},{8,13,6},{4,1,11},{5,8,11},{9,13,11},{14,10,11}};

typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

void inisilize_board(board_t board){
    for(int i =0; i<15; i++){
        board[i] = '.';
    }
}

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        printf("board[%d] -->",i);
        if(board[i] == 'x'){
            printf("%c",'x');
        }
        else if(board[i] == 'o'){
            printf("%c",'o');
        }
        else{
            printf("%c",'.');
        }
        printf("\n");
    }
    printf("\n");
}

void print_won(int won[15]){
    for(int i = 0; i<15; i++){
        printf("%d",won[i]);
    }
    printf("\n");
}


void play(int user1_tens, int user1_ones, board_t board, player_t player){
    if(user1_tens == 1 && user1_ones == 2){
        board[0] = player;
    }
    if(user1_tens == 1 && user1_ones == 3){
        board[1] = player;
    }
    if(user1_tens == 2 && user1_ones == 6){
        board[2] = player;;
    }
    if(user1_tens == 1 && user1_ones == 5){
        board[3] = player;;
    }
    if(user1_tens == 1 && user1_ones == 6){
        board[4] = player;;
    }
    if(user1_tens == 2 && user1_ones == 3){
        board[5] = player;
    }
    if(user1_tens == 2 && user1_ones == 4){
        board[6] = player;
    }
    if(user1_tens == 2 && user1_ones == 5){
        board[7] = player;
    }
    if(user1_tens == 2 && user1_ones == 6){
        board[8] = player;
    }
    if(user1_tens == 3 && user1_ones == 4){
        board[9] = player;
    }
    if(user1_tens == 3 && user1_ones == 5){
        board[10] = player;
    }
    if(user1_tens == 3 && user1_ones == 6){
        board[11] = player;
    }
    if(user1_tens == 4 && user1_ones == 5){
        board[12] = player;
    }
    if(user1_tens == 4 && user1_ones == 6){
        board[13] = player;
    }
    if(user1_tens == 5 && user1_ones == 6){
        board[14] = player;
    }
}

// int triangle[15][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,6},{1,3,10},{8,6,13},{1,10,3},{10,3,1},{8,13,6},{4,1,11},{5,8,11},{9,13,11},{14,10,11}};

int has_lose(board_t board, player_t player)
{
    int count = 0;
    for (int i = 0; i<15; i++){
        if(board[triangle[i][0]] == player && board[triangle[i][1]] == player  && board[triangle[i][2]] == player){
            printf("%c loss\n",player);
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

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int scoreß; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;


int best_move(board_t board, int won[15], player_t computer)
{
    for(int i = 0; i<15; i++){
        if((board[triangle[i][0]]== '.') && (board[triangle[i][1]]== '.') && (board[triangle[i][2]] == '.')){}
        if((board[triangle[i][0]] == computer && board[triangle[i][1]] == computer) || (board[triangle[i][1]] == computer && board[triangle[i][2]] == computer) || (board[triangle[i][2]]== computer && board[triangle[i][0]]== computer)){
            won[i] = 1;  //yaha nahi karna hai
            return 1;
        }
        else if((board[triangle[i][0]]== computer) || (board[triangle[i][1]]== computer) || (board[triangle[i][2]] == computer)){
            won[i] = -1;  //yaha kar sakte ho
            return -1;
        }
        else{
            won[i] = 0; //yaha karnahi hai
            return 0;
        }
    }
}

int new_computer_play(int play, int won[15], board_t board){
    char priv_play = board[play];
    board[play] = 'o';
    for(int j = 0; j<3; j++){
        for(int i = 0; i<15; i++){
            if(triangle[i][j]==play){
                if((board[triangle[i][0]] != 'o' && board[triangle[i][1]] != 'o') || (board[triangle[i][1]] != 'o' && board[triangle[i][2]] != 'o') || (board[triangle[i][2]]!= 'o' && board[triangle[i][0]] != 'o')){
                    board[play] = priv_play;
                    return 0;
                }
                if((board[triangle[i][0]] != 'o') || (board[triangle[i][1]] != 'o') || (board[triangle[i][2]] != 'o')){
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

int computer_play(int won[15], board_t board){
    int play_always = 21;
    int play_intermidiate = 21;
    int play_not = 21;
    for(int i= 0; i<15; i++){
        if(won[i]==0 && board[i] != 'o' && board[i] != 'x'){ //change
            play_always = i;
        }
        if(won[i]==-1 && board[i] != 'o' && board[i] != 'x'){
            play_intermidiate = i;
        }
        if(won[i]==1 && board[i] != 'o' && board[i] != 'x'){
            play_not = i;
        }
    }
    if(play_always != 21){
        return play_always;
    }
    else if(play_intermidiate != 21){
        return play_intermidiate;
    }
    else if(play_not != 21){
        return play_not;
    }
    else{
        return 200;
    }
}

void computer_play(board_t board,int won[15]){
    int complite_play = 0;
    int can_play = 200;
    int not_play = 200;
    for(int play = 0; play<15; play++){
        if(board[play] == '.'){
            if(new_computer_play(play, won, board) == 0){
                board[play] = 'o';
                complite_play = 1;
                break;
            }
            else if (new_computer_play(play, won, board) == -1){
                can_play = play;
            }
            else if (new_computer_play(play, won, board) == 21){
                continue;
            }
            else{
                not_play = play;
            }
        }
    }
    if(complite_play== 0 && can_play != 200){
        board[can_play] = 'o';
    }
    else if(complite_play== 0 && can_play == 200){
        board[not_play] = 'o';
    }
}

int main()
{
    board_t board;
    player_t player;
    player_t computer;
    int won[15] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    int triangle[15][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,6},{1,3,10},{8,6,13},{1,10,3},{10,3,1},{8,13,6},{4,1,11},{5,8,11},{9,13,11},{14,10,11}};
    player = 'x';
    computer = 'o';
    char input[3];
    int user1_tens;
    int user1_ones;
    
    inisilize_board(board);
    // print_won(won);
    print_board(board);
    int count = 1;
    int temp;
    while (count == 1){
        printf("Your choice (format :XY where X<Y) is ");
        scanf("%2s", input);
        user1_tens = input[0] - '0';
        user1_ones = input[1] - '0';

        if(user1_ones <= user1_tens){
            temp = user1_tens;
            user1_tens = user1_ones;
            user1_ones = temp;
        }   

        play(user1_tens, user1_ones, board, player);
        if (has_lose(board, player) == 1){
            break;
        }
        if (has_lose(board, computer) == 1){
            break;
        }
        if(is_full(board) == 1){
            printf("draw");
            break;
        }

        computer_play(board,won);
        if(is_full(board) == 1){
            printf("draw");
            break;
        }
        // best_move(board, won, computer);
        // int comp = computer_play(won, board);
        // if(comp == 200){
        //     printf("error");
        // }
        // print_won(won);
        // board[comp] = computer;
        printf("x --> you");
        printf("o --> you");
        print_board(board);
    }
    return 0;
}
