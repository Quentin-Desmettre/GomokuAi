def eval_shape(count, open_ends, currentTurn):
    win_guarantee = 1000000
    win_score = 100000000

    if open_ends == 0 and count < 5:
        return 0
    if count == 5:
        return win_score
    elif count == 4:
        if currentTurn:
            return win_guarantee
        else:
            if open_ends == 2:
                return win_guarantee / 4
            else:
                return 200
    elif count == 3:
        if open_ends == 2:
            if currentTurn:
                return 50000
            else:
                return 200
        else:
            if currentTurn:
                return 10
            else:
                return 5
    elif count == 2:
        if open_ends == 2:
            if currentTurn:
                return 7
            else:
                return 5
        else:
            return 3
    elif count == 1:
        return 1
    else:
        return win_guarantee * (4 - count)
