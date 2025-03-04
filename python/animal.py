#!/usr/bin/python3

data = {1: 'Оно умеет плавать?', 2: 'птица', 3: 'рыба'}

def yesNo(question):
    while True:
        s = input(f'{question} (д/н) ')
        if s == 'д' or s == 'Д':
            return True
        if s == 'н' or s == 'Н':
            return False

while True:
    print('\nЗагадайте животное...')
    i = 1
    while True:
        current = data[i]
        no = i * 2
        yes = i * 2 + 1
        if current[-1] == '?':
            if yesNo(current):
                i = yes
            else:
                i = no
        else:
            if yesNo(f'Это {current}?'):
                print('Ура, я отгадал!')
            else:
                animal = input('Вы победили!\nЧто за животное вы загадали? ')
                question = input(f'С помощью какого вопроса можно отличить {current} от {animal}? ')
                data[i] = question
                data[no] = current
                data[yes] = animal
            break
    if not yesNo('Хотите сыграть ещё?'):
        break
