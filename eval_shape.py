from math import inf

def eval_1_row(nb_open_ends):
    if nb_open_ends == 1:
        return 0.8
    elif nb_open_ends == 2:
        return 1
    else:
        return 0

def eval_2_row(nb_open_ends):
    if nb_open_ends == 1:
        return 2.51
    elif nb_open_ends == 2:
        return 5
    else:
        return 0

def eval_3_row(nb_open_ends, is_my_turn):
    if nb_open_ends == 1:
        if is_my_turn:
            return 10
        else:
            return 5
    elif nb_open_ends == 2:
        if is_my_turn:
            return 10000
        else:
            return 50
    else:
        return 0

def eval_4_row(nb_open_ends, is_my_turn):

    if nb_open_ends == 1:
        if is_my_turn:
            return 100000000
        else:
            return 100
    elif nb_open_ends == 2:
        if is_my_turn:
            return 100000000
        else:
            return 500000
    else:
        return 0

def eval_shape(nb_row, nb_open_ends, is_my_turn):
    if nb_row >= 5:
        # i won
        return 100000000000000000
    if nb_open_ends == 0:
        # this shape is useless
        return 0
    if nb_row == 4:
        return eval_4_row(nb_open_ends, is_my_turn)
    elif nb_row == 3:
        return eval_3_row(nb_open_ends, is_my_turn)
    # we don't care anymore if it's my turn, as there is too few in a row
    elif nb_row == 2:
        return eval_2_row(nb_open_ends)
    else:
        return eval_1_row(nb_open_ends)
    return 0
