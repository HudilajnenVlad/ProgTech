#include "container.hpp"
#include <stdexcept>

FactorialContainer::Iterator::Iterator() :
    index_(1),
    factorialValue_(1)
{}

FactorialContainer::Iterator::Iterator(size_t index) :
    index_(index),
    factorialValue_(MIN_INDEX)
{
  if (index > MAX_INDEX)
  {
    throw std::out_of_range("Index must be less than 11\n");
  }
  if (index < MIN_INDEX)
  {
    throw std::out_of_range("Index must be more than 0\n");
  }
  for (size_t i = 1; i <= index; ++i)
  {
    factorialValue_ *= i;
  }
}

unsigned int &FactorialContainer::Iterator::operator*()
{
  return factorialValue_;
}

FactorialContainer::Iterator &FactorialContainer::Iterator::operator++()
{
  index_++;
  if (index_ > MAX_INDEX)
  {
    throw std::out_of_range("Index must be less than 11\n");
  }
  factorialValue_ *= index_;
  return *this;
}

FactorialContainer::Iterator &FactorialContainer::Iterator::operator--()
{
  factorialValue_ /= index_;
  index_--;
  if (index_ < MIN_INDEX)
  {
    throw std::out_of_range("Index must be more than 1\n");
  }
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator++(int)
{
  const Iterator tmp = *this;
  this->operator++();
  return tmp;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator--(int)
{
  const Iterator tmp = *this;
  this->operator--();
  return tmp;
}

bool FactorialContainer::Iterator::operator!=(const Iterator &other)
{
  return factorialValue_ != other.factorialValue_;
}

bool FactorialContainer::Iterator::operator==(const Iterator &other)
{
  return factorialValue_ == other.factorialValue_;
}

FactorialContainer::Iterator FactorialContainer::begin() const
{
  return Iterator(MIN_INDEX);
}

FactorialContainer::Iterator FactorialContainer::end() const
{
  return Iterator(MAX_INDEX);
}

FactorialContainer::reverse_iterator FactorialContainer::rbegin() const
{
  return std::make_reverse_iterator(end());
}

FactorialContainer::reverse_iterator FactorialContainer::rend() const
{
  return std::make_reverse_iterator(begin());
}
