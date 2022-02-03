#!/bin/python

from math import *
from operator import le
import string
from print_grid import *

arr = [[0 for i in range(20)] for j in range(20)]
get = []
turn = 0
tmp = -1

def all_print(arr, turn, tmp):
    print_grid(arr)
    if (tmp == turn):
        print("Error retry")
    if turn % 2 == 0:
        print("Player 1\nTurn:", turn + 1)
    else:
        print("Player 2\nTurn:", turn + 1)
    return turn

while True:
    tmp = all_print(arr, turn, tmp)
    get = (str(input()))
    if len(get) > 3:
        continue
    ltr = ord(get[0][0]) - 65
    nb = int(get[1:]) - 1
    if ltr > 20:
        ltr -= 32
    if ltr < 0 or ltr > 19:
        continue
    if nb < 0 or nb > 19:
        continue
    if arr[nb][ltr] == 0:
        if turn % 2 == 0:
            arr[nb][ltr] = 1
        else:
            arr[nb][ltr] = -1
    else:
        continue
    turn += 1



