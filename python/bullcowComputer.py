#!/usr/bin/python3
import sys

guesses = []

def countBullsCows(secret, guess):
    bulls = 0
    cows = 0
    for i in range(4):
        if secret[i] == guess[i]:
            bulls += 1
        elif secret.find(guess[i]) != -1:
            cows += 1
    return bulls * 10 + cows

def generate():
    for v in range(100, 10000):
        s = f'{v:04d}'
        ok = True
        for i in range(4):
            if s.find(s[i], i + 1) != -1:
                ok = False
        for g in guesses:
            if countBullsCows(s, g['guess']) \
                != g['bulcow']:
                ok = False
        if ok:
            return s
    return "9999"

def readBullsCows():
    while True:
        bulls, cows = [int(x)
            for x in input('Введите число быков и число коров: ').split()]
        if bulls + cows >= 0 \
            and bulls + cows <= 4 \
            and bulls >=0 and cows >=0:
            return bulls * 10 + cows

def save(guess, bulcow):
    guesses.append({'guess': guess, 'bulcow': bulcow})

while True:
    guess = generate()
    print(f'Моя попытка: {guess}')
    bulcow = readBullsCows()
    if bulcow == 40:
        print('Я отгадал!')
        break
    save(guess, bulcow)
