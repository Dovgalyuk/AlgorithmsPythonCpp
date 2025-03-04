#!/usr/bin/python3

EMPTY = '.'
BLACK = '#'
WHITE = 'O'

N = 8

board = [[EMPTY] * N for _ in range(N)]

cost = [
    [10, 1, 5, 5, 5, 5, 1, 10],
    [1, 1, 1, 1, 1, 1, 1, 1],
    [5, 1, 3, 3, 3, 3, 1, 5],
    [5, 1, 3, 3, 3, 3, 1, 5],
    [5, 1, 3, 3, 3, 3, 1, 5],
    [5, 1, 3, 3, 3, 3, 1, 5],
    [1, 1, 1, 1, 1, 1, 1, 1],
    [10, 1, 5, 5, 5, 5, 1, 10],
]

def count(player):
    res = 0
    for i in range(N):
        for j in range(N):
            if board[i][j] == player:
                res += 1
    return res

def printBoard():
    print(' ', end='')
    for j in range(N):
        print(f' {chr(ord("a") + j)}', end='')
    print()
    for i in range(N):
        print(f'{i + 1}', end='')
        for j in range(N):
            print(f' {board[i][j]}', end='')
        print()
    print(f'У вас {count(WHITE)} фишек, у меня {count(BLACK)} фишек\n')

def checkDir(player, x, y, dx, dy):
    res = 0
    xx = x + dx
    yy = y + dy
    while xx >= 0 and xx < N and yy >= 0 and yy < N:
        if board[yy][xx] == player:
            return res
        elif board[yy][xx] == EMPTY:
            return 0
        res += 1
        xx += dx
        yy += dy
    return 0

def checkMove(player, x, y):
    if x < 0 or x >= N or y < 0 or y >= N or board[y][x] != EMPTY:
        return 0
    res = 0
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            if dx == 0 and dy == 0:
                continue
            res += checkDir(player, x, y, dx, dy)
    return res

def swapDir(player, x, y, dx, dy):
    x += dx
    y += dy
    while board[y][x] != player:
        board[y][x] = player
        x += dx
        y += dy

def makeMove(player, x, y):
    board[y][x] = player
    for dx in range(-1, 2):
        for dy in range(-1, 2):
            if dx == 0 and dy == 0:
                continue
            if checkDir(player, x, y, dx, dy):
                swapDir(player, x, y, dx, dy)

def hasMove(player):
    for i in range(N):
        for j in range(N):
            if checkMove(player, j, i):
                return True
    return False


board[N // 2 - 1][N // 2 - 1] = WHITE
board[N // 2][N // 2] = WHITE
board[N // 2][N // 2 - 1] = BLACK
board[N // 2 - 1][N // 2] = BLACK

while hasMove(WHITE) or hasMove(BLACK):
    # ход игрока
    printBoard()
    if not hasMove(WHITE):
        print('Вам некуда ходить')
    else:
        x = -1
        y = -1
        while not checkMove(WHITE, x, y):
            s = input('Куда будете ходить? ')
            x = ord(s[0]) - ord('a')
            y = int(s[1]) - 1
        makeMove(WHITE, x, y)
    # ход компьютера
    printBoard()
    best = 0
    for i in range(N):
        for j in range(N):
            c = checkMove(BLACK, j, i) * cost[i][j]
            if c > best:
                x = j
                y = i
                best = c
    if best > 0:
        print(f'Мой ход {chr(ord("a") + x)}{y + 1}')
        makeMove(BLACK, x, y)
    else:
        print('Мне некуда ходить')

print('Игра окончена')
printBoard()
white = count(WHITE)
black = count(BLACK)
if white > black:
    print('Вы победили!')
elif black > white:
    print('Я выиграл!')
else:
    print('Ничья')
