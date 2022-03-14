#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <list>
#include <stdexcept>

template<typename T>
class QueueWithPriority
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void add(T &element, ElementPriority priority);

  template<typename F>
  void getFirstElement(const F &handleTopElement);

  void accelerate();

  bool isEmpty() const;

private:
  std::list<T> high_;
  std::list<T> normal_;
  std::list<T> low_;
};

template<typename T>
template<typename F>
void QueueWithPriority<T>::getFirstElement(const F &handleTopElement)
{
  if (!high_.empty())
  {
    handleTopElement(high_.front());
    high_.pop_front();
  }
  else if (!normal_.empty())
  {
    handleTopElement(normal_.front());
    normal_.pop_front();
  }
  else if (!low_.empty())
  {
    handleTopElement(low_.front());
    low_.pop_front();
  }
  else
  {
    throw std::runtime_error("<EMPTY>\n");
  }
}

template<typename T>
void QueueWithPriority<T>::add(T &element, ElementPriority priority)
{
  switch (priority)
  {
    case LOW:
      low_.push_back(element);
      break;
    case NORMAL:
      normal_.push_back(element);
      break;
    case HIGH:
      high_.push_back(element);
      break;
    default:
      throw std::invalid_argument("Error. Unknown priority. \n");
  }
}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  high_.splice(high_.end(), low_);
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const
{
  return high_.empty() && normal_.empty() && low_.empty();
}

#endif
