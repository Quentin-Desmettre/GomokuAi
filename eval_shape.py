from math import inf

def eval_1_row(nb_open_ends):
    if nb_open_ends == 1:
        return 0.5
    elif nb_open_ends == 2:
        return 1

def eval_2_row(nb_open_ends):
    if nb_open_ends == 1:
        return 2
    elif nb_open_ends == 2:
        return 5

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

def eval_4_row(nb_open_ends, is_my_turn):

    if nb_open_ends == 1:
        if is_my_turn:
            # 4 in a row, 1 open end and it's my turn: i almost won
            return 100000000
        else:
            # 4 in a row, 1 open end and it's not my turn: opponent will block it
            return 50
    elif nb_open_ends == 2:
        if is_my_turn:
        # 4 in a row, 2 open end and it's my turn: i will win
            return 100000000
        else:
        # 4 in a row, 2 open end and it's not my turn: i can win
            return 500000

def eval_shape(nb_row, nb_open_ends, is_my_turn):
    if nb_row >= 5:
        # i won
        return inf
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
