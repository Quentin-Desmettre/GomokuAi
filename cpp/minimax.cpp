#include "gomoku.hpp"
#include <utility>
#include <vector>

double analyze_ia_pos(char grid[SIZE][SIZE], bool is_ia_turn)
{
    int ia_score = analyze_grid_for_color(grid, -1, is_ia_turn);
    int player_score = analyze_grid_for_color(grid, 1, is_ia_turn);

    if (player_score == 0)
        player_score = 1;
    return float(ia_score) / player_score;
}

move_t check_finishing_move(char grid[SIZE][SIZE])
{
    move_list all_moves = possible_moves(grid);

    for (move_t move : all_moves) {
        grid[move.first][move.second] = -1;
        double tmp = analyze_grid_for_color(grid, -1, true);
        grid[move.first][move.second] = 0;

        if (tmp >= 100000000)
            return move;
    }
    for (move_t move : all_moves) {
        grid[move.first][move.second] = 1;
        double tmp = analyze_grid_for_color(grid, 1, true);
        grid[move.first][move.second] = 0;

        if (tmp >= 100000000)
            return move;
    }
    return move_t(-1, -1);
}

/*
def check_finishing_move(grid):
    all_moves = possible_moves(grid)

    for move in all_moves:
        grid[move[0]][move[1]] = -1
        tmp = analyze_grid_for_color(grid, -1, True)
        grid[move[0]][move[1]] = 0

        if tmp >= 100000000:
            return [1, move]

    for move in all_moves:
        grid[move[0]][move[1]] = 1
        tmp = analyze_grid_for_color(grid, 1, True)
        grid[move[0]][move[1]] = 0

        if tmp >= 100000000:
            return [1, move]
    return [0]*/
