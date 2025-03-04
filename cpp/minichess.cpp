#include <iostream>
#include <string>
#include <cctype>
#include <array>

const int N = 5;
const int KING = 1000;
const int END = KING / 2;
const int MAX = KING * 2;

typedef std::array<std::string, N> Board;

Board board = {
    "RNBQK",
    "PPPPP",
    ".....",
    "ppppp",
    "rnbqk"
};

void printBoard()
{
    std::cout << "  abcde\n";
    for (int i = N - 1 ; i >= 0 ; --i)
    {
        std::cout << i + 1 << " " << board[i] << "\n";
    }
    std::cout << "\n";
}

bool isOwnFigure(int player, char f)
{
    if (player == 0 && std::isupper(f))
    {
        return true;
    }
    if (player == 1 && std::islower(f))
    {
        return true;
    }
    return false;
}

bool isFreeWay(const Board &board, int c1, int r1, int c2, int r2)
{
    int dx = c2 - c1;
    if (dx != 0)
    {
        dx /= std::abs(dx);
    }
    int dy = r2 - r1;
    if (dy != 0)
    {
        dy /= std::abs(dy);
    }
    c1 += dx;
    r1 += dy;
    while (c1 != c2 || r1 != r2)
    {
        if (board[r1][c1] != '.')
        {
            return false;
        }
        c1 += dx;
        r1 += dy;
    }
    return true;
}

bool isValidMove(const Board &board, int player, int c1, int r1, int c2, int r2)
{
    if (c1 < 0 || c1 >= N || r1 < 0 || r1 >= N
        || c2 < 0 || c2 >= N || r2 < 0 || r2 >= N)
    {
        return false;
    }
    if (c1 == c2 && r1 == r2)
    {
        return false;
    }
    char f = board[r1][c1];
    if (f == '.')
    {
        return false;
    }
    char t = board[r2][c2];
    if (!isOwnFigure(player, f) || isOwnFigure(player, t))
    {
        return false;
    }
    if (f == 'P' || f == 'p')
    {
        int dy = f == 'P' ? 1 : -1;
        if (r1 + dy != r2)
        {
            return false;
        }
        if (c1 == c2)
        {
            return t == '.';
        }
        if (c1 + 1 == c2 || c1 - 1 == c2)
        {
            return isOwnFigure(1 - player, t);
        }
        return false;
    }
    f = std::toupper(f);
    int dx = std::abs(c2 - c1);
    int dy = std::abs(r2 - r1);
    if (f == 'K')
    {
        return dx <= 1 && dy <= 1;
    }
    if (f == 'N')
    {
        return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
    }
    if (f == 'R')
    {
        if (dx && dy)
        {
            return false;
        }
        return isFreeWay(board, c1, r1, c2, r2);
    }
    if (f == 'B')
    {
        if (dx != dy)
        {
            return false;
        }
        return isFreeWay(board, c1, r1, c2, r2);
    }
    if (f == 'Q')
    {
        if (dx != dy && dx && dy)
        {
            return false;
        }
        return isFreeWay(board, c1, r1, c2, r2);
    }
    return false;
}

int makeMove(Board &board, int c1, int r1, int c2, int r2)
{
    char f = board[r1][c1];
    char t = std::toupper(board[r2][c2]);
    board[r1][c1] = '.';
    board[r2][c2] = f;
    switch (t)
    {
    case 'P':
        return 1;
    case 'R':
        return 5;
    case 'N':
        return 3;
    case 'B':
        return 3;
    case 'Q':
        return 9;
    case 'K':
        return KING;
    }
    return 0;
}

int playerMove()
{
    char c1, r1, c2, r2;
    do
    {
        std::cout << "Введите ваш ход: ";
        std::cin >> c1 >> r1 >> c2 >> r2;
        c1 -= 'a';
        r1 -= '1';
        c2 -= 'a';
        r2 -= '1';
    }
    while (!isValidMove(board, 0, c1, r1, c2, r2));
    return makeMove(board, c1, r1, c2, r2);
}

int checkMove(const Board &board, int player, int depth, int score, int alpha, int beta)
{
    if (depth == 0 || std::abs(score) >= END)
    {
        return score;
    }
    int res = player == 0 ? MAX : -MAX;
    for (int c1 = 0 ; c1 < N ; ++c1)
    {
        for (int r1 = 0 ; r1 < N ; ++r1)
        {
            for (int c2 = 0 ; c2 < N ; ++c2)
            {
                for (int r2 = 0 ; r2 < N ; ++r2)
                {
                    if (isValidMove(board, player, c1, r1, c2, r2))
                    {
                        Board b(board);
                        int r = makeMove(b, c1, r1, c2, r2);
                        if (player == 0)
                        {
                            r = -r;
                        }
                        r = checkMove(b, 1 - player, depth - 1, score + r, alpha, beta);
                        if (player == 0)
                        {
                            res = std::min(r, res);
                            if (r < alpha)
                            {
                                return res;
                            }
                            beta = std::min(beta, r);
                        }
                        else
                        {
                            res = std::max(r, res);
                            if (r > beta)
                            {
                                return res;
                            }
                            alpha = std::max(alpha, r);
                        }
                    }
                }
            }
        }
    }
    return res;
}

int computerMove()
{
    int mc1, mr1, mc2, mr2;
    int max = -MAX;
    for (int c1 = 0 ; c1 < N ; ++c1)
    {
        for (int r1 = 0 ; r1 < N ; ++r1)
        {
            for (int c2 = 0 ; c2 < N ; ++c2)
            {
                for (int r2 = 0 ; r2 < N ; ++r2)
                {
                    if (isValidMove(board, 1, c1, r1, c2, r2))
                    {
                        Board b(board);
                        int m = makeMove(b, c1, r1, c2, r2);
                        m = checkMove(b, 0, 7, m, -MAX, MAX);
                        if (m > max)
                        {
                            max = m;
                            mc1 = c1;
                            mr1 = r1;
                            mc2 = c2;
                            mr2 = r2;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Мой ход: " << (char)(mc1 + 'a') << mr1 + 1
        << '-' << (char)(mc2 + 'a') << mr2 + 1 << "\n\n";
    return makeMove(board, mc1, mr1, mc2, mr2);
}

int main()
{
    printBoard();
    while (true)
    {
        int m = playerMove();
        printBoard();
        if (m == KING)
        {
            std::cout << "Вы выиграли!\n";
            break;
        }
        m = computerMove();
        printBoard();
        if (m == KING)
        {
            std::cout << "Я победил!\n";
            break;
        }
    }
}
