#!/bin/python

def get_player_points(cell, row_1, row_2):
    if cell == 1:
        return (row_1 + 1, 0)
    elif cell == -1:
        return (0, row_2 + 1)
    else:
        return (0, 0)

def player_win(row_1, row_2):
    if row_1 >= 5:
        return 1
    elif row_2 >= 5:
        return -1
    else:
        return 0

def is_line_win(line):
    row_1 = 0
    row_2 = 0
    for i in range(len(line)):
        (row_1, row_2) = get_player_points(line[i], row_1, row_2)
        if row_1 >= 5 or row_2 >= 5:
            break
    return player_win(row_1, row_2)

def print_winner(grid):
    w = who_won(grid)
    if w == 1:
        print("Player 1 won")
    elif w == -1:
        print("Player 2 won")
    else:
        return
    exit(0)

def is_diag_win(grid, x, y):
    ch = 0
    try:
        ch = grid[x][y]
        for i in range(5):
            if grid[x + i][y + i] != ch:
                return 0
    except:
        return 0
    return ch

def is_column_or_diag_win(grid, column):
    row_1 = 0
    row_2 = 0
    diag = 0
    for i in range(len(grid)):
        diag = is_diag_win(grid, i, column)
        if diag != 0:
            return diag
        (row_1, row_2) = get_player_points(grid[i][column], row_1, row_2)
        if row_1 >= 5 or row_2 >= 5:
            break
    return player_win(row_1, row_2)

def who_won(grid):
    for i in range(len(grid)):
        win = is_line_win(grid[i])
        if win != 0:
            return win
        win = is_column_or_diag_win(grid, i)
        if win != 0:
            return win
    return 0