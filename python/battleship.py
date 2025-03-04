#!/usr/bin/python3
import random

N = 10
S = 10
shipLen = [4, 3, 3, 2, 2, 2, 1, 1, 1, 1]

Missed = 0
Hit = 1
Sunk = 2

class Player:
    def __init__(self):
        self.field = [[0] * N for _ in range(N)]
        self.hits = [[False] * N for _ in range(N)]
        self.ships = [0] * S

def alive(pl):
    for s in pl.ships:
        if s > 0:
            return True
    return False

def printField(pl, hide):
    print('  ', end='')
    for j in range(N):
        print(f' {j + 1}', end='')
    print()
    for i in range(N):
        print(f'{i + 1:>2}', end='')
        for j in range(N):
            print(' ', end='')
            if pl.hits[i][j]:
                if pl.field[i][j] > 0:
                    print('*', end='')
                else:
                    print('x', end='')
            elif not hide and pl.field[i][j] > 0:
                print('O', end='')
            else:
                print('.', end='')
        print()
    print()

def checkShip(pl, x, y, len, v):
    if x < 0 or y < 0:
        return False

    endx = x if v else x + len - 1
    endy = y + len - 1 if v else y
    if endx >= N or endy >= N:
        return False

    for i in range(-1, len + 1):
        for j in range(-1, 2):
            xx = x + j if v else x + i
            yy = y + i if v else y + j
            if xx >= 0 and xx < N and yy >= 0 and yy < N:
                if pl.field[yy][xx] > 0:
                    return False
    return True

def placeShip(pl, x, y, type, v):
    len = shipLen[type]
    for i in range(len):
        xx = x if v else x + i
        yy = y + i if v else y
        pl.field[yy][xx] = type + 1
    pl.ships[type] = len

def shoot(pl, x, y):
    if not pl.hits[y][x]:
        pl.hits[y][x] = True
        if pl.field[y][x] > 0:
            pl.ships[pl.field[y][x] - 1] -= 1
            if pl.ships[pl.field[y][x] - 1] == 0:
                print('Убит!')

                for i in range(N):
                    for j in range(N):
                        if pl.field[i][j] == pl.field[y][x]:
                            for ii in range(i - 1, i + 2):
                                for jj in range(j - 1, j + 2):
                                    if ii >= 0 and ii < N and jj >= 0 and jj < N:
                                        pl.hits[ii][jj] = True
                return Sunk
            else:
                print('Ранен!')
                return Hit
        else:
            print('Мимо!')
    return Missed


player = Player()
computer = Player()
shipX = -1
shipY = -1
# расстановка кораблей игрока
for s in range(S):
    printField(player, False)
    while True:
        str = input(f'Введите позицию для корабля {s + 1} ({shipLen[s]}-палубный) (x, y{", v" if shipLen[s] > 1 else ""}): ')
        if shipLen[s] > 1:
            x, y, c = str.split()
        else:
            x, y = str.split()
        x = int(x) - 1
        y = int(y) - 1
        v = c == 'v' or c == 'V'
        if checkShip(player, x, y, shipLen[s], v):
            break
    placeShip(player, x, y, s, v)

# расстановка кораблей компьютера
for s in range(S):
    while True:
        x = random.randint(0, N - 1)
        y = random.randint(0, N - 1)
        v = random.choice([True, False])
        if checkShip(computer, x, y, shipLen[s], v):
            break
    placeShip(computer, x, y, s, v)

# главный игровой цикл
while True:
    # ход компьютера
    while alive(player):
        print('Ваше поле:')
        printField(player, False)
        if shipX == -1:
            len = 0
            for i in range(S):
                if player.ships[i] > 0:
                    len = shipLen[i]
                    break
            while True:
                x = random.randint(0, N - 1)
                y = random.randint(0, N - 1)
                if not player.hits[y][x] and (x + y) % len == 0:
                    break
        else:
            x = -1
            for j in range(shipX - 1, -1, -1):
                if not player.hits[shipY][j]:
                    x = j
                    y = shipY
                    break
                elif player.field[shipY][j] == 0:
                    break
            if x < 0:
                for j in range(shipX + 1, N):
                    if not player.hits[shipY][j]:
                        x = j
                        y = shipY
                        break
                    elif player.field[shipY][j] == 0:
                        break
            if x < 0:
                for i in range(shipY - 1, -1, -1):
                    if not player.hits[i][shipX]:
                        x = shipX
                        y = i
                        break
                    elif player.field[i][shipX] == 0:
                        break
            if x < 0:
                for i in range(shipY + 1, N):
                    if not player.hits[i][shipX]:
                        x = shipX
                        y = i
                        break
                    elif player.field[i][shipX] == 0:
                        break
        print(f'Мой ход: {x + 1}, {y + 1}')
        s = shoot(player, x, y)
        if s == Hit and shipX < 0:
            shipX = x
            shipY = y
        elif s == Sunk:
            shipX = -1
        elif s == Missed:
            print('Ваше поле:')
            printField(player, False)
            break

    if not alive(player):
        print('Ваше поле:')
        printField(player, False)
        print('Я победил!\nВот мои корабли:')
        printField(computer, False)
        break

    # ход человека
    while alive(computer):
        print('Моё поле:')
        printField(computer, True)
        while True:
            str = input('Куда будете стрелять (x, y)? ')
            x, y = str.split()
            x = int(x) - 1
            y = int(y) - 1
            if x >= 0 and y >= 0 and x < N and y < N and not computer.hits[y][x]:
                break
        if shoot(computer, x, y) == Missed:
            print('Моё поле:')
            printField(computer, True)
            break

    if not alive(computer):
        print('Моё поле:')
        printField(computer, False)
        print('Вы выиграли!')
        break
