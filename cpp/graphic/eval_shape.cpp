#include "gomoku.hpp"

unsigned eval_shape(unsigned count, unsigned open_ends, bool currentTurn)
{
    if (open_ends == 0 && count < 5)
        return 0;

    switch (count) {
    case 5:
        if (currentTurn)
            return WIN_SCORE * 2;
        else
            return WIN_SCORE * 2;
    case 4:
        if (currentTurn)
            return WIN_GUARANTEE * 2;
        else
            return (open_ends == 2) ? WIN_GUARANTEE / 2 : 400;
    case 3:
        if (open_ends == 2)
            return currentTurn ? 200000 : 400;
        else
            return currentTurn ? 20 : 10;
    case 2:
        if (open_ends == 2)
            return currentTurn ? 14 : 10;
        else
            return 6;
    case 1:
        return 1;
    default:
        return WIN_GUARANTEE * 4;
    }
}
