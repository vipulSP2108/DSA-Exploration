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

typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

int triangle[16][3] = {{0,5,1}, {5,9,6}, {9,12,10}, {12,14,13}, {14,4,3}, {4,0,8}, {1,3,10}, {8,6,13}, {1,10,3}, {6,13,8}, {10,3,1}, {8,13,6}, {4,1,11}, {5,8,11}, {9,13,11}, {14,10,11}};

int has_won(board_t board, player_t player)
{
    for (int i = 0; i<16; i++){
        if(board[triangle[i][0]] && board[triangle[i][1]]  && board[triangle[i][2]] == player){
            return 1;
        }
    }
    return 0;
}

int is_full(board_t board)
{
    for (int i = 0; i < 15; i++) {
        if (board[i] == 0){
            return 1;
        }
        return 0;
    }
}

typedef struct {
    int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
    int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, player_t player)
{}

void print_board(board_t board)
{
    for (int i = 0; i < 15; ++i) {
        switch (board[i]) {
        case RED: printf("R  "); break;
        case BLUE: printf("B  "); break;
        }
    }
}

int main()
{
    /* Your game play logic. */
    /* The user should have the option to select red or blue player. */
    return 0;
}
