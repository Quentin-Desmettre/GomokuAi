#ifndef GOMOKU_H
    #define GOMOKU_H

static const int SIZE = 19;

int who_won(char grid[19][19]);
void print_winner(char grid[19][19]);
unsigned eval_shape(unsigned count, unsigned open_ends, bool currentTurn);

#endif
