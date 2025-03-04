#include <iostream>

const char EMPTY = '.';
const char BLACK = '#';
const char WHITE = 'O';

const int N = 8;

char board[N][N];

int cost[N][N] = {
    {10, 1, 5, 5, 5, 5, 1, 10},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {5, 1, 3, 3, 3, 3, 1, 5},
    {5, 1, 3, 3, 3, 3, 1, 5},
    {5, 1, 3, 3, 3, 3, 1, 5},
    {5, 1, 3, 3, 3, 3, 1, 5},
    {1, 1, 1, 1, 1, 1, 1, 1},
    {10, 1, 5, 5, 5, 5, 1, 10},
};

int count(char player)
{
    int res = 0;
    for (int i = 0 ; i < N ; ++i)
    {
        for (int j = 0 ; j < N ; ++j)
        {
            if (board[i][j] == player)
            {
                ++res;
            }
        }
    }
    return res;
}

void printBoard()
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
            std::cout << ' ' << board[i][j];
        }
        std::cout << '\n';
    }
    std::cout << "У вас " << count(WHITE) << " фишек, у меня " << count(BLACK) << " фишек\n\n";
}

int checkDir(char player, int x, int y, int dx, int dy)
{
    int res = 0;
    int xx = x + dx;
    int yy = y + dy;
    while (xx >= 0 && xx < N && yy >= 0 && yy < N)
    {
        if (board[yy][xx] == player)
        {
            return res;
        }
        else if (board[yy][xx] == EMPTY)
        {
            return 0;
        }
        ++res;
        xx += dx;
        yy += dy;
    }
    return 0;
}

int checkMove(char player, int x, int y)
{
    if (x < 0 || x >= N || y < 0 || y >= N || board[y][x] != EMPTY)
    {
        return 0;
    }
    int res = 0;
    for (int dx = -1 ; dx <= 1 ; ++dx)
    {
        for (int dy = -1 ; dy <= 1 ; ++dy)
        {
            if (!dx && !dy)
            {
                continue;
            }
            res += checkDir(player, x, y, dx, dy);
        }
    }
    return res;
}

void swapDir(char player, int x, int y, int dx, int dy)
{
    x += dx;
    y += dy;
    while (board[y][x] != player)
    {
        board[y][x] = player;
        x += dx;
        y += dy;
    }
}

void makeMove(char player, int x, int y)
{
    board[y][x] = player;
    for (int dx = -1 ; dx <= 1 ; ++dx)
    {
        for (int dy = -1 ; dy <= 1 ; ++dy)
        {
            if (!dx && !dy)
            {
                continue;
            }
            if (checkDir(player, x, y, dx, dy))
            {
                swapDir(player, x, y, dx, dy);
            }
        }
    }
}

bool hasMove(char player)
{
    for (int i = 0 ; i < N ; ++i)
    {
        for (int j = 0 ; j < N ; ++j)
        {
            if (checkMove(player, j, i))
            {
                return true;
            }
        }
    }
    return false;
}

int main()
{
    for (int i = 0 ; i < N ; ++i)
    {
        for (int j = 0 ; j < N ; ++j)
        {
            board[i][j] = EMPTY;
        }
    }
    board[N / 2 - 1][N / 2 - 1] = WHITE;
    board[N / 2][N / 2] = WHITE;
    board[N / 2][N / 2 - 1] = BLACK;
    board[N / 2 - 1][N / 2] = BLACK;

    while (hasMove(WHITE) || hasMove(BLACK))
    {
        int x, y;
        // ход игрока
        printBoard();
        if (!hasMove(WHITE))
        {
            std::cout << "Вам некуда ходить\n";
        }
        else
        {
            do
            {
                std::cout << "Куда будете ходить? ";
                char c;
                std::cin >> c;
                x = c - 'a';
                std::cin >> c;
                y = c - '1';
            }
            while (!checkMove(WHITE, x, y));
            makeMove(WHITE, x, y);
        }
        // ход компьютера
        printBoard();
        int best = 0;
        for (int i = 0 ; i < N ; ++i)
        {
            for (int j = 0 ; j < N ; ++j)
            {
                int c = checkMove(BLACK, j, i) * cost[i][j];
                if (c > best)
                {
                    x = j;
                    y = i;
                    best = c;
                }
            }
        }
        if (best > 0)
        {
            std::cout << "Мой ход " << (char)('a' + x) << y + 1 << "\n";
            makeMove(BLACK, x, y);
        }
        else
        {
            std::cout << "Мне некуда ходить\n";
        }
    }
    std::cout << "Игра окончена\n";
    printBoard();
    int white = count(WHITE);
    int black = count(BLACK);
    if (white > black)
    {
        std::cout << "Вы победили!\n";
    }
    else if (black > white)
    {
        std::cout << "Я выиграл!\n";
    }
    else
    {
        std::cout << "Ничья\n";
    }
}
