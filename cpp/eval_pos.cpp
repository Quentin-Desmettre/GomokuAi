#include "gomoku.hpp"

typedef struct {
    int consecutive;
    int open_ends;
    int score;
} row_t;

void analyze_lines(char grid[SIZE][SIZE], int const &x, int const &y,
row_t &scores, bool is_my_turn, int color)
{
    if (grid[x][y] == color)
        scores.consecutive++;
    else if (grid[x][y] == 0) {
        if (scores.consecutive > 0) {
            scores.open_ends++;
            scores.score += eval_shape(scores.consecutive, scores.open_ends, is_my_turn);
            scores.consecutive = 0;
            scores.open_ends = 1;
        } else
            scores.open_ends = 1;
    } else {
        if (scores.consecutive > 0) {
            scores.score += eval_shape(scores.consecutive, scores.open_ends, is_my_turn);
            scores.consecutive = 0;
            scores.open_ends = 1;
        } else {
            scores.open_ends = 0;
        }
    }
}

int analyze_grid_for_color(char grid[SIZE][SIZE], int color, bool is_my_turn)
{
    row_t rows, columns, diag_bl, diag_ur, diag_ul, diag_br;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            analyze_lines(grid, i, j, rows, is_my_turn, color);
            analyze_lines(grid, j, i, columns, is_my_turn, color);


            if (j < SIZE - i) {

                analyze_lines(grid, i + j, j, diag_bl, is_my_turn, color);
                analyze_lines(grid, (SIZE - 1) - (i + j), j, diag_ul, is_my_turn, color);

                if (j > 0 && i != SIZE - 5) {
                    analyze_lines(grid, j - 1, i + j, diag_ur, is_my_turn, color);
                    analyze_lines(grid, (SIZE - 1) - (j - 1), i + j, diag_br, is_my_turn, color);
                }
            }
        }
    }
    return rows.score + columns.score + diag_bl.score + diag_ur.score + diag_ul.score + diag_br.score;
}
