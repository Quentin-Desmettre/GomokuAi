#include "gomoku.hpp"
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <utility>

void clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
}

void print_grid(char grid[19][19])
{
    clear();
    int l = 19;
    std::cout << "    ";
    for (int i; i < l; i++)
        std::cout << 'A' + i;
    std::cout << "\n--";
    for (int i; i < l; i++)
        std::cout <<"--";
    std::cout << "\n";
    for (int i; i < 19; i++) {
        if (i < 9)
            std::cout << " ";
        std::cout << i + 1 << "|";
        for (int j; j < 19; j++) {
            if (grid[i][j] == 0)
                std::cout << '.';
            if (grid[i][j] == -1)
                std::cout << 'X';
            if (grid[i][j] == 1)
                std::cout << 'O';
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}
