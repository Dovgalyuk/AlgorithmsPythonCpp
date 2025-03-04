#include <iostream>
#include <time.h>
#include <stdlib.h>

int main()
{
    srand((int)time(NULL));
    int guess;
    std::cout << "Сделайте ставку: ";
    std::cin >> guess;

    int dice = 1 + rand() % 6;
    if (dice == guess)
    {
        std::cout << "Вы выиграли!\n";
    }
    else
    {
        std::cout << "Вы проиграли! "
            << "Выпало число " << dice << "\n";
    }
}
