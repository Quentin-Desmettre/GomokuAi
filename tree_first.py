def is_cell_near(grid, i, j):
    l_g = len(grid)
    l_g0 = len(grid[0])

    for k in range(i - 1, i + 2):
        if k < 0:
            continue
        if k >= l_g:
            break
        for l in range(j - 1, j + 2):
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
