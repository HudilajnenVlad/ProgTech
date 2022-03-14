#include <iostream>
#include <stdexcept>
#include <cstring>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid count of argument.\n");
    }
    int var = 0;
    size_t pos = 0;
    try
    {
      var = std::stoi(argv[1], &pos);
      if (pos != std::strlen(argv[1]))
      {
        std::cerr << "Error, invalid argument format.\n";
        return 1;
      }
    }
    catch (const std::out_of_range &ex)
    {
      std::cerr << "Error, argument is too big.\n";
      return 1;
    }
    catch (const std::invalid_argument &ex)
    {
      std::cerr << "Error, invalid argument.\n";
      return 1;
    }

    switch (var)
    {
      case 1:
        task1(std::cin, std::cout);
        break;
      case 2:
        task2(std::cout);
        break;
      default:
        std::cerr << "Error, invalid number of task.\n";
        return 1;
    }
  }
  catch (const std::exception &ex)
  {
    std::cerr << ex.what();
    return 1;
  }
  return 0;
}
