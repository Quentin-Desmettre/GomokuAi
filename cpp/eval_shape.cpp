#define WIN_GUARANTEE 1000000
#define WIN_SCORE 100000000

unsigned eval_shape(unsigned count, unsigned open_ends, bool currentTurn)
{
    if (open_ends == 0 && count < 5)
        return 0;

    switch (count) {
    case 5:
        return WIN_SCORE;
    case 4:
        if (currentTurn)
            return WIN_GUARANTEE;
        else
            return (open_ends == 2) ? WIN_GUARANTEE / 4 : 200;
    case 3:
        if (open_ends == 2)
            return currentTurn ? 50000 : 200;
        else
            return currentTurn ? 10 : 5;
    case 2:
        if (open_ends == 2)
            return currentTurn ? 7 : 5;
        else
            return 3;
    case 1:
        return 1;
    default:
        return WIN_GUARANTEE * (4 - count);
    }
}
