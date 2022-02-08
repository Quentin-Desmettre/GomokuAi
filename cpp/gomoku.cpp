#include "gomoku.hpp"
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <utility>
#include <vector>
#include <iostream>

void my_print(/*????????????????*/)
{
    std::cout << "move:" << 'A' /*+ ????????????????*/;
    std::cout << "move:" << /*????????????????*/ + 1;
}


void ai_play(char grid[19][19])
{
    // global ia_move
    // global total_time

    // total_time = time()
    int *ia_move;
    int *move = calculateNextMove(grid, 3);
    // total_time = time() - total_time

    grid[move[0]][move[1]] = -1;
    ia_move = move;
}

int all_print(char grid[19][19], int turn, int tmp)
{
    // global ia_move
    print_grid(grid);
    print_winner(grid);
    if (turn % 2 == 0 && turn > 0) {
        // print_time();
        // print_other_time();
        // reset_time();
        printf("IA played ");
        my_print(ia_move);
    }
    if (tmp == turn)
        printf("Error retry\n");
    if (turn % 2 == 0)
        printf("Player 1\nTurn:%i\n", turn + 1);
    else {
        printf("Player 2\nTurn:%i\n", turn + 1);
        printf("IA is thinking...\n");
    }
    return turn;
}

int verify_intput(int &ltr, int nb)
{
    if (ltr > 18)
        ltr -= 32;
    if (ltr < 0 or ltr > 18)
        return 1;
    if (nb < 0 or nb > 18)
        return 1;
    return 0;
}

int main(void)
{
    char grid[19][19];
    char *get;
    int turn = 0;
    int tmp = -1;

    for (int i = 0; i < 19; i++)
        memset(grid[i], 0, sizeof(char) * 19);
    for (;;) {
        tmp = all_print(grid, turn, tmp);
        if (turn % 2) {
            ai_play(grid);
            turn += 1;
            continue;
        }
        if (scanf(get) != 3 || strlen(get) > 3)
            continue;
        int ltr = get[0] - 65;
        int nb = atoi(get + 1) - 1;
        if (verify_intput(ltr, nb) == 1)
            continue;
        if (grid[nb][ltr] == 0) {
            if (turn % 2 == 0)
                grid[nb][ltr] = 1;
            else
                grid[nb][ltr] = -1;
        } else
            continue;
        turn += 1;
    }
    return 0;
}
