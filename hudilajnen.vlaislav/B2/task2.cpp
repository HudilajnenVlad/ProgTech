#include "tasks.hpp"
#include <iostream>
#include <stdexcept>
#include <list>

void task2()
{
  const size_t maxCount = 20;
  const int minNum = 1;
  const int maxNum = 20;
  std::list<int> list;
  int num = 0;
  size_t count = 0;
  while (std::cin >> num)
  {
    if ((num < minNum) || (num > maxNum))
    {
      throw std::out_of_range("Error, argument out of range [1;20]. \n");
    }
    ++count;
    if (count > maxCount)
    {
      throw std::runtime_error("Error, count of element more 20. \n");
    }
    list.push_back(num);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Input error.\n");
  }

  std::list<int>::iterator i = list.begin();
  std::list<int>::iterator j = list.end();
  while (i != j)
  {
    std::cout << *(i++) << ' ';
    if (i == j)
    {
      break;
    }
    std::cout << *(--j) << ' ';
  }
  std::cout << '\n';
}
