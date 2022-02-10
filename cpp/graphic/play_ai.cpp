#include "Window.hpp"
#include "gomoku.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

void play_ai(Window &window, bool is_ia)
{
    move_t move = calculateNextMove(window.get_grid(), 3, window.mode ? is_ia : true);

    window.moves.push_back(move);
    if (window.mode) {
        if (is_ia)
            window[move.first][move.second] = -1;
        else
            window[move.first][move.second] = 1;
    } else
        window[move.first][move.second] = -1;
    window.last_move = move;
}