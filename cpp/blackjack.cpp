#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>

const char pictures[] = "JQK";
const int MAX = 21;

struct Card
{
    int rank;
    char suit;
};

typedef std::vector<Card> Deck;

void deal(Deck &hand, Deck &deck)
{
    std::swap(deck.back(), deck[rand() % deck.size()]);
    hand.push_back(deck.back());
    deck.pop_back();
}

int printDeck(bool is_dealer, const Deck &hand)
{
    if (is_dealer)
    {
        std::cout << "Мои карты: ";
    }
    else
    {
        std::cout << "Ваши карты: ";
    }
    int sum = 0;
    int aces = 0;
    for (auto &card : hand)
    {
        if (card.rank == 1)
        {
            ++aces;
            ++sum;
            std::cout << 'A';
        }
        else if (card.rank <= 10)
        {
            sum += card.rank;
            std::cout << card.rank;
        }
        else
        {
            sum += 10;
            std::cout << pictures[card.rank - 11];
        }
        std::cout << card.suit << " ";
    }
    if (aces > 0 && sum <= MAX - 10)
    {
        sum += 10;
    }
    std::cout << "\nОчки: " << sum << "\n\n";
    return sum;
}

int main()
{
    Deck deck;
    for (int r = 1 ; r <= 13 ; ++r)
    {
        for (char s : {'H', 'D', 'C', 'S'})
        {
            deck.push_back({r, s});
        }
    }

    srand((int)time(NULL));
    Deck dealer, player;
    deal(dealer, deck);
    deal(player, deck);
    deal(player, deck);
    int dealer_sum = printDeck(true, dealer);
    int player_sum = printDeck(false, player);

    while (player_sum < MAX)
    {
        char c;
        std::cout << "Будете брать ещё карту? (Y/N) ";
        std::cin >> c;
        if (c != 'y' && c != 'Y')
        {
            break;
        }
        deal(player, deck);
        player_sum = printDeck(false, player);
    }

    if (player_sum < MAX)
    {
        do
        {
            deal(dealer, deck);
            dealer_sum = printDeck(true, dealer);
        }
        while (dealer_sum <= player_sum);
    }

    std::cout << "У вас " << player_sum << " очков, у меня " << dealer_sum << " очков\n";
    if (player_sum > MAX)
    {
        std::cout << "У вас перебор, вы проиграли!\n";
    }
    else if (dealer_sum > MAX)
    {
        std::cout << "У меня перебор, вы выиграли!\n";
    }
    else if (dealer_sum > player_sum)
    {
        std::cout << "Я выиграл!\n";
    }
    else
    {
        std::cout << "Вы выиграли!\n";
    }
}
