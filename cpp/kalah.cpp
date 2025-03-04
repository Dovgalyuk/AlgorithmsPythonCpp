#include <iostream>
#include <iomanip>
#include <array>

const int N = 6;
const int K1 = N;
const int K2 = 2 * N + 1;
const int First1 = 0;
const int Last1 = N - 1;
const int First2 = K1 + 1;
const int Last2 = K2 - 1;
const int SZ = N * 2 + 2;
const int S = 6;
const int TOTAL = S * N * 2;

typedef std::array<int, SZ> Board;

Board board;

enum MoveResult
{
    MoveNext,
    MoveAgain,
    MoveEnd,
};

void printBoard()
{
    std::cout << " ";
    for (int i = N ; i >= 1 ; --i)
    {
        std::cout << std::setw(3) << i;
    }
    std::cout << "\n ";
    for (int i = Last2 ; i >= First2 ; --i)
    {
        std::cout << std::setw(3) << board[i];
    }
    std::cout << "\n" << std::setw(2) << board[K2]
        << "                  " << board[K1] << "\n ";
    for (int i = First1 ; i <= Last1 ; ++i)
    {
        std::cout << std::setw(3) << board[i];
    }
    std::cout << "\n ";
    for (int i = 1 ; i <= N ; ++i)
    {
        std::cout << std::setw(3) << i;
    }
    std::cout << "\n\n";
}

MoveResult makeMove(Board &board, int m)
{
    // посев камней
    int s = board[m];
    board[m] = 0;
    int cur = m;
    int player = m <= Last1 ? 0 : 1;
    int kalahOpp = player == 0 ? K2 : K1;
    while (s)
    {
        cur = (cur + 1) % SZ;
        if (cur != kalahOpp)
        {
            --s;
            ++board[cur];
        }
    }
    // захват камней противника
    int lastPlayer = cur <= Last1 ? 0 : 1;
    int opp = SZ - 2 - cur;
    int kalah = player == 0 ? K1 : K2;
    if (cur != kalah && player == lastPlayer && board[cur] == 1 && board[opp])
    {
        // обновить калах
        board[kalah] += board[cur] + board[opp];
        // очистить лунки
        board[cur] = 0;
        board[opp] = 0;
    }
    // проверка, стал ли ход последним
    int sum1 = 0;
    int sum2 = 0;
    for (int i = 0 ; i < N ; ++i)
    {
        sum1 += board[First1 + i];
        sum2 += board[First2 + i];
    }
    if (!sum1 || !sum2)
    {
        for (int i = 0 ; i < N ; ++i)
        {
            board[K1] += board[First1 + i];
            board[K2] += board[First2 + i];
            board[First1 + i] = 0;
            board[First2 + i] = 0;
        }
        return MoveEnd;
    }
    // повторный ход
    if (cur == kalah)
    {
        return MoveAgain;
    }

    return MoveNext;
}

MoveResult playerMove()
{
    int m;
    do
    {
        std::cout << "Выберите лунку с камнями: ";
        std::cin >> m;
        --m;
    }
    while (m < 0 || m >= N || !board[First1 + m]);
    return makeMove(board, First1 + m);
}

int checkMove(Board board, int player, int m, int depth, int alpha, int beta)
{
    MoveResult mr = makeMove(board, m);
    if (mr == MoveEnd || depth == 0)
    {
        // оценка позиции
        return board[K2] - board[K1];
    }
    int nextPlayer = 1 - player;
    if (mr == MoveAgain)
    {
        nextPlayer = player;
    }
    int res = nextPlayer == 0 ? TOTAL : -TOTAL;
    for (int i = 0 ; i < N ; ++i)
    {
        int m = i + (nextPlayer ? First2 : First1);
        if (board[m])
        {
            int r = checkMove(board, nextPlayer, m, depth - 1, alpha, beta);
            // игрок минимизирует оценку
            if (nextPlayer == 0)
            {
                res = std::min(r, res);
                if (res < alpha)
                {
                    break;
                }
                beta = std::min(beta, res);
            }
            // компьютер максимизирует оценку
            if (nextPlayer == 1)
            {
                res = std::max(r, res);
                if (res > beta)
                {
                    break;
                }
                alpha = std::max(alpha, res);
            }
        }
    }
    return res;
}

MoveResult computerMove()
{
    int m = -1;
    int max = -TOTAL;
    for (int i = First2 ; i <= Last2 ; ++i)
    {
        if (board[i])
        {
            int r = checkMove(board, 1, i, 12, -TOTAL, TOTAL);
            if (r > max)
            {
                m = i;
                max = r;
            }
        }
    }

    std::cout << "Мой ход: " << m - First2 + 1 << "\n";
    return makeMove(board, m);
}

int main()
{
    for (int i = 0 ; i < N ; ++i)
    {
        board[First1 + i] = S;
        board[First2 + i] = S;
    }
    while (true)
    {
        MoveResult res;
        do
        {
            printBoard();
            res = playerMove();
        }
        while (res == MoveAgain);
        if (res == MoveEnd)
        {
            break;
        }
        do
        {
            printBoard();
            res = computerMove();
        }
        while (res == MoveAgain);
        if (res == MoveEnd)
        {
            break;
        }
    }
    printBoard();
    if (board[K1] > board[K2])
    {
        std::cout << "Вы победили!\n";
    }
    else if (board[K2] > board[K1])
    {
        std::cout << "Я выиграл!\n";
    }
    else
    {
        std::cout << "Ничья.\n";
    }
}
