#include "gomoku.hpp"
#include "Window.hpp"

void get_player_points(char cell_type, int &row_1, int &row_2)
{
    if (cell_type == 1) {
        row_1++;
        row_2 = 0;
    } else if (cell_type == -1) {
        row_1 = 0;
        row_2++;
    } else {
        row_1 = 0;
        row_2 = 0;
    }
}

int player_win(int row_1, int row_2)
{
    if (row_1 >= 5)
        return 1;
    if (row_2 >= 5)
        return -1;
    return 0;
}

int is_line_win(char line[SIZE])
{
    int row_1 = 0, row_2 = 0;

    for (int i = 0; i < SIZE; i++) {
        get_player_points(line[i], row_1, row_2);
        if (row_1 >= 5 || row_2 >= 5)
            break;
    }
    return player_win(row_1, row_2);
}

int check_diag_right(char **grid, int x, int y)
{
    char ch = grid[x][y];

    for (int i = 0; i < 5; i++) {
        if (x + i >= SIZE || y + i >= SIZE)
            return 0;
        if (grid[x + i][y + i] != ch)
            return 0;
    }
    return ch;
}

int check_diag_left(char **grid, int x, int y)
{
    char ch = grid[x][y];

    for (int i = 0; i < 5; i++) {
        if (x + i >= SIZE || y - i < 0)
            return 0;
        if (grid[x + i][y - i] != ch)
            return 0;
    }
    return ch;
}

int is_diag_win(char **grid, int x, int y)
{
    int c = check_diag_right(grid, x, y);

    return (c != 0) ? c : check_diag_left(grid, x, y);
}

int is_column_win(char **grid, int column)
{
    int row_1 = 0;
    int row_2 = 0;

    for (int i = 0; i < SIZE; i++) {
        get_player_points(grid[i][column], row_1, row_2);
        if (row_1 >= 5 || row_2 >= 5)
            break;
    }
    return player_win(row_1, row_2);
}

int who_won(char **grid)
{
    int win = 0;

    for (int i = 0; i < SIZE; i++) {
        win = is_line_win(grid[i]);
        if (win != 0)
            return win;
        win = is_column_win(grid, i);
        if (win != 0)
            return win;
    }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            win = is_diag_win(grid, i, j);
            if (win != 0)
                return win;
        }
    return 0;
}

void print_winner(Window &window)
{
    int w = who_won(window.get_grid());

    if (w == 1)
        window.change_victory(1);
    else if (w == -1)
        window.change_victory(2);
    else
        return;
}
