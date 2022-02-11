#ifndef GOMOKU_H
    #define GOMOKU_H
    #include <utility>
    #include <vector>
    #include <cstdarg>
    #include <cstring>
    #include <cstdio>
    #include <cstdlib>
    #include <iostream>
    #define WIN_SCORE 100000000
    #define WIN_GUARANTEE 1000000

static const int SIZE = 19;

typedef long ul;

typedef std::pair<ul, ul> move_t;
typedef std::vector<move_t> move_list;

int who_won(char **grid);
unsigned eval_shape(unsigned count, unsigned open_ends, bool currentTurn);
int analyze_grid_for_color(char **grid, int color, bool is_my_turn);
move_list possible_moves(char **grid);
void print_grid(char **grid);
move_t calculateNextMove(char **grid, int depth, bool is_ia);
move_t check_adv_finish(char **grid, bool is_ia);

#endif
