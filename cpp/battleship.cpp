#include <iostream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>

const int N = 10;
const int S = 10;
const int shipLen[S] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

enum Shoot
{
    Missed,
    Hit,
    Sunk,
};

struct Player
{
    int field[N][N] = {};
    bool hits[N][N] = {};
    int ships[S] = {};
};

bool alive(const Player &pl)
{
    for (auto s : pl.ships)
    {
        if (s)
        {
            return true;
        }
    }
    return false;
}

void printField(const Player &pl, bool hide)
{
    std::cout << "  ";
    for (int j = 0 ; j < N ; ++j)
    {
        std::cout << ' ' << j + 1;
    }
    std::cout << '\n';
    for (int i = 0 ; i < N ; ++i)
    {
        std::cout << std::setw(2) << i + 1;
        for (int j = 0 ; j < N ; ++j)
        {
            std::cout << ' ';
            if (pl.hits[i][j])
            {
                if (pl.field[i][j])
                {
                    std::cout << '*';
                }
                else
                {
                    std::cout << 'x';
                }
            }
            else if (!hide && pl.field[i][j])
            {
                std::cout << 'O';
            }
            else
            {
                std::cout << '.';
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

bool checkShip(const Player &pl, int x, int y, int len, bool v)
{
    if (x < 0 || y < 0)
    {
        return false;
    }
    int endx = v ? x : x + len - 1;
    int endy = v ? y + len - 1 : y;
    if (endx >= N || endy >= N)
    {
        return false;
    }
    for (int i = -1 ; i <= len ; ++i)
    {
        for (int j = -1 ; j <= 1 ; ++j)
        {
            int xx = v ? x + j : x + i;
            int yy = v ? y + i : y + j;
            if (xx >= 0 && xx < N && yy >= 0 && yy < N)
            {
                if (pl.field[yy][xx])
                {
                    return false;
                }
            }
        }
    }
    return true;
}

void placeShip(Player &pl, int x, int y, int type, bool v)
{
    int len = shipLen[type];
    for (int i = 0 ; i < len ; ++i)
    {
        int xx = v ? x : x + i;
        int yy = v ? y + i : y;
        pl.field[yy][xx] = type + 1;
    }
    pl.ships[type] = len;
}

Shoot shoot(Player &pl, int x, int y)
{
    if (!pl.hits[y][x])
    {
        pl.hits[y][x] = true;
        if (pl.field[y][x])
        {
            if (!--pl.ships[pl.field[y][x] - 1])
            {
                std::cout << "Убит!\n";

                for (int i = 0 ; i < N ; ++i)
                {
                    for (int j = 0 ; j < N ; ++j)
                    {
                        if (pl.field[i][j] == pl.field[y][x])
                        {
                            for (int ii = i - 1 ; ii <= i + 1 ; ++ii)
                            {
                                for (int jj = j - 1 ; jj <= j + 1 ; ++jj)
                                {
                                    if (ii >= 0 && ii < N && jj >= 0 && jj < N)
                                    {
                                        pl.hits[ii][jj] = true;
                                    }
                                }
                            }
                        }
                    }
                }
                return Sunk;
            }
            else
            {
                std::cout << "Ранен!\n";
                return Hit;
            }
        }
        else
        {
            std::cout << "Мимо!\n";
        }
    }
    return Missed;
}

int main()
{
    srand((int)time(NULL));

    Player player, computer;
    int shipX = -1, shipY;
    // расстановка кораблей игрока
    for (int s = 0 ; s < S ; ++s)
    {
        printField(player, false);
        int x, y;
        char c;
        bool v;
        do
        {
            std::cout << "Введите позицию для корабля " << s + 1
                << " (" << shipLen[s] << "-палубный) (x, y"
                << (shipLen[s] > 1 ? ", v" : "")
                << "): ";
            std::cin >> x >> y;
            if (shipLen[s] > 1)
            {
                std::cin >> c;
            }
            --x;
            --y;
            v = c == 'v' || c == 'V';
        }
        while (!checkShip(player, x, y, shipLen[s], v));
        placeShip(player, x, y, s, v);
    }
    // расстановка кораблей компьютера
    for (int s = 0 ; s < S ; ++s)
    {
        int x, y;
        bool v;
        do
        {
            x = rand() % N;
            y = rand() % N;
            v = rand() % 2;
        }
        while (!checkShip(computer, x, y, shipLen[s], v));
        placeShip(computer, x, y, s, v);
    }
    while (true)
    {
        int x, y;
        // ход компьютера
        while (alive(player))
        {
            std::cout << "Ваше поле:\n";
            printField(player, false);
            if (shipX == -1)
            {
                int len = 0;
                for (int i = 0 ; !len && i < S ; ++i)
                {
                    if (player.ships[i])
                    {
                        len = shipLen[i];
                    }
                }
                do
                {
                    x = rand() % N;
                    y = rand() % N;
                }
                while (player.hits[y][x] || (x + y) % len != 0);
            }
            else
            {
                x = -1;
                for (int j = shipX - 1 ; j >= 0 ; --j)
                {
                    if (!player.hits[shipY][j])
                    {
                        x = j;
                        y = shipY;
                        break;
                    }
                    else if (!player.field[shipY][j])
                    {
                        break;
                    }
                }
                if (x < 0)
                {
                    for (int j = shipX + 1 ; j < N ; ++j)
                    {
                        if (!player.hits[shipY][j])
                        {
                            x = j;
                            y = shipY;
                            break;
                        }
                        else if (!player.field[shipY][j])
                        {
                            break;
                        }
                    }
                }
                if (x < 0)
                {
                    for (int i = shipY - 1 ; i >= 0 ; --i)
                    {
                        if (!player.hits[i][shipX])
                        {
                            x = shipX;
                            y = i;
                            break;
                        }
                        else if (!player.field[i][shipX])
                        {
                            break;
                        }
                    }
                }
                if (x < 0)
                {
                    for (int i = shipY + 1 ; i < N ; ++i)
                    {
                        if (!player.hits[i][shipX])
                        {
                            x = shipX;
                            y = i;
                            break;
                        }
                        else if (!player.field[i][shipX])
                        {
                            break;
                        }
                    }
                }
            }
            std::cout << "Мой ход: " << x + 1 << ", " << y + 1 << "\n";
            Shoot s = shoot(player, x, y);
            if (s == Hit && shipX < 0)
            {
                shipX = x;
                shipY = y;
            }
            else if (s == Sunk)
            {
                shipX = -1;
            }
            else if (s == Missed)
            {
                std::cout << "Ваше поле:\n";
                printField(player, false);
                break;
            }
        }
        if (!alive(player))
        {
            std::cout << "Ваше поле:\n";
            printField(player, false);
            std::cout << "Я победил!\nВот мои корабли:\n";
            printField(computer, false);
            break;
        }
        // ход человека
        while (alive(computer))
        {
            std::cout << "Моё поле:\n";
            printField(computer, true);
            do
            {
                std::cout << "Куда будете стрелять (x, y)? ";
                std::cin >> x >> y;
                --x;
                --y;
            }
            while (x < 0 || y < 0 || x >= N || y >= N || computer.hits[y][x]);
            if (shoot(computer, x, y) == Missed)
            {
                std::cout << "Моё поле:\n";
                printField(computer, true);
                break;
            }
        }
        if (!alive(computer))
        {
            std::cout << "Моё поле:\n";
            printField(computer, false);
            std::cout << "Вы выиграли!\n";
            break;
        }
    }
}
