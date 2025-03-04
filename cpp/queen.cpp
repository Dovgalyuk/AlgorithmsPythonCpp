#include <iostream>

void inputPos(int &x, int &y)
{
  char a, b;
  do
  {
    std::cin >> a >> b;
  }
  while (a < 'a' || a > 'h'
    || b < '1' || b > '8');
  x = a - 'a' + 1;
  y = b - '0';
}

void printField(int x, int y)
{
  for (int i = 8 ; i > 0 ; --i)
  {
    std::string s(8, '.');
    if (i == y)
    {
      s[x - 1] = 'Q';
    }
    std::cout << i << ' ' << s << '\n';
  }
  std::cout << "  abcdefgh\n";
}

bool checkMove(int x, int y, int &qx, int &qy)
{
  if (x > qx || y > qy
    || (x == qx && y == qy))
  {
    return false;
  }
  if (x == qx || y == qy
    || y - qy == x - qx)
  {
    qx = x;
    qy = y;
    return true;
  }
  return false;
}

int main()
{
  std::cout << "Игра \"Ферзя в угол\"\n";
  int x, y;
  printField(0, 0);
  do
  {
    std::cout << "Выберите начальное положение (a8-g8, h1-h8): ";
    inputPos(x, y);
  }
  while (x != 8 && y != 8);

  printField(x, y);
  while (true)
  {
    if (!checkMove(1, 1, x, y)
      && !checkMove(2, 3, x, y)
      && !checkMove(3, 2, x, y)
      && !checkMove(6, 4, x, y)
      && !checkMove(4, 6, x, y))
    {
      if (x > 1)
      {
        --x;
      }
      else
      {
        --y;
      }
    }
    std::cout << "Мой ход " << (char)('a' + x - 1) << y << "\n";
    printField(x, y);
    if (x == 1 && y == 1)
    {
      std::cout << "Вы проиграли!\n";
      break;
    }
    int x1, y1;
    while (true)
    {
      std::cout << "Куда вы будете ходить? ";
      inputPos(x1, y1);
      int dx = x1 - x;
      int dy = y1 - y;
      if ((dx < 0 && dy == 0)
        || (dy < 0 && dx == 0)
        || (dx < 0 && dx == dy))
      {
        break;
      }
    }
    x = x1;
    y = y1;
    printField(x, y);
    if (x == 1 && y == 1)
    {
      std::cout << "Вы выиграли, поздравляю!\n";
      break;
    }
  }
}
