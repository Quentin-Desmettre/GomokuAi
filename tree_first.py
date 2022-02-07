
# a tree:
# contains an array of cell

from copy import deepcopy
from math import inf

def eval_player_pos(grid):
    return grid

def eval_ia_pos(grid):
    return grid

def map_value(grid) -> int:
    l_g = len(grid)
    l_g0 = len(grid[0])
    score = 0

    for i in range(l_g):
        for j in range(l_g0):
            if j + 1 < l_g0 and grid[i][j] == grid[i][j + 1] and\
                ((j + 2 < l_g0 and grid[i][j + 2] == 0) or\
                 (j - 1 >= 0 and grid[i][j - 1] == 0)):
                score += grid[i][j] * 2
            if (i + 1 < l_g and grid[i][j] == grid[i + 1][j]) and\
                ((i + 2 < l_g and grid[i + 2][j] == 0) or\
                 (i - 1 >= 0 and grid[i - 1][j] == 0)):
                score += grid[i][j] * 2
            if (i + 1 < l_g and j + 1 < l_g0) and\
                (grid[i][j] == grid[i + 1][j + 1]):
                score += grid[i][j] * 2
    return score

def is_cell_near(grid, i, j):
    l_g = len(grid)
    l_g0 = len(grid[0])

    for k in range(i - 2, i + 3):
        if k < 0:
            continue
        if k >= l_g:
            break
        for l in range(j - 2, j + 3):
            if l < 0:
                continue
            if l >= l_g0:
                break
            if k == i and l == j:
                continue
            if grid[k][l] != 0:
                return True
    return False

def possible_moves(grid):
    moves = []
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == 0 and is_cell_near(grid, i, j):
                moves.append([i, j])
    return moves

def best_move(grid):
    best_val = inf
    best_move = [-1, -1]
    # we compute the possible moves for the ai
    moves_ia = possible_moves(grid)

    best_adv = -inf
    # for each possible move
    for i in moves_ia:
        # we play this move
        cpy = deepcopy(grid)
        cpy[i[0]][i[1]] = -1

        # compute the opponent moves
        moves_adv = possible_moves(cpy)
        # for each of these moves
        for j in moves_adv:
            # we play it
            cpy_2 = deepcopy(cpy)
            cpy_2[j[0]][j[1]] = 1

            # If the played move is worse for the opponent than any played before, we skip it
            tmp = map_value(cpy_2)
            if tmp <= best_adv:
                continue
            best_adv = tmp

            # compute the 2nd ai moves
            moves_ia_2 = possible_moves(cpy_2)
            # for each move
            for k in moves_ia_2:
                # we play it
                cpy_3 = deepcopy(cpy_2)
                cpy_3[k[0]][k[1]] = -1

                # if the played move is better for the ai than any played before, we save it
                tmp = map_value(cpy_3)
                if tmp < best_val:
                    best_val = tmp
                    best_move = k
    return best_move
