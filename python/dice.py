#!/usr/bin/python3
import random

guess = int(input('Сделайте ставку: '))
dice = random.randint(1, 6)

if guess == dice:
    print('Вы выиграли!')
else:
    print(f'Вы проиграли! Выпало число {dice}')
