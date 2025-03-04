#!/usr/bin/python3
def inputPos():
    s = ''
    while len(s) != 2 or s[0] < 'a' or s[0] > 'h' or s[1] < '1' or s[1] > '8':
        s = input()
    return int(s[0], 18) - 9, int(s[1])

def printField(x, y):
    for i in range(8, 0, -1):
        s = '.' * 8
        if i == y:
            s = s[:x - 1] + 'Q' + s[x:]
        print(f'{i} {s}')
    print('  abcdefgh')

def checkMove(x, y, qx, qy):
    if x > qx or y > qy or (x == qx and y == qy):
        return None
    if x == qx or y == qy or y - qy == x - qx:
        return x, y
    return None

print('Игра "Ферзя в угол"')
printField(0, 0)
x = 0
y = 0
while x != 8 and y != 8:
    print('Выберите начальное положение (a8-g8, h1-h8): ', end='')
    x, y = inputPos()

while True:
    t = checkMove(1, 1, x, y) or checkMove(2, 3, x, y) \
        or checkMove(3, 2, x, y) or checkMove(6, 4, x, y) \
        or checkMove(4, 6, x, y)
    if t is not None:
        x, y = t
    else:
        if x > 1:
            x -= 1
        else:
            y -= 1
    print(f'Мой ход {chr(ord("a") + x - 1)}{y}')
    printField(x, y)
    if x == 1 and y == 1:
        print('Вы проиграли!')
        break
    while True:
        print('Куда вы будете ходить? ', end='')
        x1, y1 = inputPos()
        dx = x1 - x
        dy = y1 - y
        if (dx < 0 and dy == 0) \
            or (dy < 0 and dx == 0) \
            or (dx < 0 and dx == dy):
            break
    x = x1
    y = y1
    printField(x, y)
    if x == 1 and y == 1:
        print('Вы выиграли, поздравляю!')
        break
