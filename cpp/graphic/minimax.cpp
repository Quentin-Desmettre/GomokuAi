#include "gomoku.hpp"
#include <algorithm>
#include "Window.hpp"

typedef std::pair<double, move_t> best_move_t;

std::pair<ul, ul> analyze_ia_pos(char **grid, bool is_ia_turn)
{
    int ia_score = analyze_grid_for_color(grid, -1, !is_ia_turn);
    ul player_score = analyze_grid_for_color(grid, 1, is_ia_turn);

    if (player_score == 0)
        player_score = 1;
    if (is_ia_turn)
        player_score *= 60;
    return move_t(ia_score, player_score);
}

move_t check_finishing_move(char **grid, bool is_ia)
{
    move_list all_moves = possible_moves(grid);
    int color = is_ia ? -1 : 1;

    for (move_t move : all_moves) {
        grid[move.first][move.second] = color;
        double tmp = analyze_grid_for_color(grid, color, true);
        grid[move.first][move.second] = 0;

        if (tmp >= 100000000)
            return move;
    }
    return move_t(-1, -1);
}

move_t random_move(char **grid)
{
    move_list list = possible_moves(grid);

    return list[rand() % list.size()];
}

best_move_t minimaxSearchAB(int depth, char **grid, bool is_max, double alpha, double beta, bool is_black = true)
{
    if (depth == 0) {
        move_t tmp = analyze_ia_pos(grid, !is_max);
        double val = is_black ? tmp.second / (60*double(tmp.first)) : tmp.first / (60*double(tmp.second));
        return best_move_t(val, move_t(-1, -1));
    }
    move_list allPossibleMoves = possible_moves(grid);

    if (allPossibleMoves.size() == 0) {
        move_t tmp = analyze_ia_pos(grid, !is_max);
        double val = is_black ? tmp.second / (60*double(tmp.first)) : tmp.first / (60*double(tmp.second));
        return best_move_t(val, move_t(-1, -1));
    }
    best_move_t bestMove(0, move_t(-1, -1));

    if (is_max) {
        bestMove.first = -1.0;
        bestMove.second = allPossibleMoves[0];

        for (move_t move : allPossibleMoves) {
            grid[move.first][move.second] = is_black ? -1 : 1;
            best_move_t tmpMove = minimaxSearchAB(depth - 1, grid, false, alpha, beta, !is_black);
            grid[move.first][move.second] = 0;

            if (tmpMove.first >= beta)
                return tmpMove;
            if (tmpMove.first > alpha)
                alpha = tmpMove.first;
            if (tmpMove.first > bestMove.first) {
                bestMove.first = tmpMove.first;
                bestMove.second = move;
            }
        }
    } else {
        bestMove.first = (unsigned)(-1);
        bestMove.second = allPossibleMoves[0];

        for (move_t move : allPossibleMoves) {
            grid[move.first][move.second] = is_black ? -1 : 1;
            best_move_t tmpMove = minimaxSearchAB(depth - 1, grid, true, alpha, beta, !is_black);
            grid[move.first][move.second] = 0;

            if (tmpMove.first <= alpha)
                return tmpMove;
            if (tmpMove.first < beta)
                beta = tmpMove.first;

            if (tmpMove.first < bestMove.first) {
                bestMove.first = tmpMove.first;
                bestMove.second = move;
            }
        }
    }
    return bestMove;
}

move_t calculateNextMove(char **grid, int depth, bool is_ia)
{
    move_t finish = check_finishing_move(grid, is_ia);

    if (finish.first >= 0 && finish.second >= 0)
        return finish;
    finish = check_adv_finish(grid, !is_ia);
    if (finish.first >= 0 && finish.second >= 0)
        return finish;
    move_list pos = possible_moves(grid);
    if (pos.empty() && !grid[0][0])
        return move_t(9, 9);

    best_move_t bestMove = minimaxSearchAB(depth, grid, true, -1.0, (unsigned)(-1), is_ia);
    if (bestMove.second.first < 0)
        return random_move(grid);
    return bestMove.second;
}
