#include "gomoku.hpp"
#include <vector>
#include <utility>

bool is_cell_near(char grid[SIZE][SIZE], int i, int j)
{
    for (int k = i - 1, m = i + 2; k < m; k++) {
        if (k < 0)
            continue;
        if (k >= SIZE)
            break;
        for (int l = j - 1, m = j + 2; l < m; l++) {
            if (l < 0)
                continue;
            if (l >= SIZE)
                break;
            if (k == i && l == j)
                continue;
            if (grid[k][l] != 0)
                return true;
        }
    }
    return false;
}

std::vector<std::pair<int, int>> possible_moves(char grid[SIZE][SIZE])
{
    std::vector<std::pair<int, int>> moves;
    std::pair<int, int> p;

    for (int i = 0; i < SIZE; i++) {
        p.first = i;
        for (int j = 0; j < SIZE; j++) {
            p.second = j;
            if (grid[i][j] == 0 && is_cell_near(grid, i, j))
                moves.push_back(p);
        }
    }
    return moves;
}
