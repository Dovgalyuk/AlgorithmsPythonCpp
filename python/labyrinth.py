#!/usr/bin/python3
import queue
from dataclasses import dataclass

@dataclass
class Pos:
    x: int
    y: int

maze = []
prev = []

dir = [Pos(-1, 0), Pos(1, 0), Pos(0, -1), Pos(0, 1)]

def inputMaze():
    print('Введите лабиринт со стартовой клеткой S и финишной E.')
    while True:
        s = input()
        if len(s) == 0:
            break
        maze.append(list(s))

def findChar(c):
    for y in range(len(maze)):
        for x in range(len(maze[y])):
            if maze[y][x] == c:
                return Pos(x, y)
    return Pos(-1, -1)

def findPath():
    for y in range(len(maze)):
        prev.append([Pos(-1, -1)] * len(maze[y]))
    start = findChar('S')
    prev[start.y][start.x] = start

    q = queue.Queue()
    q.put(start)

    while not q.empty():
        cur = q.get()
        for d in dir:
            x = cur.x + d.x
            y = cur.y + d.y
            if prev[y][x].x < 0 and maze[y][x] != '#':
                prev[y][x] = cur
                q.put(Pos(x, y))

def outputPath():
    end = findChar('E')
    if end.x < 0 or prev[end.y][end.x].x < 0:
        print('Пути между S и E не существует.')
        return

    while prev[end.y][end.x].x != end.x or prev[end.y][end.x].y != end.y:
        end = prev[end.y][end.x]
        maze[end.y][end.x] = '*'
    maze[end.y][end.x] = 'S'
    print('Кратчайший путь:')
    for s in maze:
        print("".join(s))

inputMaze()
findPath()
outputPath()
