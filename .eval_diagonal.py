from eval_pos import analyze_lines

def analyze_diag_right(grid, color, is_my_turn):
    consecutive_bl = 0
    score_bl = 0
    nb_ends_bl = 0

    consecutive_ur = 0
    score_ur = 0
    nb_ends_ur = 0

    for i in range(11):
        for j in range(len(grid) - i):
            # bottom left
            score_bl, nb_ends_bl, consecutive_bl =\
                analyze_lines(i + j, j, score_bl, nb_ends_bl, consecutive_bl, grid, is_my_turn, color)
            # up right
            if j > 0 and i != 10:
                score_ur, nb_ends_ur, consecutive_ur =\
                    analyze_lines(j - 1, i + j, score_ur, nb_ends_ur, consecutive_ur, grid, is_my_turn, color)
    return score_ur + score_bl

def analyze_diag_left(grid, color, is_my_turn):
    consecutive_bl = 0
    score_bl = 0
    nb_ends_bl = 0

    consecutive_ur = 0
    score_ur = 0
    nb_ends_ur = 0

    for i in range(11):
        for j in range(len(grid) - i):
            # bottom left
            score_bl, nb_ends_bl, consecutive_bl =\
                analyze_lines(14 - (i + j), j, score_bl, nb_ends_bl, consecutive_bl, grid, is_my_turn, color)
            # up right
            if j > 0 and i != 10:
                score_ur, nb_ends_ur, consecutive_ur =\
                    analyze_lines(14 - (j - 1), i + j, score_ur, nb_ends_ur, consecutive_ur, grid, is_my_turn, color)
    return score_ur + score_bl

