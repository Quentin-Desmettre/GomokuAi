#include "Window.hpp"

typedef std::map<move_t, int> finish_list;

bool sorter(std::pair<move_t, int> const& a, std::pair<move_t, int> const& b)
{
    return a.second < b.second;
}

move_t get_most_present_move(finish_list &map)
{
     // Declare vector of pairs
    std::vector<std::pair<move_t, int>> A;

    // Copy key-value pair from Map
    // to vector of pairs
    for (auto& it : map) {
        A.push_back(it);
    }

    // Sort using comparator function
    sort(A.begin(), A.end(), sorter);
    return A.back().first;
}

finish_list get_all_finish(char **grid, bool is_ia)
{
    move_list all_moves = possible_moves(grid);
    finish_list finishes;
    int color = is_ia ? -1 : 1;

    for (move_t move : all_moves) {
        grid[move.first][move.second] = color;
        double tmp = analyze_grid_for_color(grid, color, true);
        grid[move.first][move.second] = 0;

        if (tmp >= 100000000) {
            if (finishes.find(move) != finishes.end())
                finishes[move]++;
            else
                finishes[move] = 1;
        }
    }
    return finishes;
}

move_t check_adv_finish(char **grid, bool is_ia)
{
    finish_list finish_move = get_all_finish(grid, is_ia);

    if (finish_move.empty())
        return move_t(-1, -1);
    return get_most_present_move(finish_move);
}
