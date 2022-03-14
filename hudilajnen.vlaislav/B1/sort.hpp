#ifndef SORT_HPP
#define SORT_HPP

#include <stdexcept>
#include "details.hpp"

namespace hudilajnen
{
  template<template<typename> typename sortBy, typename container_type>
  void sortBubble(container_type &container,
                  bool (*cmp)(const typename container_type::value_type &a, const typename container_type::value_type &b))
  {
    if (cmp == nullptr)
    {
      throw std::invalid_argument("The comparator was not passed");
    }

    typedef sortBy<container_type> strategy;
    typedef typename strategy::iterator iterator;

    for (iterator i = strategy::getBegin(container); i != strategy::getEnd(container); ++i)
    {
      for (iterator j = i; j != strategy::getEnd(container); ++j)
      {
        if (cmp(strategy::getElement(container, j), strategy::getElement(container, i)))
        {
          std::swap(strategy::getElement(container, j), strategy::getElement(container, i));
        }
      }
    }
  }
}

#endif
