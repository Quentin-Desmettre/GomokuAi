#!/bin/python

from math import *
from time import time
from print_grid import *
from win_condition import print_winner
from minimax_ab import calculateNextMove
from best_move import my_print
from eval_pos import print_time, reset_time

ia_move = []

total_time = 0

def print_other_time():
    print(total_time)

def all_print(arr, turn, tmp):
    global ia_move
    print_grid(arr)
    print_winner(arr)
    if turn % 2 == 0 and turn > 0:
        print_time()
        print_other_time()
        reset_time()
        print("IA played ", end="")
        my_print(ia_move)
    if (tmp == turn):
        print("Error retry")
    if turn % 2 == 0:
        print("Player 1\nTurn:", turn + 1)
    else:
        print("Player 2\nTurn:", turn + 1)
    return turn

def verify_intput(ltr, nb):
    if ltr < 0 or ltr > 14:
        return 1
    if nb < 0 or nb > 14:
        return 1
    return 0


def ai_play(grid):
    global ia_move
    global total_time

    total_time = time()
    move = calculateNextMove(grid, 3)
    total_time = time() - total_time

    grid[move[0]][move[1]] = -1
    ia_move = move
    return grid

def main():
    global ia_move
    arr = [[0 for i in range(15)] for j in range(15)]
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
        if ltr > 14:
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
