#include <iostream>
#include <time.h>
#include <stdlib.h>

int main()
{
    srand((int)time(NULL));
    int guess;
    int secret = 1 + rand() % 100;

    do
    {
        std::cout << "Введите число: ";
        std::cin >> guess;
        if (secret > guess)
        {
            std::cout << "Загаданное число больше.\n";
        }
        else if (secret < guess)
        {
            std::cout << "Загаданное число меньше.\n";
        }
        else
        {
            std::cout << "Вы выиграли!\n";
        }
    }
    while (secret != guess);
}
