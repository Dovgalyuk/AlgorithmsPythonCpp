#include <string>
#include <iostream>
#include <list>

struct Bulcow {
    std::string guess;
    int bulcow;
};
std::list<Bulcow> guesses;

int countBullsCows(std::string secret, std::string guess)
{
    int bulls = 0;
    int cows = 0;
    for (int i = 0 ; i < 4 ; ++i)
    {
        if (guess[i] == secret[i])
        {
            ++bulls;
        }
        else if (secret.find(guess[i]) != std::string::npos)
        {
            ++cows;
        }
    }
    return bulls * 10 + cows;
}

bool check(std::string s)
{
    for (int i = 0 ; i < 4 ; ++i)
    {
        if (s.find(s[i], i + 1) != std::string::npos)
        {
            return false;
        }
    }
    return true;
}

std::string generate()
{
    for (int v = 100 ; v <= 9999 ; ++v)
    {
        std::string s = std::to_string(v);
        if (v < 1000)
        {
            s = "0" + s;
        }
        if (!check(s))
        {
            continue;
        }
        bool ok = true;
        for (const Bulcow &g : guesses)
        {
            if (countBullsCows(s, g.guess) != g.bulcow)
            {
                ok = false;
            }
        }
        if (ok)
        {
            return s;
        }
    }
    return "9999";
}

int readBullsCows()
{
    while (true)
    {
        int bulls, cows;
        std::cout << "Введите число быков и число коров: ";
        std::cin >> bulls >> cows;
        if (bulls + cows >= 0
            && bulls + cows <= 4
            && bulls >=0 && cows >=0)
        {
            return bulls * 10 + cows;
        }
    }
}

void save(std::string guess, int bulcow)
{
    guesses.push_back({guess, bulcow});
}

int main()
{
    while (true)
    {
        std::string guess = generate();
        std::cout << "Моя попытка: " << guess << "\n";
        int bulcow = readBullsCows();
        if (bulcow == 40)
        {
            std::cout << "Я отгадал!\n";
            break;
        }
        save(guess, bulcow);
    }
}
