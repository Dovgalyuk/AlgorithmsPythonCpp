#include <iostream>
#include <cmath>

const int M = 4;
const int S = 10;
const int G = 10;
struct Pos { int x, y; };
Pos m[M];
bool caught[M];

void placeMonsters()
{
    for (int i = 0 ; i < M ; ++i)
    {
        bool again = true;
        while (again)
        {
            m[i].x = rand() % S;
            m[i].y = rand() % S;
            again = false;
            for (int j = 0 ; j < i ; ++j)
            {
                if (m[i].x == m[j].x && m[i].y == m[j].y)
                {
                    again = true;
                }
            }
        }
    }
}

void printMonsters()
{
    std::cout << "Монстры:\n";
    for (int i = 0 ; i < M ; ++i)
    {
        std::cout << i << ": ";
        if (caught[i])
        {
            std::cout << "пойман\n";
        }
        else
        {
            std::cout << m[i].x << " " << m[i].y << "\n";
        }
    }
}

Pos inputMove()
{
    int x, y;
    do
    {
        std::cout << "Введите координаты: ";
        std::cin >> x >> y;
    }
    while (x < 0 || x >= S
        || y < 0 || y >= S);
    return Pos{x, y};
}

void checkDistance(Pos pos)
{
    for (int i = 0 ; i < M ; ++i)
    {
        if (caught[i])
        {
            continue;
        }
        std::cout << "Монстр " << i + 1;
        if (pos.x == m[i].x && pos.y == m[i].y)
        {
            caught[i] = true;
            std::cout << " пойман!\n";
        }
        else
        {
            int dx = pos.x - m[i].x;
            int dy = pos.y - m[i].y;
            double dist = std::sqrt(dx * dx + dy * dy);
            std::cout << " на расстоянии " << dist << "\n";
        }
    }
}

bool allCaught()
{
    for (int i = 0 ; i < M ; ++i)
    {
        if (!caught[i])
        {
            return false;
        }
    }
    return true;
}

void finalMessage(int move)
{
    if (move <= G)
    {
        std::cout << "Поздравляем, вы поймали всех монстров за " << move << " ходов!\n";
    }
    else
    {
        std::cout << "Вы проиграли, можете попробовать снова.\n";
    }
}

int main()
{
    srand((int)time(NULL));

    int move;
    placeMonsters();
    for (move = 1 ; move <= G ; ++move)
    {
        std::cout << "Ход " << move << "\n";
        //printMonsters();
        checkDistance(inputMove());
        if (allCaught())
        {
            break;
        }
    }
    finalMessage(move);
}
