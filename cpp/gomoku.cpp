#include "gomoku.hpp"
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <utility>
#include <vector>
#include <iostream>
#include <string>

move_t ia_move;

void ai_play(char grid[SIZE][SIZE])
{
    move_t move = calculateNextMove(grid, 3);

    grid[move.first][move.second] = -1;
    ia_move = move;
}

void print_ia_move(void)
{
    std::cout << "IA played " <<
        char('A' + ia_move.first) << ia_move.second + 1
    << std::endl;
}

int all_print(char grid[SIZE][SIZE], int turn, int tmp)
{
    print_grid(grid);
    print_winner(grid);
    if (turn % 2 == 0 && turn > 0)
        print_ia_move();
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

bool verify_intput(int &ltr, int nb)
{
    if (ltr > SIZE - 1)
        ltr -= 32;
    if (ltr < 0 or ltr > SIZE - 1)
        return true;
    if (nb < 0 or nb > SIZE - 1)
        return true;
    return false;
}

int main(void)
{
    char grid[SIZE][SIZE];
    char *get = nullptr;
    size_t s = 0;
    int turn = 0;
    int tmp = -1;

    for (int i = 0; i < SIZE; i++)
        memset(grid[i], 0, sizeof(char) * SIZE);
    for (;;) {
        tmp = all_print(grid, turn, tmp);
        if (turn % 2) {
            ai_play(grid);
            turn += 1;
            continue;
        }
        free(get);
        get = nullptr;
        if (getline(&get, &s, stdin) < 0)
            return 0;
        if (!get || strlen(get) > 4 || strlen(get) < 3)
            continue;
        int ltr = get[0] - 65;
        int nb = atoi(get + 1) - 1;
        if (verify_intput(ltr, nb))
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
