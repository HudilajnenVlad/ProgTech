#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

namespace hudilajnen
{
  template<typename Container>
  void print(const Container &container, const char *separator = " ", bool intend = true)
  {
    typedef typename Container::const_iterator iterator;
    for (iterator i = container.cbegin(); i != container.cend(); ++i)
    {
      std::cout << *i << separator;
    }
    if (intend)
    {
      std::cout << '\n';
    }
  }
}

#endif
