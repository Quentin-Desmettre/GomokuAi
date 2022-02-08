#include "gomoku.hpp"
#include <cstdarg>

typedef struct {
    int consecutive;
    int open_ends;
    int score;
} row_t;

void analyze_lines(char grid[19][19], int const &x, int const &y,
row_t &scores, bool is_my_turn, int color)
{
    if (grid[x][y])
        scores.consecutive++;
    else if (grid[x][y]) {
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

int sum_rows(row_t n[6])
{
    int sc = 0;

    for (int i = 0; i < 6; i++) {
        sc += n[i].score;
    }
    return sc;
}

int analyze_grid_for_color(char grid[19][19], int color, bool is_my_turn)
{
    row_t rows, columns, diag_bl, diag_ur, diag_ul, diag_br;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            analyze_lines(grid, i, j, rows, is_my_turn, color);
            analyze_lines(grid, j, i, rows, is_my_turn, color);


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
    return sum_rows(row_t[6]{rows, columns, diag_bl, diag_ur, diag_ul, diag_br});
}
