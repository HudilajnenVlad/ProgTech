#include "details.hpp"
#include <cstring>
#include <stdexcept>

namespace hudilajnen
{
  Order getOrderMode(const char *order)
  {
    Order orderMode = ASCENDING;
    if (std::strcmp(order, "ascending") == 0)
    {
      orderMode = ASCENDING;
    }
    else if (std::strcmp(order, "descending") == 0)
    {
      orderMode = DESCENDING;
    }
    else
    {
      throw std::invalid_argument("Bad order argument\n");
    }
    return orderMode;
  }
}
