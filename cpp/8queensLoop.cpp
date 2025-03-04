#include <iostream>

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

int main()
{
  for (int a = 0 ; a < 4 ; ++a)
  {
    for (int b = 0 ; b < 4 ; ++b)
    {
      if (!check(0, a, 1, b))
      {
        continue;
      }
      for (int c = 0 ; c < 4 ; ++c)
      {
        if (!check(0, a, 2, c) || !check(1, b, 2, c))
        {
          continue;
        }
        for (int d = 0 ; d < 4 ; ++d)
        {
          if (!check(0, a, 3, d) || !check(1, b, 3, d) || !check(2, c, 3, d))
          {
            continue;
          }
          std::string field[4] = {"....", "....", "....", "...."};
          field[a][0] = 'Q';
          field[b][1] = 'Q';
          field[c][2] = 'Q';
          field[d][3] = 'Q';
          for (int i = 0 ; i < 4 ; ++i)
          {
            std::cout << field[i] << "\n";
          }
          std::cout << "\n";
        }
      }
    }
  }
}
