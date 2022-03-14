#include "commands.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <cctype>
#include <map>
#include "interface.hpp"


void readCommand(const std::string &inputCommand, Interface &interface, std::ostream &out)
{
  std::istringstream in{inputCommand};
  std::string command = "";
  in >> command >> std::ws;
  std::map<std::string, void (*)(std::istream &, std::ostream &, Interface &)>::const_iterator iter = commandsMap.find(
      command);
  if (iter == commandsMap.end())
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }
  iter->second(in, out, interface);
}

void executeAdd(std::istream &input, std::ostream &out, Interface &interface)
{
  std::string name, contact;
  if (!(input >> LinkContact{contact} >> LinkName{name}))
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }
  interface.add(contact, name);
}

void executeStore(std::istream &input, std::ostream &out, Interface &interface)
{
  std::string firstMark, secondMark;
  if (!(input >> LinkBookmark{firstMark} >> LinkBookmark{secondMark}))
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }
  interface.store(firstMark, secondMark, out);
}

void executeInsert(std::istream &input, std::ostream &out, Interface &interface)
{
  std::string direction, markName, number, name;
  if (!(input >> direction >> LinkBookmark{markName} >> LinkContact{number} >> LinkName{name}))
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }

  if ((direction == "after") || (direction == "before"))
  {
    interface.insert(direction, markName, number, name, out);
  }
  else
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }
}

void executeDelete(std::istream &input, std::ostream &out, Interface &interface)
{
  std::string markName;
  if (!(input >> LinkBookmark{markName}))
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }
  interface.deleteMark(markName, out);
}

void executeShow(std::istream &input, std::ostream &out, Interface &interface)
{
  std::string markName;
  if (!(input >> LinkBookmark{markName}))
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }
  interface.show(markName, out);
}

void executeMove(std::istream &input, std::ostream &out, Interface &interface)
{
  std::string markName, steps;
  if (!(input >> LinkBookmark{markName} >> steps))
  {
    out << INVALID_COMMAND_ERROR;
    return;
  }
  if ((steps == "first") || (steps == "last"))
  {
    interface.move(markName, steps, out);
  }
  else
  {
    try
    {
      interface.move(markName, std::stoi(steps), out);
    }
    catch (const std::exception &err)
    {
      out << INVALID_STEP_ERROR;
      return;
    }
  }
}

std::istream &operator>>(std::istream &input, LinkName name)
{
  std::ios_base::fmtflags flags = input.flags();
  input >> std::ws;
  if (input.get() != '"')
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  input >> std::noskipws;
  std::string nameString = "";
  std::string tmp = "";
  while ((std::getline(input, tmp, '"') && (!input.eof())))
  {
    nameString += tmp;
    if (nameString.back() == '\\')
    {
      nameString.back() = '"';
    }
    tmp = "";
  }
  if (input.eof())
  {
    if (tmp.empty())
    {
      input.clear();
    }
    else
    {
      for (size_t i = 0; i < tmp.size(); ++i)
      {
        if (!std::isspace(tmp[i]))
        {
          input.setstate(std::ios::failbit);
          return input;
        }
      }
      input.clear();
    }
  }
  name.name = nameString;
  input.setf(flags);
  return input;
}

std::istream &operator>>(std::istream &input, LinkContact contact)
{
  std::string tmp = "";
  input >> tmp;
  if (tmp == "")
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  for (size_t i = 0; i < tmp.size(); ++i)
  {
    if (!std::isdigit(tmp[i]))
    {
      input.setstate(std::ios::failbit);
      return input;
    }
  }
  contact.contact = tmp;
  return input;
}

std::istream &operator>>(std::istream &input, LinkBookmark bookmark)
{
  std::ios_base::fmtflags flags = input.flags();
  std::string tmp = "";
  input >> std::ws >> tmp;
  if (tmp == "")
  {
    input.setstate(std::ios::failbit);
    return input;
  }
  for (size_t i = 0; i < tmp.size(); ++i)
  {
    if (!std::isalnum(tmp[i]) && (tmp[i] != '-'))
    {
      input.setstate(std::ios::failbit);
      return input;
    }
  }
  bookmark.bookmark = tmp;
  input.setf(flags);
  return input;
}
