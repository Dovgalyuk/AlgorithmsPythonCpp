#include <iostream>
#include <string>
#include <array>
#include <unordered_set>

const int N = 3;

enum MoveResult
{
    OK,
    PLAYER,
    COMPUTER
};

typedef std::array<std::string, N> Board;
std::unordered_set<int> bad;

Board board;
Board last;

int boardCode(const Board &board)
{
    int res = 0;
    for (auto row : board)
    {
        for (auto c : row)
        {
            res *= 3;
            if (c == 'p')
            {
                res += 1;
            }
            if (c == 'P')
            {
                res += 2;
            }
        }
    }
    return res;
}


bool yesNo(const std::string &question)
{
    while (true)
    {
        std::cout << question << " (y/n) ";
        char c;
        std::cin >> c;
        if (c == 'y' || c == 'Y')
        {
            return true;
        }
        if (c == 'n' || c == 'N')
        {
            return false;
        }
    }
}

void printBoard()
{
    std::cout << "  abc\n";
    for (int i = N - 1 ; i >= 0 ; --i)
    {
        std::cout << i + 1 << " " << board[i] << "\n";
    }
    std::cout << "\n";
}

bool isValidMove(char player, int c1, int r1, int c2, int r2)
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
    if (f != player)
    {
        return false;
    }
    int dy = f == 'P' ? 1 : -1;
    if (r1 + dy != r2)
    {
        return false;
    }
    char t = board[r2][c2];
    if (c1 == c2)
    {
        return t == '.';
    }
    if (c1 + 1 == c2 || c1 - 1 == c2)
    {
        return t != '.' && f != t;
    }
    return false;
}

void makeMove(Board &board, int c1, int r1, int c2, int r2)
{
    board[r2][c2] = board[r1][c1];
    board[r1][c1] = '.';
}

MoveResult computerMove()
{
    bool foundBad = true;
    int mc = -1, mr, mc2;
    for (int r = 1 ; r < N ; ++r)
    {
        for (int c = 0 ; c < N ; ++c)
        {
            if (board[r][c] == 'p')
            {
                for (int c2 = c - 1 ; c2 <= c + 1 ; ++c2)
                {
                    if (isValidMove('p', c, r, c2, r - 1))
                    {
                        if (foundBad)
                        {
                            mc = c;
                            mr = r;
                            mc2 = c2;
                        }
                        Board b = board;
                        makeMove(b, c, r, c2, r - 1);
                        if (!bad.contains(boardCode(b)))
                        {
                            foundBad = false;
                        }
                    }
                }
            }
        }
    }
    if (mc < 0)
    {
        return PLAYER;
    }
    makeMove(board, mc, mr, mc2, mr - 1);
    if (!foundBad)
    {
        last = board;
    }
    std::cout << "Мой ход: " << (char)(mc + 'a') << mr + 1
        << '-' << (char)(mc2 + 'a') << mr << "\n\n";
    if (mr == 1)
    {
        return COMPUTER;
    }
    return OK;
}

MoveResult playerMove()
{
    bool hasMove = false;
    for (int r = 0 ; r < N - 1 ; ++r)
    {
        for (int c = 0 ; c < N ; ++c)
        {
            if (board[r][c] == 'P')
            {
                for (int c2 = c - 1 ; c2 <= c + 1 ; ++c2)
                {
                    if (isValidMove('P', c, r, c2, r + 1))
                    {
                        hasMove = true;
                    }
                }
            }
        }
    }
    if (!hasMove)
    {
        return COMPUTER;
    }
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
    while (!isValidMove('P', c1, r1, c2, r2));
    makeMove(board, c1, r1, c2, r2);
    if (r2 == N - 1)
    {
        return PLAYER;
    }
    return OK;
}

int main()
{
    do
    {
        last = Board();
        board = {"PPP", "...", "ppp"};
        MoveResult res = OK;
        while (res == OK)
        {
            printBoard();
            res = playerMove();
            if (res != OK)
            {
                break;
            }
            printBoard();
            res = computerMove();
        }
        printBoard();
        if (res == PLAYER)
        {
            std::cout << "Вы выиграли!\n";
            bad.insert(boardCode(last));
        }
        else
        {
            std::cout << "Я победил!\n";
        }
    }
    while (yesNo("Сыграем ещё?"));
}
