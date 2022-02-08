#ifndef GOMOKU_H
    #define GOMOKU_H

static const int SIZE = 19;

typedef std::pair<int, int> move_t;
typedef std::vector<move_t> move_list;

int who_won(char grid[19][19]);
void print_winner(char grid[19][19]);
unsigned eval_shape(unsigned count, unsigned open_ends, bool currentTurn);
int analyze_grid_for_color(char grid[19][19], int color, bool is_my_turn);
move_list possible_moves(char grid[SIZE][SIZE]);
#endif
