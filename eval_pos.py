from eval_shape import eval_shape

def end_of_sequence(consecutive, open_ends, is_my_turn):
    s = eval_shape(consecutive, open_ends, is_my_turn)
    return s

def analyze_lines(x, y, score, open_ends, consecutive, grid, is_my_turn, color):
    if grid[x][y] == color:
        consecutive += 1
    elif grid[x][y] == 0:
        if consecutive > 0:
            open_ends += 1
            score += end_of_sequence(consecutive, open_ends, is_my_turn)
            consecutive = 0
            open_ends = 1
        else:
            open_ends = 1
    else:
        if consecutive > 0:
            score += end_of_sequence(consecutive, open_ends, is_my_turn)
            consecutive = 0
            open_ends = 1
        else:
            open_ends = 0
    return score, open_ends, consecutive

def analyze_grid_for_color(grid, color, is_my_turn):
    # rows:
    consecutive_r = 0
    open_ends_r = 0
    score_r = 0

    # columns
    consecutive_c = 0
    open_ends_c = 0
    score_c = 0

    # diagonals
    consecutive_bl = 0
    score_bl = 0
    nb_ends_bl = 0

    consecutive_ur = 0
    score_ur = 0
    nb_ends_ur = 0

    consecutive_ul = 0
    score_ul = 0
    nb_ends_ul = 0

    consecutive_br = 0
    score_br = 0
    nb_ends_br = 0

    l = len(grid)
    lg = len(grid[0])
    for i in range(l):
        for j in range(lg):
            score_r, open_ends_r, consecutive_r = analyze_lines(i, j, score_r, open_ends_r, consecutive_r, grid, is_my_turn, color)
            score_c, open_ends_c, consecutive_c = analyze_lines(j, i, score_c, open_ends_c, consecutive_c, grid, is_my_turn, color)

            if j < l - i:
                # bottom left
                score_bl, nb_ends_bl, consecutive_bl =\
                    analyze_lines(i + j, j, score_bl, nb_ends_bl, consecutive_bl, grid, is_my_turn, color)
                # up right
                if j > 0 and i != 10:
                    score_ur, nb_ends_ur, consecutive_ur =\
                        analyze_lines(j - 1, i + j, score_ur, nb_ends_ur, consecutive_ur, grid, is_my_turn, color)
                # up left
                score_ul, nb_ends_ul, consecutive_ul =\
                    analyze_lines(14 - (i + j), j, score_ul, nb_ends_ul, consecutive_ul, grid, is_my_turn, color)
                # down right
                if j > 0 and i != 10:
                    score_br, nb_ends_br, consecutive_br =\
                        analyze_lines(14 - (j - 1), i + j, score_br, nb_ends_br, consecutive_br, grid, is_my_turn, color)

        consecutive_r = 0
        consecutive_c = 0
        consecutive_bl = 0
        consecutive_ur = 0
        consecutive_ul = 0
        consecutive_br = 0
    return score_r + score_c + score_bl + score_ur + score_ul + score_br
