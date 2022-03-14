#include "tasks.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include "queue.hpp"

void addDataInQueue(std::istringstream &in, QueueWithPriority<std::string> &queue);

void print(const std::string &element);

void task1()
{
  std::string inputString = "";
  QueueWithPriority<std::string> queue;
  while (std::getline(std::cin, inputString))
  {
    std::istringstream in{inputString};
    std::string command = "";
    in >> command >> std::ws;
    if ((command == "add") && (!in.eof()))
    {
      addDataInQueue(in, queue);
    }
    else if ((command == "get") && (in.eof()))
    {
      if (queue.isEmpty())
      {
        std::cout << "<EMPTY>\n";
      }
      else
      {
        queue.getFirstElement(print);
      }
    }
    else if ((command == "accelerate") && (in.eof()))
    {
      queue.accelerate();
    }
    else
    {
      std::cout << ("<INVALID COMMAND>\n");
    }
  }
}

void print(const std::string &element)
{
  std::cout << element << '\n';
}

void addDataInQueue(std::istringstream &in, QueueWithPriority<std::string> &queue)
{
  std::string priority = "";
  in >> priority >> std::ws;
  std::string data = "";
  std::getline(in, data);
  if ((priority == "") || (data == ""))
  {
    std::cout << "<INVALID COMMAND>\n";
  }
  if (priority == "low")
  {
    queue.add(data, QueueWithPriority<std::string>::ElementPriority::LOW);
  }
  else if (priority == "normal")
  {
    queue.add(data, QueueWithPriority<std::string>::ElementPriority::NORMAL);
  }
  else if (priority == "high")
  {
    queue.add(data, QueueWithPriority<std::string>::ElementPriority::HIGH);
  }
  else
  {
    std::cout << "<INVALID COMMAND>\n";
  }
}
