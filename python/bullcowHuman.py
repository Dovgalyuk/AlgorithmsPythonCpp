#!/usr/bin/python3
import random

LEN = 4

def generate():
    return ''.join(random.sample('0123456789', LEN))

def check(s):
    for i in range(LEN):
        if s.find(s[i], i + 1) != -1:
            return False
    return True

def inputGuess():
    while True:
        s = input('Введите последовательность из 4 цифр: ')
        if len(s) == LEN and s.isdigit() and check(s):
            return s

def countBullsAndCows(secret, guess):
    bulls = 0
    cows = 0
    for i in range(LEN):
        if secret[i] == guess[i]:
            bulls += 1
        elif secret.find(guess[i]) != -1:
            cows += 1
    print(f'Быки: {bulls} Коровы: {cows}')

secret = generate()
while True:
    guess = inputGuess()
    if secret == guess:
        print('Вы выиграли!')
        break
    countBullsAndCows(secret, guess)
