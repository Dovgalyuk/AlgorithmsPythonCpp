#include <iostream>
#include <inttypes.h>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>

static const int N = 7;
typedef uint64_t Field;
std::unordered_map<Field, Field> positions;
static const int dx[4] = {-1, 1, 0, 0};
static const int dy[4] = {0, 0, -1, 1};
std::vector<int> moves[N * N];

bool hasPeg(Field f, int x, int y)
{
    return f & (1ULL << (y * N + x));
}

void printField(Field f)
{
    for (int y = 0 ; y < N ; ++y)
    {
        for (int x = 0 ; x < N ; ++x)
        {
            if (hasPeg(f, x, y))
            {
                std::cout << "o";
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void printSolution(Field f)
{
    Field next = positions[f];
    if (next)
    {
        printSolution(next);
    }
    printField(f);
}

Field readField()
{
    std::string field[N];
    for (int i = 0 ; i < N ; ++i)
    {
        do
        {
            std::getline(std::cin, field[i]);
        }
        while (field[i].length() != N);
    }
    Field res = 0;
    for (int i = 0 ; i < N ; ++i)
    {
        for (int j = 0 ; j < N ; ++j)
        {
            int index = i * N + j;
            if (field[i][j] == 'o')
            {
                res |= 1ULL << index;
            }
            if (field[i][j] != 'X')
            {
                for (int d = 0 ; d < 4 ; ++d)
                {
                    int x = j + dx[d] * 2;
                    int y = i + dy[d] * 2;
                    if (x >= 0 && x < N && y >= 0 && y < N
                        && field[y][x] != 'X')
                    {
                        moves[index].push_back(d);
                    }
                }
            }
        }
    }
    return res;
}

int main()
{
    Field start = readField();

    std::queue<Field> q;
    q.push(start);
    positions[start] = 0;
    Field last;
    while (!q.empty())
    {
        last = q.front();
        q.pop();
        for (int i = 0 ; i < N ; ++i)
        {
            for (int j = 0 ; j < N ; ++j)
            {
                if (!hasPeg(last, j, i))
                {
                    continue;
                }
                for (int d : moves[i * N + j])
                {
                    int x = j + dx[d] * 2;
                    int y = i + dy[d] * 2;
                    int mx = j + dx[d];
                    int my = i + dy[d];
                    if (hasPeg(last, x, y) || !hasPeg(last, mx, my))
                    {
                        continue;
                    }
                    Field next = last;
                    next ^= 1ULL << (i * N + j);
                    next ^= 1ULL << (y * N + x);
                    next ^= 1ULL << (my * N + mx);
                    if (!positions.contains(next))
                    {
                        positions[next] = last;
                        q.push(next);
                    }
                }
            }
        }
    }

    std::cout << "\n";
    printSolution(last);
}
