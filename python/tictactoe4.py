#!/usr/bin/python3
import random

N = 4
field = [[None] * N for _ in range(N)]

def playerMove():
    x = -1
    y = -1
    while x < 0 or x >= N or y < 0 or y >= N or field[y][x] is not None:
        s = input('Куда будете ходить? ')
        x = ord(s[0]) - ord('a')
        y = int(s[1]) - 1
    field[y][x] = 'X'

def checkLines():
    for i in range(N):
        found = field[i][0] is not None
        for j in range(N):
            found = found and field[i][j] == field[i][0]
        if found:
            return True
        found = field[0][i] is not None
        for j in range(N):
            found = found and field[j][i] == field[0][i]
        if found:
            return True
    found = field[0][0] is not None
    for j in range(N):
        found = found and field[j][j] == field[0][0]
    return found

def canWin(player):
    if checkLines():
        return False
    for x in range(N):
        for y in range(N):
            if field[y][x] is None:
                field[y][x] = 'X' if player else 'O'
                w = canWin(not player)
                field[y][x] = None
                if not player and w:
                    return True
                if player and not w:
                    return False
    return player

def computerMove():
    for x in range(N):
        for y in range(N):
            if field[y][x] is None:
                field[y][x] = 'O'
                if canWin(True):
                    return
                field[y][x] = None
    while True:
        x = random.randint(0, N - 1)
        y = random.randint(0, N - 1)
        if field[y][x] is None:
            break
    field[y][x] = 'O'

def printField():
    print(' ', end='')
    for j in range(N):
        print(f' {chr(ord("a") + j)}', end='')
    print()
    for i in range(N):
        print(f'{i + 1}', end='')
        for j in range(N):
            if field[i][j] is not None:
                print(f' {field[i][j]}', end='')
            else:
                print(' .', end='')
        print()
    print()

moves = 0
while True:
    printField()
    if checkLines():
        print('Вы выиграли!')
        break
    if moves == N * N:
        print('Я победил!')
        break
    playerMove()
    moves += 1
    printField()
    if checkLines():
        print('Вы выиграли!')
        break
    print('Мой ход:')
    computerMove()
    moves += 1
