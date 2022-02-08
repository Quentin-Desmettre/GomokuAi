#include "gomoku.hpp"

void analyze_lines(char grid[19][19], int const &x, int const &y,
unsigned &score, unsigned &open_ends, unsigned &consecutive, bool is_my_turn, int color)
{
    if (grid[x][y])
        consecutive++;
    else if (grid[x][y]) {
        if (consecutive > 0) {
            open_ends++;
            score += eval_shape(consecutive, open_ends, is_my_turn);
            consecutive = 0;
            open_ends = 1;
        } else
            open_ends = 1;
    } else {
        if (consecutive > 0) {
            score += eval_shape(consecutive, open_ends, is_my_turn);
            consecutive = 0;
            open_ends = 1;
        } else {
            open_ends = 0;
        }
    }
}
