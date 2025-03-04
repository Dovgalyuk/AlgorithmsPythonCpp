#!/usr/bin/python3
import queue

N = 3
SIZE = N * N

positions = {}

def getKey(board):
    r = 0
    for x in board:
        r = r * 9 + x
    return r

def findEmpty(board):
    for i in range(SIZE):
        if board[i] == 0:
            return i
    return -1

def printSolution(board):
    dir = positions[getKey(board)]
    empty = findEmpty(board)
    next = -1
    if dir == 1:
        next = empty + 1
    elif dir == 2:
        next = empty - 1
    elif dir == 3:
        next = empty + N
    elif dir == 4:
        next = empty - N
    if next != -1:
        board[next], board[empty] = board[empty], board[next]
        printSolution(board)
        board[next], board[empty] = board[empty], board[next]

    for x in board:
        print(x, end='')
    print()


start = [int(x) for x in input().split()]
b = [0] * SIZE
for s in start:
    if s >= 0 and s < SIZE:
        b[s] = 1
# проверить ввод
if sum(b) != SIZE:
    print('Некорректная позиция')
    exit(0)

q = queue.Queue()
q.put(start)
positions[getKey(start)] = 0
while not q.empty():
    board = q.get()
    empty = findEmpty(board)
    # перебираем все направления движения
    for i in range(1, 5):
        next = -1
        if i == 1 and empty % N != 0:
            next = empty - 1
        elif i == 2 and empty % N != N - 1:
            next = empty + 1
        elif i == 3 and empty >= N:
            next = empty - N
        elif i == 4 and empty < N * N - N:
            next = empty + N
        if next != -1:
            b = board.copy()
            b[empty], b[next] = b[next], b[empty]
            key = getKey(b)
            if key not in positions:
                positions[key] = i
                q.put(b)

final = [1, 2, 3, 4, 5, 6, 7, 8, 0]
if getKey(final) not in positions:
    print('Решения не существует!')
else:
    printSolution(final)
