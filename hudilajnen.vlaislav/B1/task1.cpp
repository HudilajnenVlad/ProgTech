#include "tasks.hpp"
#include <iostream>
#include <vector>
#include <forward_list>
#include "details.hpp"
#include "sort.hpp"
#include "print.hpp"

void task1(hudilajnen::Order order)
{
  std::vector<int> vecForIndexSort;
  int num = 0;

  while ((std::cin.good()) && (std::cin >> num))
  {
    vecForIndexSort.push_back(num);
  }

  if (!std::cin.eof())
  {
    throw std::runtime_error("Input error.\n");
  }

  if (vecForIndexSort.empty())
  {
    return;
  }

  bool (*comparator)(const int &, const int &) = nullptr;
  comparator = hudilajnen::getComparator<int>(order);

  std::vector<int> vectorForAt = vecForIndexSort;
  hudilajnen::sortBubble<hudilajnen::policyIndexOperator, std::vector<int>>(vecForIndexSort, comparator);
  hudilajnen::print(vecForIndexSort);

  hudilajnen::sortBubble<hudilajnen::policyAt, std::vector<int>>(vectorForAt, comparator);
  hudilajnen::print(vectorForAt);

  std::forward_list<int> list(vecForIndexSort.begin(), vecForIndexSort.end());
  hudilajnen::sortBubble<hudilajnen::policyIterator, std::forward_list<int>>(list, comparator);
  hudilajnen::print(list, " ", false);
}
