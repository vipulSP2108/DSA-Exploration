#include <stdio.h>
#include <assert.h>

#include "test.h"
typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */
int triangle[20][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,8},{1,3,10},{8,6,13},{4,1,11},{5,8,11},{9,13,11},{14,10,11},{0,7,3},{3,2,12},{4,2,13},{8,14,7},{0,6,2},{12,6,7},{5,10,7},{1,2,9}};

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

//player
void best_move_player(board_t board, player_t player, int won_player[15]){
    for(int play = 0; play<15; play++){
        int count = 0;
        if (board[play] == '.'){
            for(int i = 0; i<20; i++){ // trangle ke anda to 20
                if((triangle[i][0] == play) || (triangle[i][1] == play) || (triangle[i][2] == play)){
                    if((board[triangle[i][0]] == player && board[triangle[i][1]] == player) || (board[triangle[i][1]] == player && board[triangle[i][2]] == player) || (board[triangle[i][2]] == player && board[triangle[i][0]] == player)){
                        count = 2;
                        won_player[play] = 1;
                        break;
                    }
                    else if(((board[triangle[i][0]] == player) || (board[triangle[i][1]] == player) || (board[triangle[i][2]] == player))){
                        count = 1;
                        won_player[play] = -1;
                    }
                    else if((board[triangle[i][0]] != player) && (board[triangle[i][1]] != player) && (board[triangle[i][2]] != player)){
                        won_player[play] = 0;
                    }
                } 
            }
            if(count == 1){
                won_player[play] = -1;
            }
        }
        if(board[play] != '.'){
            won_player[play] = 2;
        }
    }
}

// old
// void best_move(board_t board, player_t player,int won[15]){
//     int can_play_best = 200;
//     int not_play_best = 200;
//     for(int play = 0; play<15; play++){
//         int count = 0;
//         char priv_play = board[play];
//         board[play] = player;
//         for(int i = 0; i<20; i++){ //trangle ke anda to 20
//             if((board[triangle[i][0]] == player && board[triangle[i][1]] == player && board[triangle[i][2]] == player)){
//                 count = 2;
//                 won[play] = 1;
//                 break;
//             }
//             else if((board[triangle[i][0]] == player && board[triangle[i][1]] == player ) || (board[triangle[i][1]] == player && board[triangle[i][2]] == player) || (board[triangle[i][2]] == player && board[triangle[i][0]] == player)){
//                 count = 1;
//                 won[play] = -1;
//             }
//             else if((board[triangle[i][0]] != player) || (board[triangle[i][1]] != player) || (board[triangle[i][2]] != player)){
//                 won[play] = 0;
//             }
//         }
//         if(count == 1){
//             won[play] = -1;
//         }
//         board[play] = priv_play;
// 
//         if(board[play] != '.'){
//             won[play] = 2;
//         }
//     }
// }

// new and triangle count added
void best_move(board_t board, player_t player,int won[15], int triangle_count[15]){
    int can_play_best = 200;
    int not_play_best = 200;
    for(int play = 0; play<15; play++){
        int tri_count = 0;
        int count = 0;
        char priv_play = board[play];
        board[play] = player;
        for(int i = 0; i<20; i++){ //trangle ke anda to 20
            if((board[triangle[i][0]] == player && board[triangle[i][1]] == player && board[triangle[i][2]] == player)){
                count = 2;
                won[play] = 1;
                break;
            }
            else if((board[triangle[i][0]] == player && board[triangle[i][1]] == player && board[triangle[i][2]] == '.') || (board[triangle[i][1]] == player && board[triangle[i][2]] == player && board[triangle[i][0]] == '.') || (board[triangle[i][2]] == player && board[triangle[i][0]] == player && board[triangle[i][1]] == '.')){
                tri_count = tri_count + 1;
                count = 1;
                won[play] = -1;
            }
            else if((board[triangle[i][0]] != player) || (board[triangle[i][1]] != player) || (board[triangle[i][2]] != player)){
                won[play] = 0;
            }
        }
        if(count == 1){
            triangle_count[play] = tri_count;
            won[play] = -1;
        }
        board[play] = priv_play;
            
        if(board[play] != '.'){
            won[play] = 2;
        }
    }
}

//1
// int computer_play(board_t board, player_t player, int won[15], int won_player[15]){
//     int final_play = 200;
//     int pravirity = 200;
//     int pravirity_value = 200;
//     int complite_play = 0;
//     int can_play = 200;
//     int not_play = 200;
//     for (int i = 0; i<15; i++){
//         if(board[i] == '.'){
//             if(won_player[i] == 0 && won[i] == 0){
//                 final_play = i;
//                 break;
//             }
//             else if(won_player[i] == -1 && won[i] == 0){
//                 pravirity = 1;
//                 final_play = i;
//             }
//             else if(won_player[i] == 0 && won[i] == -1){
//                 if(pravirity != 1){
//                     pravirity = 2;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == -1 && won[i] == -1){
//                 if(pravirity != 1 && pravirity != 2){
//                     pravirity = 3;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == 0){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3){
//                     pravirity = 4;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == -1){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4){
//                     pravirity = 5;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == 1){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4 && pravirity != 5){
//                     pravirity = 6;
//                     final_play = i;
//                 }
//             }
//         }
//     }
//     return final_play;
// }

//2
// int computer_play(board_t board, player_t player, int won[15], int won_player[15]){
//     int final_play = 200;
//     int pravirity = 200;
//     int pravirity_value = 200;
//     int complite_play = 0;
//     int can_play = 200;
//     int not_play = 200;
//     for (int i = 0; i<15; i++){
//         if(board[i] == '.'){
//             if(won_player[i] == 0 && won[i] == 0){
//                 final_play = i;
//                 break;
//             }
//             else if(won_player[i] == -1 && won[i] == 0){
//                 pravirity = 1;
//                 final_play = i;
//             }
//             else if(won_player[i] == 1 && won[i] == 0){
//                 if(pravirity != 1){
//                     pravirity = 2;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 0 && won[i] == -1){
//                 if(pravirity != 1 && pravirity != 2){
//                     pravirity = 3;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == -1 && won[i] == -1){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3){
//                     pravirity = 4;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == -1){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4){
//                     pravirity = 5;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == 1){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4 && pravirity != 5){
//                     pravirity = 6;
//                     final_play = i;
//                 }
//             }
//         }
//     }
//     return final_play;
// }

//3
// int computer_play(board_t board, player_t player, int won[15], int won_player[15]){
//     int final_play = 200;
//     int pravirity = 200;
//     int pravirity_value = 200;
//     int complite_play = 0;
//     int can_play = 200;
//     int not_play = 200;
//     for (int i = 0; i<15; i++){
//         if(board[i] == '.'){
//             if(won_player[i] == 0 && won[i] == 0){
//                 final_play = i;
//                 break;
//             }
//             else if(won_player[i] == -1 && won[i] == 0){
//                 pravirity = 1;
//                 final_play = i;
//             }
//             else if(won_player[i] == 0 && won[i] == -1){
//                 if(pravirity != 1){
//                     pravirity = 2;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == -1 && won[i] == -1){
//                 if(pravirity != 1 && pravirity != 2){
//                     pravirity = 3;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == 0){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3){
//                     pravirity = 4;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == -1){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4){
//                     pravirity = 5;
//                     final_play = i;
//                 }
//             }
//             else if(won_player[i] == 1 && won[i] == 1){
//                 if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4 && pravirity != 5){
//                     pravirity = 6;
//                     final_play = i;
//                 }
//             }
//         }
//     }
//     return final_play;
// }

//4
int computer_play(board_t board, player_t player, int won[15], int won_player[15], int triangle_count[15]){
    int tri_form = 200;
    int finalplay_tri_form = 200;
    int final_play = 200;
    int pravirity = 200;
    int pravirity_value = 200;
    int complite_play = 0;
    int can_play = 200;
    int not_play = 200;
    for (int i = 0; i<15; i++){
        if(board[i] == '.'){
            if(won_player[i] == 0 && won[i] == 0){
                final_play = i;
                break;
            }
            else if(won_player[i] == -1 && won[i] == 0){
                pravirity = 1;
                final_play = i;
            }
            else if(won_player[i] == 0 && won[i] == -1){
                if(pravirity != 1){
                    pravirity = 2;
                    int new_tri_form = triangle_count[i];
                    if(new_tri_form < tri_form){
                        tri_form = new_tri_form;
                        final_play = i;
                    }
                }
            }
            else if(won_player[i] == -1 && won[i] == -1){
                if(pravirity != 1 && pravirity != 2){
                    pravirity = 3;
                    int new_tri_form = triangle_count[i];
                    if(new_tri_form < tri_form){
                        tri_form = new_tri_form;
                        final_play = i;
                    }
                }
            }
            else if(won_player[i] == 1 && won[i] == 0){
                if(pravirity != 1 && pravirity != 2 && pravirity != 3){
                    pravirity = 4;
                    final_play = i;
                }
            }
            else if(won_player[i] == 1 && won[i] == -1){
                if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4){
                    pravirity = 5;
                    int new_tri_form = triangle_count[i];
                    if(new_tri_form < tri_form){
                        tri_form = new_tri_form;
                        final_play = i;
                    }
                }
            }
            else if(won_player[i] == 1 && won[i] == 1){
                if(pravirity != 1 && pravirity != 2 && pravirity != 3 && pravirity != 4 && pravirity != 5){
                    pravirity = 6;
                    final_play = i;
                }
            }
        }
    }
    return final_play;
}

int main()
{
    int won[15] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    int won_player[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int triangle_count[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    // int won_player[15] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};
    board_t board;
    player_t player;
    player_t computer;
    int triangle[20][3] = {{0,5,1},{5,9,6},{9,12,10},{12,14,13},{14,4,3},{4,0,8},{1,3,10},{8,6,13},{4,1,11},{5,8,11},{9,13,11},{14,10,11},{0,7,3},{3,2,12},{4,2,13},{8,14,7},{0,6,2},{12,6,7},{5,10,7},{1,2,9}};
    char choose;
    int input;
    int user1_tens;
    int user1_ones;
    int count = 1;
    int temp;

    printf("\n\nWELCOME to SIM (Pencil Game)\nRule:- \n always input from spaces which are not used basicly '.' \n as over writting is not allowed\n to win you have to avoid making of triangle\n");
    printf("Your choose between x (ie, first player) and o (ie, secound player) : ");
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

        if(player == 'o'){

            best_move_player(board, player, won_player);
            print_won(won_player);
            print_won(won);
            best_move(board,computer,won,triangle_count);
            print_won(won);
            int comp_play = computer_play(board, computer, won, won_player, triangle_count);
            printf("%d\n", comp_play);                   //bad me commentout
            board[comp_play] = computer;

            // best_move(board,computer,won, triangle_count);
            // print_won(won);
            // int comp_play = computer_play(board,computer,won, triangle_count);
            // printf("%d\n", comp_play);                   //bad me commentout
            // board[comp_play] = computer;

            if ((has_lose(board, computer) == 1)){ 
                printf("       GAME OVER %c won\n",player);
                printf("         **YOU WON**\n    COME AGAIN NEXT TIME");
                break;
            }

            print_board(board);
            printf("%c --> you\n",player);
            printf("%c --> computer\n",computer);
        }

        printf("Your choice (format :X --> bet[0 to 14]) : ");
        scanf("%d", &input);
        if(board[input] == '.'){
            board[input] = player;

            if ((has_lose(board, player) == 1)){ 
                printf("       GAME OVER %c won\n",computer);
                printf("         **YOU LOST**\n    BETTER LUCK NEXT TIME");
                break;
            }

            if(player == 'x'){
                best_move_player(board, player, won_player);
                print_won(won_player);
                print_won(won);
                best_move(board,computer,won,triangle_count);
                print_won(won);
                int comp_play = computer_play(board, computer, won, won_player, triangle_count);
                printf("%d\n", comp_play);                   //bad me commentout
                board[comp_play] = computer;

                // best_move(board,computer,won, triangle_count);
                // print_won(won);
                // int comp_play = computer_play(board,computer,won, triangle_count);
                // printf("%d\n", comp_play);                   //bad me commentout
                // board[comp_play] = computer;
                
                if ((has_lose(board, computer) == 1)){ 
                    printf("       GAME OVER %c won\n",player);
                    printf("         **YOU WON**\n    COME AGAIN NEXT TIME");
                    break;
                }

                print_board(board);
                printf("%c --> you\n",player);
                printf("%c --> computer\n",computer);
            }

            if(is_full(board) == 1){
                printf("draw");
                break;
            }
        }
        else{
            printf("already in use; no over write\n");
        }
    }
    return 0;
}
