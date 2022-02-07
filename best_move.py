from math import inf
from tree_first import possible_moves
from eval_pos import analyze_gomoku

def my_print(move):
    print("move:", chr(move[1] + ord('A')), end="")
    print(move[0] + 1)

def best_ia_move(grid, is_ia_turn, depth):
    possible_move = possible_moves(grid)
    best_move = [-1, -1]
    best_scores = [inf, -inf]
    scores = [0, 0]

    for move in possible_move:
        # play the move
        grid[move[0]][move[1]] = -1 if is_ia_turn else 1

        # get the score associated with the new map
        if depth == 1:
            my_print(move)
            scores = analyze_gomoku(grid, is_ia_turn)
        else:
            scores = best_ia_move(grid, not is_ia_turn, depth - 1)[2]

        # unplay the move
        grid[move[0]][move[1]] = 0

        # print("move:", move, "; Score:", score, "is ia:", is_ia_turn)
        # update the highest score:
        # print("is ia turn:", is_ia_turn)
        # print("")
        if (is_ia_turn and scores[0] < best_scores[0]) or \
           ((not is_ia_turn) and scores[1] > best_scores[1]):
            best_scores = scores
            best_move = move
    return [best_move[0], best_move[1], best_scores]
