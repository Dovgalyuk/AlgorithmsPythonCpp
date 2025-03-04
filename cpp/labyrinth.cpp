#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Pos
{
    int x, y;
};

std::vector<std::string> maze;
std::vector<std::vector<Pos>> prev;

Pos dir[4] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

void inputMaze()
{
    std::cout << "Введите лабиринт со стартовой клеткой S и финишной E.\n";
    while (true)
    {
        std::string s;
        std::getline(std::cin, s);
        if (s.empty())
        {
            break;
        }
        maze.push_back(s);
    }
}

Pos findChar(char c)
{
    for (int y = 0 ; y < maze.size() ; ++y)
    {
        for (int x = 0 ; x < maze[y].size() ; ++x)
        {
            if (maze[y][x] == c)
            {
                return {x, y};
            }
        }
    }
    return {-1, -1};
}

void findPath()
{
    prev.resize(maze.size());
    for (int y = 0 ; y < maze.size() ; ++y)
    {
        prev[y].resize(maze[y].size(), {-1, -1});
    }
    Pos start = findChar('S');
    prev[start.y][start.x] = start;
    std::queue<Pos> q;
    q.push(start);

    while (!q.empty())
    {
        Pos cur = q.front();
        q.pop();

        for (auto d : dir)
        {
            int x = cur.x + d.x;
            int y = cur.y + d.y;
            if (prev[y][x].x < 0 && maze[y][x] != '#')
            {
                prev[y][x] = cur;
                q.push({x, y});
            }
        }
    }
}

void outputPath()
{
    Pos end = findChar('E');
    if (end.x < 0 || prev[end.y][end.x].x < 0)
    {
        std::cout << "Пути между S и E не существует.\n";
        return;
    }
    while (prev[end.y][end.x].x != end.x
        || prev[end.y][end.x].y != end.y)
    {
        end = prev[end.y][end.x];
        maze[end.y][end.x] = '*';
    }
    maze[end.y][end.x] = 'S';
    std::cout << "Кратчайший путь:\n";
    for (auto s : maze)
    {
        std::cout << s << '\n';
    }
}

int main()
{
    inputMaze();
    findPath();
    outputPath();
}
