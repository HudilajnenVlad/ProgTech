#include <iostream>
#include <algorithm>
#include "container.hpp"

void task2(std::ostream &out)
{
  FactorialContainer factorial;

  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';

  std::reverse_copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';
}
