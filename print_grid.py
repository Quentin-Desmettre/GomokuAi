#!/bin/python

from random import *
import os

def putchr(c):
    print("%c" %c, end="")

def print_grid(grid):
    #   os.system("clear")
    l = len(grid)
    print("    ", end="")
    for i in range(l):
        print("", chr(ord('A') + i), end="")
    print("")
    print("--", end="")
    for i in range(l + 1):
        print("--", end="")
    print("")
    for i in range(len(grid)):
        if i < 9:
            putchr(' ')
        print(i + 1, "|", end=" ")
        for j in range(len(grid[0])):
            if (grid[i][j] == 0):
                putchr('.')
            if (grid[i][j] == -1):
                putchr('X')
            if (grid[i][j] == 1):
                putchr('O')
            print(" ", end ="")
        print("")
    print("")
