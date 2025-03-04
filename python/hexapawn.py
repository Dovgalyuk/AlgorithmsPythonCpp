#!/usr/bin/python3
import copy

N = 3

OK = 0
PLAYER = 1
COMPUTER = 2

bad = set()

board = []
last = []

def boardCode(board):
    res = 0
    for row in board:
        for c in row:
            res *= 3
            if c == 'p':
                res += 1
            if c == 'P':
                res += 2
    return res


def yesNo(question):
    while True:
        c = input(f'{question} (y/n) ')
        if c == 'y' or c == 'Y':
            return True
        if c == 'n' or c == 'N':
            return False

def printBoard():
    print('  abc')
    for i in range(N - 1, -1, -1):
        print(f'{i + 1} {"".join(board[i])}')
    print()

def isValidMove(player, c1, r1, c2, r2):
    if c1 < 0 or c1 >= N or r1 < 0 or r1 >= N or c2 < 0 or c2 >= N or r2 < 0 or r2 >= N:
        return False
    if c1 == c2 and r1 == r2:
        return False

    f = board[r1][c1]
    if f != player:
        return False

    dy = 1 if f == 'P' else -1
    if r1 + dy != r2:
        return False

    t = board[r2][c2]
    if c1 == c2:
        return t == '.'
    if c1 + 1 == c2 or c1 - 1 == c2:
        return t != '.' and f != t
    return False

def makeMove(board, c1, r1, c2, r2):
    board[r2][c2] = board[r1][c1]
    board[r1][c1] = '.'

def computerMove():
    global last
    foundBad = True
    mc = -1
    for r in range(1, N):
        for c in range(0, N):
            if board[r][c] == 'p':
                for c2 in range(c - 1, c + 2):
                    if isValidMove('p', c, r, c2, r - 1):
                        if foundBad:
                            mc = c
                            mr = r
                            mc2 = c2
                        b = copy.deepcopy(board)
                        makeMove(b, c, r, c2, r - 1)
                        if boardCode(b) not in bad:
                            foundBad = False
    if mc < 0:
        return PLAYER
    makeMove(board, mc, mr, mc2, mr - 1)
    if not foundBad:
        last = copy.deepcopy(board)
    print(f'Мой ход: {chr(mc + ord('a'))}{mr + 1}-{chr(mc2 + ord('a'))}{mr}\n')
    if mr == 1:
        return COMPUTER
    return OK

def playerMove():
    hasMove = False
    for r in range(N - 1):
        for c in range(N):
            if board[r][c] == 'P':
                for c2 in range(c - 1, c + 2):
                    if isValidMove('P', c, r, c2, r + 1):
                        hasMove = True
    if not hasMove:
        return COMPUTER
    c1 = 0
    r1 = 0
    c2 = 0
    r2 = 0
    while not isValidMove('P', c1, r1, c2, r2):
        line = input('Введите ваш ход: ')
        c1, r1, c2, r2 = list(line)
        c1 = ord(c1) - ord('a')
        r1 = ord(r1) - ord('1')
        c2 = ord(c2) - ord('a')
        r2 = ord(r2) - ord('1')
    makeMove(board, c1, r1, c2, r2)
    if r2 == N - 1:
        return PLAYER
    return OK

while True:
    last = []
    board = [list('PPP'), list('...'), list('ppp')]
    res = OK
    while res == OK:
        printBoard()
        res = playerMove()
        if res != OK:
            break
        printBoard()
        res = computerMove()
    printBoard()
    if res == PLAYER:
        print('Вы выиграли!')
        bad.add(boardCode(last))
    else:
        print('Я победил!')
    if not yesNo('Сыграем ещё?'):
        break
