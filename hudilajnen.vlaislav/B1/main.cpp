#include <iostream>
#include <stdexcept>
#include "details.hpp"
#include "tasks.hpp"

namespace hudilajnen
{
  Order getOrderMode(const char *order);
}

int main(int argc, char *argv[])
{
  try
  {
    if ((argc <= 1) || (argc > 4))
    {
      std::cerr << "Invalid count of arguments.\n";
      return 1;
    }
    hudilajnen::TaskVar var = hudilajnen::TaskVar::TASK1;
    try
    {
      var = hudilajnen::TaskVar(std::stoi(argv[1]));
    }
    catch (const std::invalid_argument &ex)
    {
      std::cerr << "Invalid Argument in task number\n";
      return 1;
    }
    catch (const std::out_of_range &ex)
    {
      std::cerr << "Task number is too much";
      return 1;
    }

    switch (var)
    {
      case hudilajnen::TASK1:
        if (argc != 3)
        {
          std::cerr << "Invalid count of arguments.\n";
          return 1;
        }
        task1(hudilajnen::getOrderMode(argv[2]));
        break;
      case hudilajnen::TASK2:
        if (argc != 3)
        {
          std::cerr << "Invalid count of arguments.\n";
          return 1;
        }
        task2(argv[2]);
        break;
      case hudilajnen::TASK3:
        if (argc != 2)
        {
          std::cerr << "Invalid count of arguments.\n";
          return 1;
        }
        task3();
        break;
      case hudilajnen::TASK4:
      {
        if (argc != 4)
        {
          std::cerr << "Invalid count of arguments.\n";
          return 1;
        }
        int sizeTask4 = 0;
        try
        {
          sizeTask4 = std::stoi(argv[3]);
        }
        catch (const std::invalid_argument &ex)
        {
          std::cerr << "Invalid Argument in task number\n";
          return 1;
        }
        catch (const std::out_of_range &ex)
        {
          std::cerr << "Task number is too much\n";
          return 1;
        }
        task4(hudilajnen::getOrderMode(argv[2]), sizeTask4);
        break;
      }
      default:
        std::cerr << "Incorrect number of task.\n";
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
