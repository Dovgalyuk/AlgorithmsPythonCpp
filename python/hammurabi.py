#!/usr/bin/python3
import random
import sys

def quit():
    print('\n\n\nДо встречи.\n')
    sys.exit()

def printNotEnoughGrain():
    print(f'Подумайте ещё. У вас всего {grain} бушелей зерна.')

def printNotEnoughLand():
    print(f'Подумайте ещё, у вас есть только {land} акров земли.')

def endGameBad():
    print('Ваше правление было ужасным,\n'
        'вас объявили национальным предателем и изгнали из резиденции!!!')
    quit()

def tradeLand():
    global land, grain
    cost = random.randint(17, 27)
    print(f'Стоимость земли сейчас составляет {cost} бушелей за акр.')
    buysell = 0
    while True:
        buysell = int(input('Сколько акров вы хотите купить/продать? '))
        if buysell < 0 and -buysell > land:
            printNotEnoughLand()
            continue
        if buysell > 0 and cost * buysell > grain:
            printNotEnoughGrain()
            continue
        break
    land = land + buysell
    grain = grain - cost * buysell

def feedPeople():
    global food, grain
    print('')
    while True:
        food = int(input('Сколько бушелей зерна вы потратите, чтобы накормить людей? '))
        if food < 0:
            continue
        if food <= grain:
            break
        printNotEnoughGrain()
    grain = grain - food

def plantSeeds():
    global grain, harvest, harvest_total
    print('')
    plant = 0
    while True:
        plant = int(input('Сколько акров земли вы хотите засеять? '))
        if plant < 0:
            continue
        if plant > land:
            printNotEnoughLand()
            continue
        if plant / 2 > grain:
            printNotEnoughGrain()
            continue
        if plant > 10 * population:
            print(f'Но у вас только {population} человек для работы на полях!')
            continue
        break
    grain = grain - plant // 2
    harvest = random.randint(1, 6)
    harvest_total = plant * harvest

def ratsInvasion():
    global rats, grain
    rats = 0
    c = random.randint(1, 6)
    if c % 2 == 0:
        rats = grain // c
    grain -= rats

def harvestGrain():
    global grain
    grain = grain + harvest_total

def changePopulation():
    global people_came, population, starved, percent_died, died_total
    people_came = random.randint(1, 6) * (20 * land + grain) // population // 100 + 1
    starved = population - food // 20
    if starved <= 0:
        starved = 0
    else:
        if starved > 0.45 * population:
            print(f'\nЗа год от голода умерло {starved} человек!!!')
            endGameBad()
        percent_died = ((year - 1) * percent_died + starved * 100 // population) // year
        population = population - starved
        died_total = died_total + starved
    population = population + people_came

def plague():
    global year, population
    if year > 1 and random.randint(0, 99) < 15:
        population -= population // 2
        print('\nЭпидемия чумы! Половина населения умерла.')

def report():
    print('\nХаммурапи, сообщаю Вам,')
    print(f'в прошлом {year} году, {starved} людей умерли от голода, '
        f'{people_came} человек прибыли в город.')
    print(f'Всего в городе живёт {population} человек.')
    print(f'Город владеет {land} акрами земли.')
    print(f'Вы собрали {harvest} бушелей зерна с акра.')
    print(f'Крысы съели {rats} бушелей зерна.')
    print(f'Сейчас у вас {grain} бушелей в хранилище.\n')

def final():
    print(f'За прошедшие десять лет в среднем {percent_died} процентов')
    print('населения в год умирало от голода. Всего умерло '
        f'{died_total} человек!!')
    L = land // population
    print('В начале правления у вас было 10 акров земли на человека,')
    print(f'а в конце стало {L} акров на человека.\n')
    if percent_died > 33 or L < 7:
        endGameBad()
    elif percent_died > 10 or L < 9:
        print('Своим жёстким руководством вы переплюнули Ивана Грозного.')
        print('Оставшиеся люди будут долго ненавидеть вас!!')
    elif percent_died > 3 or L < 10:
        print('Ваше правление было не самым плохим.')
        print(f'Хотя {random.randint(0, int(population * 0.8))} человек')
        print('предпочли бы, чтобы Ваша жизнь закончилась в результате покушения.')
    else:
        print('Фантастический результат!!! Даже Карл Великий и')
        print('Пётр Первый не смогли бы лучше!')

print('\t\t\t\tХАММУРАПИ')
print('\n\n\nПопробуйте управлять древним шумерским государством')
print('в течение десяти лет.\n')

year = 0
starved = 0
population = 100
rats = 200
harvest_total = 3000
grain = harvest_total - rats
harvest = 3
land = harvest_total // harvest
people_came = 5
percent_died = 0
died_total = 0
while True:
    year = year + 1
    plague()
    report()
    if year == 11:
        break
    tradeLand()
    feedPeople()
    plantSeeds()
    ratsInvasion()
    harvestGrain()
    changePopulation()
final()
quit()
