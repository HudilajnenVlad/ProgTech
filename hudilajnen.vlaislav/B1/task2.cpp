#include "tasks.hpp"
#include <fstream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "print.hpp"

void task2(const char *file)
{
  if (file == nullptr)
  {
    throw std::invalid_argument("File name is empty.\n");
  }
  std::ifstream fin(file);
  if (!fin.is_open())
  {
    throw std::runtime_error("File is not open.\n");
  }

  int sizeMax = 10;

  std::unique_ptr<char[], decltype(&free)> array(static_cast<char *>(malloc(sizeMax)), free);
  int curSize = 0;
  while (fin.good())
  {
    fin.read(&array[curSize], sizeMax - curSize);
    curSize += fin.gcount();
    if (curSize == sizeMax)
    {
      sizeMax *= 2;
      std::unique_ptr<char[], decltype(&free)> tmpArray(static_cast<char *>(realloc(array.get(), sizeMax)), free);
      if (!tmpArray)
      {
        throw std::runtime_error("Cant reallocated memory\n");
      }
      array.release();
      array.swap(tmpArray);
    }
  }

  if (curSize == 0)
  {
    return;
  }
  std::vector<char> vec(array.get(), array.get() + curSize);
  hudilajnen::print(vec, "", false);
}
