#include <iostream>

int main()
{
  int matches = 23;
  std::cout << "На столе лежит " << matches << " спичек.\n";
  while (matches > 0)
  {
    int move;
    do
    {
      std::cout << "Сколько спичек вы возьмёте? ";
      std::cin >> move;
    }
    while (move < 1 || move > matches || move > 3);
    matches -= move;
    std::cout << "Вы взяли " << move << ", осталось " << matches << " спичек.\n";
    if (matches == 0)
    {
      std::cout << "Последняя спичка ваша, я выиграл!\n";
      break;
    }
    move = (matches - 1) % 4;
    if (move == 0)
    {
      move = 1;
    }
    matches -= move;
    std::cout << "Я беру " << move << ", осталось " << matches << " спичек.\n";
    if (matches == 0)
    {
      std::cout << "Сегодня вам удалось победить. Посмотрим, что будет в следующий раз!\n";
      break;
    }
  }
}
