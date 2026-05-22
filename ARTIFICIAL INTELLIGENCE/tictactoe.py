import math
def print_board(board):
    print("-------------")
    for i in range(3):
        print("|", end=" ")
        for j in range(3):
            print(board[i][j], "|", end=" ")
        print()
        print("-------------")
        
def evaluate(board):
    for i in range(3):
        if board[i][0] != '_' and board[i][0] == board[i][1] == board[i][2]:
           return 10 if board[i][0] == 'X' else -10
    for j in range(3):
        if board[0][j] != '_' and board[0][j] == board[1][j] == board[2][j]:
           return 10 if board[0][j] == 'X' else -10
    if board[0][0] != '_' and board[0][0] == board[1][1] == board[2][2]:
        return 10 if board[0][0] == 'X' else -10
    if board[0][2] != '_' and board[0][2] == board[1][1] == board[2][0]:
        return 10 if board[0][2] == 'X' else -10
    return 0
  
  
def is_moves_left(board):
    for row in board:
        if '_' in row:
            return True
    return False
def minimax(board, depth, is_max):
    score = evaluate(board)
    if score == 10:
        return score - depth
    if score == -10:
        return score + depth
    if not is_moves_left(board):
        return 0
    if is_max:
        best = -math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == '_':
                    board[i][j] = 'X'
                    best = max(best, minimax(board, depth + 1, False))
                    board[i][j] = '_'
        return best
    else:
        best = math.inf
        for i in range(3):
            for j in range(3):
                if board[i][j] == '_':
                    board[i][j] = 'O'
                    best = min(best, minimax(board, depth + 1, True))
                    board[i][j] = '_'
        return best
def find_best_move(board):
    best_val = -math.inf
    best_move = (-1, -1)
    for i in range(3):
        for j in range(3):
            if board[i][j] == '_':
                board[i][j] = 'X'
                move_val = minimax(board, 0, False)
                board[i][j] = '_'
                if move_val > best_val:
                    best_move = (i, j)
                    best_val = move_val
    return best_move
def play_game():
    board = [['_', '_', '_'],
            ['_', '_', '_'],
            ['_', '_', '_']]
    print("You are O, AI is X\n")
    print_board(board)
    while True:
        try:
         row = int(input("\nEnter row (0-2): "))
         col = int(input("Enter column (0-2): "))
        except:
            print("Invalid input!")
            continue
        if row not in range(3) or col not in range(3) or board[row][col] != '_':
            print("Invalid move. Try again.")
            continue
        board[row][col] = 'O'
        print_board(board)
        if evaluate(board) == -10:
            print("You win! (This should never happen if AI plays optimally)")
            return
        if not is_moves_left(board):
            print("It's a draw!")
            return
        print("AI is thinking...\n")
        r, c = find_best_move(board)
        board[r][c] = 'X'
        print_board(board)
        if evaluate(board) == 10:
            print("You lose!")
            return
        if not is_moves_left(board):
            print("It's a draw!")
            return
if __name__ == "__main__":
    play_game()
 