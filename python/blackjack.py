#!/usr/bin/python3
import random
from dataclasses import dataclass

@dataclass
class Card:
    rank: int
    suit: int

pictures = 'JQK'
MAX = 21

def deal(hand, deck):
    card = random.randint(0, len(deck) - 1)
    deck[-1], deck[card] = deck[card], deck[-1]
    hand.append(deck[-1])
    deck.pop()

def printDeck(is_dealer, hand):
    if is_dealer:
        print('Мои карты: ', end='')
    else:
        print('Ваши карты: ', end='')
    sum = 0
    aces = 0
    for card in hand:
        if card.rank == 1:
            aces += 1
            sum += 1
            print('A', end='')
        elif card.rank <= 10:
            sum += card.rank
            print(card.rank, end='')
        else:
            sum += 10
            print(pictures[card.rank - 11], end='')
        print(f'{card.suit} ', end='')
    if aces > 0 and sum <= MAX - 10:
        sum += 10
    print(f'\nОчки: {sum}\n')
    return sum

deck = []
for r in range(1, 14):
    for s in 'HDCS':
        deck.append(Card(r, s))

dealer = []
player = []
deal(dealer, deck)
deal(player, deck)
deal(player, deck)
dealer_sum = printDeck(True, dealer)
player_sum = printDeck(False, player)

while player_sum < MAX:
    c = input('Будете брать ещё карту? (Y/N) ')
    if c != 'y' and c != 'Y':
        break
    deal(player, deck)
    player_sum = printDeck(False, player)

if player_sum < MAX:
    deal(dealer, deck)
    dealer_sum = printDeck(True, dealer)
    while dealer_sum <= player_sum:
        deal(dealer, deck)
        dealer_sum = printDeck(True, dealer)

print(f'У вас {player_sum} очков, у меня {dealer_sum} очков\n')
if player_sum > MAX:
    print('У вас перебор, вы проиграли!')
elif dealer_sum > MAX:
    print('У меня перебор, вы выиграли!')
elif dealer_sum > player_sum:
    print('Я выиграл!')
else:
    print('Вы выиграли!')
