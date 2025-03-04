#!/usr/bin/python3
import random
from dataclasses import dataclass
import math

@dataclass
class Pos:
    x: int
    y: int

M = 4
S = 10
G = 10
m = [Pos(0, 0)] * M
caught = [False] * M

def printMonsters():
    print('Монстры:')
    for i in range(M):
        print(f'{i}: ', end='')
        if caught[i]:
            print('пойман')
        else:
            print(f'{m[i].x} {m[i].y}')

def placeMonsters():
    for i in range(M):
        again = True
        while again:
            m[i] = Pos(random.randint(0, S - 1), \
                    random.randint(0, S - 1))
            again = False
            for j in range(i):
                if m[i].x == m[j].x and m[i].y == m[j].y:
                    again = True

def inputMove():
    x = -1
    y = -1
    while x < 0 or x >= S or y < 0 or y >= S:
        x, y = [int(s) for s in input('Введите координаты: ').split()]
    return Pos(x, y)

def checkDistance(pos):
    for i in range(M):
        if caught[i]:
            continue
        print(f'Монстр {i + 1}', end='')
        if pos.x == m[i].x and pos.y == m[i].y:
            caught[i] = True;
            print(' пойман!')
        else:
            dx = pos.x - m[i].x
            dy = pos.y - m[i].y
            dist = math.sqrt(dx * dx + dy * dy)
            print(f' на расстоянии {dist:.3}')

def allCaught():
    for c in caught:
        if not c:
            return False
    return True

def finalMessage(move):
    if move <= G:
        print(f'Поздравляем, вы поймали всех монстров за {move} ходов!')
    else:
        print('Вы проиграли, можете попробовать снова.')

placeMonsters()
move = 1
while move <= G:
    print(f'Ход {move}')
    #printMonsters()
    checkDistance(inputMove())
    if allCaught():
        break
    move += 1
finalMessage(move)
