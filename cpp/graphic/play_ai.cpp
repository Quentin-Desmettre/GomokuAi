#include "Window.hpp"
#include "gomoku.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

void play_ai(Window &window)
{
    char **grid = window.get_grid();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j])
                printf("%c", grid[j][i] == 1 ? 'O' : 'X');
            else
                printf("%c", '.');
        }
        printf("\n");
    }
    printf("\n");
    move_t move = calculateNextMove(window.get_grid(), 3);

    window[move.first][move.second] = -1;
}