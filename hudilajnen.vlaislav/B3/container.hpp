#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
  static const size_t MIN_INDEX = 1;
  static const size_t MAX_INDEX = 11;

public:
  class Iterator
      : public std::iterator<std::bidirectional_iterator_tag, unsigned int>
  {
  public:
    Iterator();

    Iterator(size_t index);

    unsigned int &operator*();

    Iterator &operator++();

    Iterator &operator--();

    Iterator operator++(int);

    Iterator operator--(int);

    bool operator!=(const Iterator &other);

    bool operator==(const Iterator &other);

  private:
    unsigned int index_;
    unsigned int factorialValue_;
  };

  typedef std::reverse_iterator<Iterator> reverse_iterator;

  FactorialContainer() = default;

  Iterator begin() const;

  Iterator end() const;

  reverse_iterator rbegin() const;

  reverse_iterator rend() const;

};


#endif
