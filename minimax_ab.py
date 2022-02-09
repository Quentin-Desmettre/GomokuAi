from tree_first import possible_moves
from math import inf
from eval_pos import analyze_grid_for_color

def analyze_ia_pos(grid, is_ia_turn):
    ia_score = analyze_grid_for_color(grid, -1, is_ia_turn)
    player_score = analyze_grid_for_color(grid, 1, is_ia_turn)

    if player_score == 0:
        player_score = 1
    return ia_score / player_score

def minimaxSearchAB(depth, grid, is_max, alpha, beta):
    if depth == 0:
        x = analyze_ia_pos(grid, not is_max)
        return [x, None, None]

    allPossibleMoves = possible_moves(grid)
    if len(allPossibleMoves) == 0:
        x = analyze_ia_pos(grid, not is_max)
        return [x, None, None]

    bestMove = [0 for i in range(3)]

    if is_max:
        bestMove[0] = -1.0
        for move in allPossibleMoves:

            grid[move[0]][move[1]] = -1
            tmpMove = minimaxSearchAB(depth - 1, grid, False, alpha, beta)
            grid[move[0]][move[1]] = 0

            if tmpMove[0] > alpha:
                alpha = tmpMove[0]
            if tmpMove[0] >= beta:
                return tmpMove

            if tmpMove[0] > bestMove[0]:
                bestMove[0] = tmpMove[0]
                bestMove[1] = move[0]
                bestMove[2] = move[1]

    else:
        bestMove[0] = inf
        bestMove[1] = allPossibleMoves[0][0]
        bestMove[2] = allPossibleMoves[0][0]

        for move in allPossibleMoves:

            grid[move[0]][move[1]] = 1
            tmpMove = minimaxSearchAB(depth - 1, grid, True, alpha, beta)
            grid[move[0]][move[1]] = 0

            if tmpMove[0] < beta:
                beta = tmpMove[0]
            if tmpMove[0] <= alpha:
                return tmpMove

            if tmpMove[0] < bestMove[0]:
                bestMove[0] = tmpMove[0]
                bestMove[1] = move[0]
                bestMove[2] = move[1]
    return bestMove

def check_finishing_move(grid):
    all_moves = possible_moves(grid)

    for move in all_moves:
        grid[move[0]][move[1]] = -1
        tmp = analyze_grid_for_color(grid, -1, True)
        grid[move[0]][move[1]] = 0

        if tmp >= 100000000:
            return [1, move]

    for move in all_moves:
        grid[move[0]][move[1]] = 1
        tmp = analyze_grid_for_color(grid, 1, True)
        grid[move[0]][move[1]] = 0

        if tmp >= 100000000:
            return [1, move]
    return [0]

def calculateNextMove(grid, depth):
    move = []

    bestMove = minimaxSearchAB(depth, grid, True, -1.0, 100000000)
    if bestMove[1] == None:
        move = []
    else :
        move = [bestMove[1], bestMove[2]]
    return move
