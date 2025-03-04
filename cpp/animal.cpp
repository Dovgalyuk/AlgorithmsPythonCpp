#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<long long, std::string> data = {{1, "Оно умеет плавать?"}, {2, "птица"}, {3, "рыба"}};

bool yesNo(const std::string &question)
{
    while (true)
    {
        std::cout << question << " (д/н) ";
        std::string s;
        std::getline(std::cin, s);
        if (s == "д" || s == "Д")
        {
            return true;
        }
        if (s == "н" || s == "Н")
        {
            return false;
        }
    }
}

int main()
{
    do
    {
        std::cout << "\nЗагадайте животное...\n";
        long long i = 1;
        while (true)
        {
            std::string current = data[i];
            long long no = i * 2;
            long long yes = i * 2 + 1;
            if (current.back() == '?')
            {
                if (yesNo(current))
                {
                    i = yes;
                }
                else
                {
                    i = no;
                }
            }
            else
            {
                if (yesNo("Это " + current + "?"))
                {
                    std::cout << "Ура, я отгадал!\n";
                }
                else
                {
                    std::cout << "Вы победили!\nЧто за животное вы загадали? ";
                    std::string animal;
                    std::getline(std::cin, animal);
                    std::cout << "С помощью какого вопроса можно отличить "
                        << current << " от " << animal << "? ";
                    std::string question;
                    std::getline(std::cin, question);
                    data[i] = question;
                    data[no] = current;
                    data[yes] = animal;
                }
                break;
            }
        }
    }
    while (yesNo("Хотите сыграть ещё?"));
}
