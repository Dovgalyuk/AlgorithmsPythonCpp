#!/usr/bin/python3

N = 6
K1 = N
K2 = 2 * N + 1
First1 = 0
Last1 = N - 1
First2 = K1 + 1
Last2 = K2 - 1
SZ = N * 2 + 2
S = 6
TOTAL = S * N * 2

board = [0] * SZ

MoveNext = 0
MoveAgain = 1
MoveEnd = 2

def printBoard():
    print(' ', end='')
    for i in range(N, 0, -1):
        print(f'{i:>3}', end='')
    print()
    print(' ', end='')
    for i in range(Last2, First2 - 1, -1):
        print(f'{board[i]:>3}', end='')
    print()
    print(f'{board[K2]:>2}                  {board[K1]}')
    print(' ', end='')
    for i in range(First1, Last1 + 1):
        print(f'{board[i]:>3}', end='')
    print()
    print(' ', end='')
    for i in range(1, N + 1):
        print(f'{i:>3}', end='')
    print()
    print()

def makeMove(board, m):
    # посев камней
    s = board[m]
    board[m] = 0
    cur = m
    player = 0 if m <= Last1 else 1
    kalahOpp = K2 if player == 0 else K1
    while s > 0:
        cur = (cur + 1) % SZ
        if cur != kalahOpp:
            s -= 1
            board[cur] += 1
    # захват камней противника
    lastPlayer = 0 if cur <= Last1 else 1
    opp = SZ - 2 - cur
    kalah = K1 if player == 0 else K2
    if cur != kalah and player == lastPlayer and board[cur] == 1 and board[opp]:
        # обновить калах
        board[kalah] += board[cur] + board[opp]
        # очистить лунки
        board[cur] = 0
        board[opp] = 0
    # проверка, стал ли ход последним
    sum1 = 0
    sum2 = 0
    for i in range(N):
        sum1 += board[First1 + i]
        sum2 += board[First2 + i]
    if sum1 == 0 or sum2 == 0:
        for i in range(N):
            board[K1] += board[First1 + i]
            board[K2] += board[First2 + i]
            board[First1 + i] = 0
            board[First2 + i] = 0
        return MoveEnd
    # повторный ход
    if cur == kalah:
        return MoveAgain

    return MoveNext

def playerMove():
    m = -1
    while m < 0 or m >= N or board[First1 + m] == 0:
        m = int(input('Выберите лунку с камнями: '))
        m -= 1
    return makeMove(board, First1 + m)

def checkMove(brd, player, m, depth, alpha, beta):
    board = brd.copy()
    mr = makeMove(board, m)
    if mr == MoveEnd or depth == 0:
        # оценка позиции
        return board[K2] - board[K1]
    nextPlayer = 1 - player
    if mr == MoveAgain:
        nextPlayer = player
    res = TOTAL if nextPlayer == 0 else -TOTAL
    for i in range(N):
        m = i + (First2 if nextPlayer > 0 else First1)
        if board[m] > 0:
            r = checkMove(board, nextPlayer, m, depth - 1, alpha, beta)
            # игрок минимизирует оценку
            if nextPlayer == 0:
                res = min(r, res)
                if res < alpha:
                    break
                beta = min(beta, res)
            # компьютер максимизирует оценку
            if nextPlayer == 1:
                res = max(r, res)
                if res > beta:
                    break
                alpha = max(alpha, res)
    return res

def computerMove():
    m = -1
    max = -TOTAL
    for i in range(First2, Last2 + 1):
        if board[i] > 0:
            r = checkMove(board, 1, i, 10, -TOTAL, TOTAL)
            if r > max:
                m = i
                max = r

    print(f'Мой ход {m - First2 + 1}')
    return makeMove(board, m)

for i in range(N):
    board[First1 + i] = S
    board[First2 + i] = S

while True:
    res = MoveAgain
    while res == MoveAgain:
        printBoard()
        res = playerMove()
    if res == MoveEnd:
        break
    res = MoveAgain
    while res == MoveAgain:
        printBoard()
        res = computerMove()
    if res == MoveEnd:
        break
printBoard();
if board[K1] > board[K2]:
    print('Вы победили!')
elif board[K2] > board[K1]:
    print('Я выиграл!')
else:
    print('Ничья.')
