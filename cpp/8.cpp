#include <iostream>
#include <array>
#include <map>
#include <queue>

const int N = 3;
const int SIZE = N * N;

typedef std::array<int, SIZE> Board;

int getKey(const Board &board)
{
    int r = 0;
    for (auto x : board)
    {
        r = r * 9 + x;
    }
    return r;
}

typedef std::map<long long, int> Positions;
Positions positions;

int findEmpty(const Board &board)
{
    for (int i = 0 ; i < SIZE ; ++i)
    {
        if (board[i] == 0)
        {
            return i;
        }
    }
    return -1;
}

void printSolution(Board &board)
{
    int dir = positions[getKey(board)];
    int empty = findEmpty(board);
    int next = -1;
    if (dir == 1)
    {
        next = empty + 1;
    }
    else if (dir == 2)
    {
        next = empty - 1;
    }
    else if (dir == 3)
    {
        next = empty + N;
    }
    else if (dir == 4)
    {
        next = empty - N;
    }
    if (next != -1)
    {
        std::swap(board[next], board[empty]);
        printSolution(board);
        std::swap(board[next], board[empty]);
    }
    for (auto x : board)
    {
        std::cout << x;
    }
    std::cout << "\n";
}

int main()
{
    Board start;
    bool b[SIZE] = {};
    for (int i = 0 ; i < SIZE ; ++i)
    {
        std::cin >> start[i];
        if (start[i] >= 0 && start[i] < SIZE)
        {
            b[start[i]] = true;
        }
    }
    // проверить ввод
    for (int i = 0 ; i < SIZE ; ++i)
    {
        if (!b[i])
        {
            std::cout << "Некорректная позиция\n";
            return 0;
        }
    }

    std::queue<Board> q;
    q.push(start);
    positions[getKey(start)] = -1;
    while (!q.empty())
    {
        Board board = q.front();
        q.pop();
        int empty = findEmpty(board);
        // перебираем все направления движения
        for (int i = 1 ; i <= 4 ; ++i)
        {
            int next = -1;
            if (i == 1 && empty % N != 0)
            {
                next = empty - 1;
            }
            else if (i == 2 && empty % N != N - 1)
            {
                next = empty + 1;
            }
            else if (i == 3 && empty >= N)
            {
                next = empty - N;
            }
            else if (i == 4 && empty < N * N - N)
            {
                next = empty + N;
            }
            if (next != -1)
            {
                Board b = board;
                std::swap(b[empty], b[next]);
                int key = getKey(b);
                if (!positions.contains(key))
                {
                    positions[key] = i;
                    q.push(b);
                }
            }
        }
    }

    Board final = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    if (!positions.contains(getKey(final)))
    {
        std::cout << "Решения не существует!\n";
    }
    else
    {
        printSolution(final);
    }
}
