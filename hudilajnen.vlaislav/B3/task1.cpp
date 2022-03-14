#include <iostream>
#include "interface.hpp"
#include "commands.hpp"

void task1(std::istream &input, std::ostream &out)
{
  Interface interface;
  std::string command;
  while (std::getline(input, command))
  {
    readCommand(command, interface, out);
  }
  if (!input.eof())
  {
    throw std::runtime_error("Error with reading command\n");
  }
}
