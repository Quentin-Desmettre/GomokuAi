#!/bin/python

from math import *
from print_grid import *
from win_condition import print_winner
from tree_first import best_move, possible_moves

def all_print(arr, turn, tmp):
    print_grid(arr)
    print_winner(arr)
    if (tmp == turn):
        print("Error retry")
    if turn % 2 == 0:
        print("Player 1\nTurn:", turn + 1)
    else:
        print("Player 2\nTurn:", turn + 1)
    return turn

def verify_intput(ltr, nb):
    if ltr < 0 or ltr > 19:
        return 1
    if nb < 0 or nb > 19:
        return 1
    return 0

def ai_play(grid):
    move = best_move(grid)
    grid[move[0]][move[1]] = -1
    return grid

def main():
    arr = [[0 for i in range(20)] for j in range(20)]
    get = []
    turn = 0
    tmp = -1

    while True:
        tmp = all_print(arr, turn, tmp)
        if turn % 2:
            arr = ai_play(arr)
            turn += 1
            continue
        get = (str(input()))
        if len(get) > 3:
            continue
        ltr = ord(get[0][0]) - 65
        try:
            nb = int(get[1:]) - 1
        except:
            continue
        if ltr > 20:
            ltr -= 32
        if (verify_intput(ltr, nb) == 1):
            continue
        if arr[nb][ltr] == 0:
            if turn % 2 == 0:
                arr[nb][ltr] = 1
            else:
                arr[nb][ltr] = -1
        else:
            continue
        turn += 1


main()
