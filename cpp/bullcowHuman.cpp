#include <string>
#include <iostream>
#include <time.h>
#include <stdlib.h>

const int LEN = 4;

std::string generate()
{
    std::string res = "0123456789";
    for (int i = 0 ; i < LEN ; ++i)
    {
        int n = i + rand() % (10 - i);
        std::swap(res[i], res[n]);
    }
    res.resize(LEN);
    return res;
}

bool check(std::string s)
{
    for (int i = 0 ; i < LEN ; ++i)
    {
        if (s[i] < '0' || s[i] > '9'
            || s.find(s[i], i + 1) != std::string::npos)
        {
            return false;
        }
    }
    return true;
}

std::string inputGuess()
{
    std::string s;
    while (true)
    {
        std::cout << "Введите последовательность из 4 цифр: ";
        std::cin >> s;
        if (s.size() == LEN && check(s))
        {
            return s;
        }
    }
}

void countBullsAndCows(const std::string &secret, const std::string &guess)
{
    int bulls = 0;
    int cows = 0;
    for (int i = 0 ; i < LEN ; ++i)
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
    std::cout << "Быки: " << bulls << " Коровы: " << cows << "\n";
}

int main()
{
    srand((int)time(NULL));
    std::string secret = generate();
    std::string guess;
    while (true)
    {
        guess = inputGuess();
        if (guess == secret)
        {
            std::cout << "Вы выиграли!\n";
            break;
        }
        countBullsAndCows(secret, guess);
    }
}
