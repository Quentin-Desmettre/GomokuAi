#include "Window.hpp"
#include "gomoku.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <math.h>

void play_ai(Window &window)
{
    move_t move = calculateNextMove(window.get_grid(), 4);

    window[move.first][move.second] = -1;
}