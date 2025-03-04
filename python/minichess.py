#!/usr/bin/python3
import copy

N = 5
KING = 1000
END = KING // 2
MAX = KING * 2

board = [
    list('RNBQK'),
    list('PPPPP'),
    list('.....'),
    list('ppppp'),
    list('rnbqk')
]

def printBoard():
    print('  abcde')
    for i in range(N - 1, -1, -1):
        print(f'{i + 1} {"".join(board[i])}')
    print()

def isOwnFigure(player, f):
    if player == 0 and f.isupper():
        return True
    if player == 1 and f.islower():
        return True
    return False

def isFreeWay(board, c1, r1, c2, r2):
    dx = c2 - c1
    if dx != 0:
        dx //= abs(dx)
    dy = r2 - r1
    if dy != 0:
        dy //= abs(dy)
    c1 += dx
    r1 += dy
    while c1 != c2 or r1 != r2:
        if board[r1][c1] != '.':
            return False
        c1 += dx
        r1 += dy
    return True

def isValidMove(board, player, c1, r1, c2, r2):
    if c1 < 0 or c1 >= N or r1 < 0 or r1 >= N or c2 < 0 or c2 >= N or r2 < 0 or r2 >= N:
        return False
    if c1 == c2 and r1 == r2:
        return False
    f = board[r1][c1]
    if f == '.':
        return False
    t = board[r2][c2]
    if not isOwnFigure(player, f) or isOwnFigure(player, t):
        return False
    if f == 'P' or f == 'p':
        dy = 1 if f == 'P' else -1
        if r1 + dy != r2:
            return False
        if c1 == c2:
            return t == '.'
        if c1 + 1 == c2 or c1 - 1 == c2:
            return isOwnFigure(1 - player, t)
        return False
    f = f.upper()
    dx = abs(c2 - c1)
    dy = abs(r2 - r1)
    if f == 'K':
        return dx <= 1 and dy <= 1
    if f == 'N':
        return (dx == 2 and dy == 1) or (dx == 1 and dy == 2)
    if f == 'R':
        if dx and dy:
            return False
        return isFreeWay(board, c1, r1, c2, r2)
    if f == 'B':
        if dx != dy:
            return False
        return isFreeWay(board, c1, r1, c2, r2)
    if f == 'Q':
        if dx != dy and dx and dy:
            return False
        return isFreeWay(board, c1, r1, c2, r2)
    return False

def makeMove(board, c1, r1, c2, r2):
    f = board[r1][c1]
    t = board[r2][c2].upper()
    board[r1][c1] = '.'
    board[r2][c2] = f
    if t == 'P':
        return 1
    if t == 'R':
        return 5
    if t == 'N':
        return 3
    if t == 'B':
        return 3
    if t == 'Q':
        return 9
    if t == 'K':
        return KING
    return 0

def playerMove():
    c1 = 0
    r1 = 0
    c2 = 0
    r2 = 0
    while not isValidMove(board, 0, c1, r1, c2, r2):
        line = input('Введите ваш ход: ')
        c1, r1, c2, r2 = list(line)
        c1 = ord(c1) - ord('a')
        r1 = ord(r1) - ord('1')
        c2 = ord(c2) - ord('a')
        r2 = ord(r2) - ord('1')
    return makeMove(board, c1, r1, c2, r2)

def checkMove(board, player, depth, score, alpha, beta):
    if depth == 0 or abs(score) >= END:
        return score
    res = MAX if player == 0 else -MAX
    for c1 in range(N):
        for r1 in range(N):
            for c2 in range(N):
                for r2 in range(N):
                    if isValidMove(board, player, c1, r1, c2, r2):
                        b = copy.deepcopy(board)
                        r = makeMove(b, c1, r1, c2, r2)
                        if player == 0:
                            r = -r
                        r = checkMove(b, 1 - player, depth - 1, score + r, alpha, beta)
                        if player == 0:
                            res = min(r, res)
                            if r < alpha:
                                return res
                            beta = min(beta, r)
                        else:
                            res = max(r, res)
                            if r > beta:
                                return res
                            alpha = max(alpha, r)
    return res

def computerMove():
    max = -MAX
    for c1 in range(N):
        for r1 in range(N):
            for c2 in range(N):
                for r2 in range(N):
                    if isValidMove(board, 1, c1, r1, c2, r2):
                        b = copy.deepcopy(board)
                        m = makeMove(b, c1, r1, c2, r2)
                        m = checkMove(b, 0, 5, m, -MAX, MAX)
                        if m > max:
                            max = m
                            mc1 = c1
                            mr1 = r1
                            mc2 = c2
                            mr2 = r2
    print(f'Мой ход: {chr(mc1 + ord('a'))}{mr1 + 1}-{chr(mc2 + ord('a'))}{mr2 + 1}\n')
    return makeMove(board, mc1, mr1, mc2, mr2)

printBoard()
while True:
    m = playerMove()
    printBoard()
    if m == KING:
        print('Вы выиграли!')
        break
    m = computerMove()
    printBoard()
    if m == KING:
        print('Я победил!')
        break
