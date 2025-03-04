#!/usr/bin/python3
import random

field = [[None] * 3, [None] * 3, [None] * 3]

def checkLine(a, b, c, xo):
  if a is None and b == c == xo:
    return 0
  if b is None and a == c == xo:
    return 1
  if c is None and a == b == xo:
    return 2
  return -1

def tryFinishLine(xo):
  for i in range(3):
    # Проверка i-й горизонтали
    t = checkLine(field[i][0], field[i][1], field[i][2], xo)
    if t >= 0:
      field[i][t] = 'O'
      return True
    # Проверка i-й вертикали
    t = checkLine(field[0][i], field[1][i], field[2][i], xo)
    if t >= 0:
      field[t][i] = 'O'
      return True
  # Проверка одной диагонали
  t = checkLine(field[0][0], field[1][1], field[2][2], xo)
  if t >= 0:
    field[t][t] = 'O'
    return True
  # Проверка другой диагонали
  t = checkLine(field[0][2], field[1][1], field[2][0], xo)
  if t >= 0:
    field[t][2 - t] = 'O'
    return True
  return False

def computerMove():
  # ход в центр
  if field[1][1] is None:
    field[1][1] = 'O'
    return
  # выигрышный ход
  if tryFinishLine('O'):
    return
  # не дать выиграть сопернику
  if tryFinishLine('X'):
    return
  # ход в угол
  if field[0][0] is None:
    field[0][0] = 'O'
    return
  if field[0][2] is None:
    field[0][2] = 'O'
    return
  if field[2][2] is None:
    field[2][2] = 'O'
    return
  if field[2][0] is None:
    field[2][0] = 'O'
    return
  # все остальные ходы
  i = 0
  j = 0
  while field[i][j] is not None:
    i = random.randint(0, 2)
    j = random.randint(0, 2)
  field[i][j] = 'O'

def checkWin():
  for i in range(3):
    if field[i][0] is not None and field[i][0] == field[i][1] == field[i][2]:
      return True
    if field[0][i] is not None and field[0][i] == field[1][i] == field[2][i]:
      return True

  return (field[0][0] is not None and field[0][0] == field[1][1] == field[2][2]) \
    or (field[0][2] is not None and field[0][2] == field[1][1] == field[2][0])

def playerMove():
  i = -1
  j = -1
  while i < 0 or i >= 3 or j < 0 or j >= 3 or field[i][j] is not None:
    move = int(input('Введите ваш ход - номер клетки: '))
    i = (move - 1) // 3
    j = (move - 1) % 3
  field[i][j] = 'X'

def printField():
  for i in range(0, 3):
    for j in range(0, 3):
      cell = field[i][j] or i * 3 + j + 1
      print(f'{cell} ', end='')
    print()
  print()

moves = 0
while True:
  printField()
  if checkWin():
    print('Я выиграл!')
    break
  playerMove()
  moves += 1
  printField()
  if checkWin():
    print('Вы победили!')
    break
  if moves == 9:
    print('Ничья!')
    break
  print('Мой ход:')
  computerMove()
  moves += 1
