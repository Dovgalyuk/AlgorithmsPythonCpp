#include <iostream>
#include <stdlib.h>

int harvest_total, harvest, food;
int year, population, land, rats, starved;
int died_total, grain, percent_died, people_came;

void quit()
{
  std::cout << "\n\n\nДо встречи.\n\n";
  exit(0);
}

void printNotEnoughGrain()
{
  std::cout << "Подумайте ещё. У вас всего "
    << grain << " бушелей зерна.\n";
}

void printNotEnoughLand()
{
  std::cout << "Подумайте ещё, у вас есть только "
    << land << " акров земли.\n";
}

void endGameBad()
{
  std::cout << "Ваше правление было ужасным,\n"
    "вас объявили национальным предателем и изгнали из резиденции!!!\n";
  quit();
}

void tradeLand()
{
  int cost = 17 + rand() % 11;
  std::cout << "Стоимость земли сейчас составляет "
    << cost << " бушелей за акр.\n";
  int buysell = 0;
  while (true)
  {
    std::cout << "Сколько акров вы хотите купить/продать? ";
    std::cin >> buysell;
    if (buysell < 0 && -buysell > land)
    {
      printNotEnoughLand();
      continue;
    }
    if (buysell > 0 && cost * buysell > grain)
    {
      printNotEnoughGrain();
      continue;
    }
    break;
  }

  land = land + buysell;
  grain = grain - cost * buysell;
}

void feedPeople()
{
  std::cout << "\n";
  while (true)
  {
    std::cout << "Сколько бушелей зерна вы потратите, чтобы накормить людей? ";
    std::cin >> food;
    if (food < 0)
    {
      continue;
    }
    if (food <= grain)
    {
      break;
    }
    printNotEnoughGrain();
  }
  grain = grain - food;
}

void plantSeeds()
{
  std::cout << "\n";
  int plant = 0;
  while (true)
  {
    std::cout << "Сколько акров земли вы хотите засеять? ";
    std::cin >> plant;
    if (plant < 0)
    {
      continue;
    }
    if (plant > land)
    {
      printNotEnoughLand();
      continue;
    }
    if (plant / 2 > grain)
    {
      printNotEnoughGrain();
      continue;
    }
    if (plant > 10 * population)
    {
      std::cout << "Но у вас только " << population << " человек для работы на полях!\n";
      continue;
    }
    break;
  }

  grain = grain - plant / 2;
  harvest = rand() % 6 + 1;
  harvest_total = plant * harvest;
}

void ratsInvasion()
{
  rats = 0;
  int c = rand() % 6 + 1;
  if (c % 2 == 0)
  {
    rats = grain / c;
  }
  grain -= rats;
}

void harvestGrain()
{
  grain = grain + harvest_total;
}

void changePopulation()
{
  people_came = (rand() % 6 + 1) * (20 * land + grain) / population / 100 + 1;

  starved = population - food / 20;
  if (starved <= 0)
  {
    starved = 0;
  }
  else
  {
    if (starved > 0.45 * population)
    {
      std::cout << "\nЗа год от голода умерло " << starved << " человек!!!\n";
      endGameBad();
    }
    percent_died = ((year - 1) * percent_died + starved * 100 / population) / year;
    population = population - starved;
    died_total = died_total + starved;
  }
  population = population + people_came;
}

void plague()
{
  if (year > 1 && rand() % 100 < 15)
  {
    population -= population / 2;
    std::cout << "\nЭпидемия чумы! Половина населения умерла.\n";
  }
}

void report()
{
  std::cout << "\nХаммурапи, сообщаю Вам,\n";
  std::cout << "в прошлом " << year << " году, " << starved << " людей умерли от голода, "
    << people_came << " человек прибыли в город.\n";
  std::cout << "Всего в городе живёт " << population << " человек.\n";
  std::cout << "Город владеет " << land << " акрами земли.\n";
  std::cout << "Вы собрали " << harvest << " бушелей зерна с акра.\n";
  std::cout << "Крысы съели " << rats << " бушелей зерна.\n";
  std::cout << "Сейчас у вас " << grain << " бушелей в хранилище.\n\n";
}

void final()
{
  std::cout << "За прошедшие десять лет в среднем " << percent_died << " процентов\n"
    << "населения в год умирало от голода. Всего умерло "
    << died_total << " человек!!\n";
  int L = land / population;
  std::cout << "В начале правления у вас было 10 акров земли на человека,\n"
    "а в конце стало " << L << " акров на человека.\n\n";
  if (percent_died > 33 || L < 7)
  {
    endGameBad();
  }
  else if (percent_died > 10 || L < 9)
  {
    std::cout << "Своим жёстким руководством вы переплюнули Ивана Грозного.\n"
      << "Оставшиеся люди будут долго ненавидеть вас!!\n";
  }
  else if (percent_died > 3 || L < 10)
  {
    std::cout << "Ваше правление было не самым плохим.\nХотя "
      << (int)(population * 0.8 * rand() / RAND_MAX) << " человек\n"
      << "предпочли бы, чтобы Ваша жизнь закончилась в результате покушения.\n";
  }
  else
  {
    std::cout << "Фантастический результат!!! Даже Карл Великий и\n"
      << "Пётр Первый не смогли бы лучше!\n";
  }
}

int main()
{
  std::cout << "\t\t\t\tХАММУРАПИ\n";
  std::cout << "\n\n\nПопробуйте управлять древним шумерским государством\n"
    "в течение десяти лет.\n\n";
  population = 100;
  rats = 200;
  harvest_total = 3000;
  grain = harvest_total - rats;
  harvest = 3;
  land = harvest_total / harvest;
  people_came = 5;
  while (true)
  {
    year = year + 1;
    plague();
    report();
    if (year == 11)
    {
      break;
    }
    tradeLand();
    feedPeople();
    plantSeeds();
    ratsInvasion();
    harvestGrain();
    changePopulation();
  }

  final();
  quit();
}
