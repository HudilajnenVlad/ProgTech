#ifndef DETAILS_HPP
#define DETAILS_HPP

#include <stdexcept>

namespace hudilajnen
{
  template<typename Container>
  struct policyIndexOperator
  {
    typedef typename Container::value_type type;
    typedef size_t iterator;

    static size_t getBegin(const Container &)
    {
      return 0;
    }

    static size_t getEnd(const Container &container)
    {
      return container.size();
    }

    static type &getElement(Container &container, size_t i)
    {
      return container[i];
    }
  };

  template<typename Container>
  struct policyAt
  {
    typedef typename Container::value_type type;
    typedef size_t iterator;

    static size_t getBegin(Container &)
    {
      return 0;
    }

    static size_t getEnd(Container &container)
    {
      return container.size();
    }

    static type &getElement(Container &container, size_t i)
    {
      return container.at(i);
    }
  };

  template<typename Container>
  struct policyIterator
  {
    typedef typename Container::value_type type;
    typedef typename Container::iterator iterator;

    static iterator getBegin(Container &container)
    {
      return container.begin();
    }

    static iterator getEnd(Container &container)
    {
      return container.end();
    }

    static type &getElement(Container &, iterator i)
    {
      return (*i);
    }
  };

  template<typename T>
  bool cmpAscending(const T &a, const T &b)
  {
    return a < b;
  }

  template<typename T>
  bool cmpDescending(const T &a, const T &b)
  {
    return a > b;
  }

  enum Order
  {
    ASCENDING,
    DESCENDING
  };

  enum TaskVar
  {
    TASK1 = 1,
    TASK2,
    TASK3,
    TASK4
  };

  template<typename T>
  bool (*getComparator(Order order))(const T &, const T &)
  {
    bool (*comparator)(const T &, const T &) = nullptr;
    if (order == ASCENDING)
    {
      comparator = cmpAscending<T>;
    }
    else if (order == DESCENDING)
    {
      comparator = cmpDescending<T>;
    }
    return comparator;
  }

  Order getOrderMode(const char *order);
}
#endif
