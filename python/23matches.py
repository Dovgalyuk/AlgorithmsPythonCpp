#!/usr/bin/python3
matches = 23
print(f'На столе лежит {matches} спичек.')
while matches > 0:
  move = 0
  while move < 1 or move > matches or move > 3:
    move = int(input('Сколько спичек вы возьмёте? '))
  matches -= move
  print(f'Вы взяли {move}, осталось {matches} спичек')
  if matches == 0:
    print('Последняя спичка ваша, я выиграл!')
    break
  move = (matches - 1) % 4
  if move == 0:
    move = 1
  matches -= move
  print(f'Я беру {move}, осталось {matches} спичек.')
  if matches == 0:
    print('Сегодня вам удалось победить. Посмотрим, что будет в следующий раз!')
    break
