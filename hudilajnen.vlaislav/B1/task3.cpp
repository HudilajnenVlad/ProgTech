#include <iostream>
#include <vector>
#include <stdexcept>
#include "print.hpp"

void task3()
{
  int curNumber = -1;
  std::vector<int> vec;
  while (std::cin >> curNumber)
  {
    if (curNumber == 0)
    {
      break;
    }
    vec.push_back(curNumber);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Input Error.\n");
  }

  if (vec.empty())
  {
    return;
  }

  if (curNumber != 0)
  {
    throw std::invalid_argument("Last number must be equal 0\n");
  }

  if (vec.back() == 1)
  {
    std::vector<int>::iterator iterator = vec.begin();
    size_t numEven = 0;
    while (iterator != vec.end())
    {
      if ((*iterator) % 2 == 0)
      {
        ++numEven;
      }
      else
      {
        if (numEven != 0)
        {
          std::swap(*iterator, *(iterator - numEven));
        }
      }
      ++iterator;
    }
    vec.erase(vec.end() - numEven, vec.end());
  }
  else if (vec.back() == 2)
  {
    size_t num = 0;
    std::vector<int>::iterator iterator = vec.begin();
    while (iterator != vec.end())
    {
      if ((*iterator) % 3 == 0)
      {
        ++num;
      }
      ++iterator;
    }
    vec.reserve(vec.size() + num * 3);
    iterator = vec.begin();
    while (iterator != vec.end())
    {
      if ((*iterator) % 3 == 0)
      {
        iterator = vec.insert(++iterator, 3, 1);
        iterator += 3;
      }
      else
      {
        ++iterator;
      }
    }
  }
  hudilajnen::print(vec, " ", false);
}
