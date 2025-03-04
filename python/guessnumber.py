#!/usr/bin/python3
import random

secret = random.randint(1, 100)
guess = 0
while True:
    guess = int(input("Введите число: "))
    if secret > guess:
        print("Загаданное число больше.")
    elif secret < guess:
        print("Загаданное число меньше.")
    else:
        print("Вы выиграли!")
