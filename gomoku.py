#!/bin/python

from math import *
from time import time
from print_grid import *
from win_condition import print_winner
from minimax_ab import calculateNextMove
from best_move import my_print

ia_move = []

def all_print(arr, turn, tmp):
    global ia_move
    print_grid(arr)
    print_winner(arr)
    if turn % 2 == 0 and turn > 0:
        print("IA played ", end="")
        my_print(ia_move)
    if (tmp == turn):
        print("Error retry")
    if turn % 2 == 0:
        print("Player 1\nTurn:", turn + 1)
    else:
        print("Player 2\nTurn:", turn + 1)
        print("IA is thinking...")
    return turn

def verify_intput(ltr, nb):
    if ltr < 0 or ltr > 18:
        return 1
    if nb < 0 or nb > 18:
        return 1
    return 0

def ai_play(grid):
    global ia_move

    move = calculateNextMove(grid, 4)
    grid[move[0]][move[1]] = -1

    ia_move = move
    return grid

def main():
    arr = [[0 for i in range(19)] for j in range(19)]
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
        try:
            ltr = ord(get[0][0]) - 65
            nb = int(get[1:]) - 1
        except:
            continue
        if ltr > 18:
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
