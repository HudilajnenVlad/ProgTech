#include "tasks.hpp"
#include <stdexcept>
#include <vector>
#include "sort.hpp"
#include "print.hpp"

namespace hudilajnen
{
  void fillRandom(double *array, int size);
}

void task4(hudilajnen::Order order, int size)
{
  if (size < 0)
  {
    throw std::invalid_argument("Size less zero\n");
  }
  if (size == 0)
  {
    return;
  }
  std::vector<double> vec(size);
  hudilajnen::fillRandom(vec.data(), size);
  hudilajnen::print(vec);

  bool (*comparator)(const double &, const double &) = nullptr;
  comparator = hudilajnen::getComparator<double>(order);
  hudilajnen::sortBubble<hudilajnen::policyIndexOperator, std::vector<double>>(vec, comparator);
  hudilajnen::print(vec, " ", false);
}
