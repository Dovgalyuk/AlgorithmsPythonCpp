#include <iostream>

char field[3][3];

int checkLine(char a, char b, char c, char xo)
{
  if (!a && b == xo && c == xo)
  {
    return 0;
  }
  if (!b && a == xo && c == xo)
  {
    return 1;
  }
  if (!c && a == xo && b == xo)
  {
    return 2;
  }
  return -1;
}

bool tryFinishLine(char xo)
{
  int t;
  for (int i = 0 ; i < 3 ; ++i)
  {
    // Проверка i-й горизонтали
    t = checkLine(field[i][0], field[i][1], field[i][2], xo);
    if (t >= 0)
    {
      field[i][t] = 'O';
      return true;
    }
    // Проверка i-й вертикали
    t = checkLine(field[0][i], field[1][i], field[2][i], xo);
    if (t >= 0)
    {
      field[t][i] = 'O';
      return true;
    }
  }
  // Проверка одной диагонали
  t = checkLine(field[0][0], field[1][1], field[2][2], xo);
  if (t >= 0)
  {
    field[t][t] = 'O';
    return true;
  }
  // Проверка другой диагонали
  t = checkLine(field[0][2], field[1][1], field[2][0], xo);
  if (t >= 0)
  {
    field[t][2 - t] = 'O';
    return true;
  }
  return false;
}

void computerMove()
{
  int i, j;
  // ход в центр
  if (!field[1][1])
  {
    field[1][1] = 'O';
    return;
  }
  // выигрышный ход
  if (tryFinishLine('O'))
  {
    return;
  }
  // не дать выиграть сопернику
  if (tryFinishLine('X'))
  {
    return;
  }
  // ход в угол
  if (!field[0][0])
  {
    field[0][0] = 'O';
    return;
  }
  if (!field[0][2])
  {
    field[0][2] = 'O';
    return;
  }
  if (!field[2][2])
  {
    field[2][2] = 'O';
    return;
  }
  if (!field[2][0])
  {
    field[2][0] = 'O';
    return;
  }
  // все остальные ходы
  do
  {
    i = rand() % 3;
    j = rand() % 3;
  }
  while (field[i][j]);
  field[i][j] = 'O';
}

bool checkWin()
{
  for (int i = 0 ; i < 3 ; ++i)
  {
    if (field[i][0]
      && field[i][0] == field[i][1]
      && field[i][1] == field[i][2])
    {
      return true;
    }
    if (field[0][i]
      && field[0][i] == field[1][i]
      && field[1][i] == field[2][i])
    {
      return true;
    }
  }
  return (field[0][0]
      && field[0][0] == field[1][1]
      && field[1][1] == field[2][2])
    || (field[0][2]
      && field[0][2] == field[1][1]
      && field[1][1] == field[2][0]);
}

void playerMove()
{
  int i, j, move;
  do
  {
    std::cout << "Введите ваш ход - номер клетки: ";
    std::cin >> move;
    i = (move - 1) / 3;
    j = (move - 1) % 3;
  }
  while (move <= 0 || move > 9
    || field[i][j]);
  field[i][j] = 'X';
}

void printField()
{
  for (int i = 0 ; i < 3 ; ++i)
  {
    for (int j = 0 ; j < 3 ; ++j)
    {
      if (field[i][j])
        std::cout << field[i][j] << " ";
      else
        std::cout << i * 3 + j + 1 << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

int main()
{
  int moves = 0;
  while (true)
  {
    printField();
    if (checkWin())
    {
      std::cout << "Я выиграл!\n";
      break;
    }
    playerMove();
    ++moves;
    printField();
    if (checkWin())
    {
      std::cout << "Вы победили!\n";
      break;
    }
    if (moves == 9)
    {
      std::cout << "Ничья!\n";
      break;
    }
    std::cout << "Мой ход:\n";
    computerMove();
    ++moves;
  }
}
