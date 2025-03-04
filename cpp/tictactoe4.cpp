#include <iostream>

const int N = 4;
char field[N][N];

void playerMove()
{
    int x, y;
    do
    {
        std::cout << "Куда будете ходить? ";
        char c;
        std::cin >> c;
        x = c - 'a';
        std::cin >> c;
        y = c - '1';
    }
    while (x < 0 || x >= N || y < 0 || y >= N || field[y][x]);
    field[y][x] = 'X';
}

bool checkLines()
{
    bool found;
    for (int i = 0 ; i < N ; ++i)
    {
        found = field[i][0] != 0;
        for (int j = 1 ; found && j < N ; ++j)
        {
            found = field[i][j] == field[i][0];
        }
        if (found)
        {
            return true;
        }
        found = field[0][i] != 0;
        for (int j = 1 ; found && j < N ; ++j)
        {
            found = field[j][i] == field[0][i];
        }
        if (found)
        {
            return true;
        }
    }
    found = field[0][0] != 0;
    for (int j = 1 ; found && j < N ; ++j)
    {
        found = field[j][j] == field[0][0];
    }
    return found;
}

bool canWin(bool player)
{
    if (checkLines())
    {
        return false;
    }
    for (int x = 0 ; x < N ; ++x)
    {
        for (int y = 0 ; y < N ; ++y)
        {
            if (!field[y][x])
            {
                field[y][x] = player ? 'X' : 'O';
                bool w = canWin(!player);
                field[y][x] = 0;
                if (!player && w)
                {
                    return true;
                }
                if (player && !w)
                {
                    return false;
                }
            }
        }
    }
    return player;
}

void computerMove()
{
    for (int x = 0 ; x < N ; ++x)
    {
        for (int y = 0 ; y < N ; ++y)
        {
            if (!field[y][x])
            {
                field[y][x] = 'O';
                if (canWin(true))
                {
                    return;
                }
                field[y][x] = 0;
            }
        }
    }
    int x, y;
    do
    {
        y = rand() % N;
        x = rand() % N;
    }
    while (field[y][x]);
    field[y][x] = 'O';
}

void printField()
{
    std::cout << ' ';
    for (int j = 0 ; j < N ; ++j)
    {
        std::cout << ' ' << (char)('a' + j);
    }
    std::cout << '\n';
    for (int i = 0 ; i < N ; ++i)
    {
        std::cout << i + 1;
        for (int j = 0 ; j < N ; ++j)
        {
            if (field[i][j])
            {
                std::cout << ' ' << field[i][j];
            }
            else
            {
                std::cout << " .";
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main()
{
    srand((int)time(NULL));

    int moves = 0;
    while (true)
    {
        printField();
        if (checkLines())
        {
            std::cout << "Вы выиграли!\n";
            break;
        }
        if (moves == N * N)
        {
            std::cout << "Я победил!\n";
            break;
        }
        playerMove();
        ++moves;
        printField();
        if (checkLines())
        {
            std::cout << "Вы выиграли!\n";
            break;
        }
        std::cout << "Мой ход:\n";
        computerMove();
        ++moves;
    }
}
