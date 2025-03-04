#!/usr/bin/python3
import queue

N = 7
positions = {}
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]

moves = []

def hasPeg(f, x, y):
    return f & (1 << (y * N + x)) != 0

def printField(f):
    for y in range(N):
        for x in range(N):
            if hasPeg(f, x, y):
                print('o', end='')
            else:
                print('.', end='')
        print()
    print()

def printSolution(f):
    next = positions[f]
    if next:
        printSolution(next)
    printField(f)

def readField():
    field = []
    for i in range(N):
        while True:
            s = input()
            if len(s) == N:
                break
        field.append(s)
    res = 0
    for i in range(N):
        for j in range(N):
            index = i * N + j
            if field[i][j] == 'o':
                res |= 1 << index
            m = []
            if field[i][j] != 'X':
                for d in range(4):
                    x = j + dx[d] * 2
                    y = i + dy[d] * 2
                    if x >= 0 and x < N and y >= 0 and y < N and field[y][x] != 'X':
                        m.append(d)
            moves.append(m)
    return res

start = readField()

q = queue.Queue()
q.put(start)
positions[start] = 0
while not q.empty():
    last = q.get()
    for i in range(N):
        for j in range(N):
            if not hasPeg(last, j, i):
                continue
            for d in moves[i * N + j]:
                x = j + dx[d] * 2
                y = i + dy[d] * 2
                mx = j + dx[d]
                my = i + dy[d]
                if hasPeg(last, x, y) or not hasPeg(last, mx, my):
                    continue
                next = last
                next ^= 1 << (i * N + j)
                next ^= 1 << (y * N + x)
                next ^= 1 << (my * N + mx)
                if next not in positions:
                    positions[next] = last
                    q.put(next)

print()
printSolution(last)
