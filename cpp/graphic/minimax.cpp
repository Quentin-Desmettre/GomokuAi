#include "gomoku.hpp"

typedef std::pair<double, move_t> best_move_t;

double analyze_ia_pos(char **grid, bool is_ia_turn)
{
    int ia_score = analyze_grid_for_color(grid, -1, !is_ia_turn);
    int player_score = analyze_grid_for_color(grid, 1, is_ia_turn);

    if (player_score == 0)
        player_score = 1;
    return double(ia_score) / player_score;
}

move_t check_finishing_move(char **grid)
{
    move_list all_moves = possible_moves(grid);

    for (move_t move : all_moves) {
        grid[move.first][move.second] = -1;
        double tmp = analyze_grid_for_color(grid, -1, true);
        grid[move.first][move.second] = 0;

        if (tmp >= 100000000)
            return move;
    }
    return move_t(-1, -1);
}

best_move_t minimaxSearchAB(int depth, char **grid, bool is_max, double alpha, double beta)
{
    if (depth == 0)
        return best_move_t(analyze_ia_pos(grid, !is_max), move_t(-1, -1));

    move_list allPossibleMoves = possible_moves(grid);

    if (allPossibleMoves.size() == 0)
        return best_move_t(analyze_ia_pos(grid, !is_max), move_t(-1, -1));
    best_move_t bestMove(0, move_t(0, 0));

    if (is_max) {
        bestMove.first = -1.0;

        for (move_t move : allPossibleMoves) {
            grid[move.first][move.second] = -1;
            best_move_t tmpMove = minimaxSearchAB(depth - 1, grid, false, alpha, beta);
            grid[move.first][move.second] = 0;

            if (tmpMove.first > alpha)
                alpha = tmpMove.first;
            if (tmpMove.first >= beta)
                return tmpMove;
            
            if (tmpMove.first > bestMove.first) {
                bestMove.first = tmpMove.first;
                bestMove.second = move;
            }
        }
    } else {
        bestMove.first = 100000000;
        bestMove.second = allPossibleMoves[0];

        for (move_t move : allPossibleMoves) {
            grid[move.first][move.second] = 1;
            best_move_t tmpMove = minimaxSearchAB(depth - 1, grid, true, alpha, beta);
            grid[move.first][move.second] = 0;

            if (tmpMove.first < beta)
                beta = tmpMove.first;
            if (tmpMove.first <= alpha)
                return tmpMove;
            
            if (tmpMove.first < bestMove.first) {
                bestMove.first = tmpMove.first;
                bestMove.second = move;
            }
        }
    }
    return bestMove;
}

move_t calculateNextMove(char **grid, int depth)
{
    move_t finish = check_finishing_move(grid);

    if (finish.first >= 0 && finish.second >= 0)
        return finish;

    best_move_t bestMove = minimaxSearchAB(depth, grid, true, -1.0, 100000000);

    return (bestMove.second.first < 0) ? move_t(0, 0) : bestMove.second;
}
