#include <iostream>
#include <string>

const int N = 8;

int queens[N];

bool check(int x1, int y1, int x2, int y2)
{
  if (y1 == y2)
  {
    return false;
  }
  if (x2 - x1 == y2 - y1 || x2 - x1 == y1 - y2)
  {
    return false;
  }
  return true;
}

void find(int q)
{
  if (q == N)
  {
    for (int i = 0 ; i < N ; ++i)
    {
      std::string line(N, '.');
      line[queens[i]] = 'Q';
      std::cout << line << '\n';
    }
    std::cout << '\n';
    return;
  }
  for (int i = 0 ; i < N ; ++i)
  {
    bool ok = true;
    for (int k = 0 ; ok && k < q ; ++k)
    {
      ok = check(k, queens[k], q, i);
    }
    if (ok)
    {
      queens[q] = i;
      find(q + 1);
    }
  }
}

int main()
{
  find(0);
}
