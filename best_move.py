from math import inf
from tree_first import possible_moves
from eval_pos import analyze_gomoku

def best_ia_move(grid, is_ia_turn, depth):
    possible_move = possible_moves(grid)
    best_move = [-1, -1]
    best_score = -inf if is_ia_turn else inf
    score = 0

    for move in possible_move:
        # play the move
        grid[move[0]][move[1]] = -1 if is_ia_turn else 1

        # get the score associated with the new map
        if depth == 1:
            print("move:", move)
            score = analyze_gomoku(grid, is_ia_turn)
        else:
            score = best_ia_move(grid, not is_ia_turn, depth - 1)[2]


        # unplay the move
        grid[move[0]][move[1]] = 0

        #print("move:", move, "; Score:", score, "is ia:", is_ia_turn)
        # update the highest score:
        print("is ia turn:", is_ia_turn)
        if (score > best_score and is_ia_turn) or \
           (score < best_score and (not is_ia_turn)):
            best_score = score
            best_move = move
    return [best_move[0], best_move[1], best_score]
