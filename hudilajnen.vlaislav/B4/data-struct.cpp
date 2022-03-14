#include "data-struct.hpp"
#include <iostream>
#include <string>
#include "guard.hpp"

std::istream &operator>>(std::istream &input, DataStruct &data)
{
  Guard guard(input);
  input >> std::noskipws;
  int key1 = 0;

  input >> skipSpace >> key1;
  if (!input.good())
  {
    return input;
  }
  if ((key1 < MIN_VALUE) || (key1 > MAX_VALUE))
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  input >> skipSpace;
  char ch = ' ';
  input.get(ch);
  if (ch != SEPARATOR)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  int key2 = 0;
  input >> skipSpace >> key2;
  if (!input.good())
  {
    return input;
  }
  if ((key2 < MIN_VALUE) || (key2 > MAX_VALUE))
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  input.get(ch);
  if (ch != SEPARATOR)
  {
    input.setstate(std::ios::failbit);
    return input;
  }

  std::string str = "";
  std::getline(input >> skipSpace, str);
  if (!input.good())
  {
    return input;
  }

  data.key1 = key1;
  data.key2 = key2;
  data.str = str;
  return input;
}

std::ostream &operator<<(std::ostream &output, const DataStruct &data)
{
  output << data.key1 << SEPARATOR << data.key2 << SEPARATOR << data.str;
  return output;
}

std::istream &skipSpace(std::istream &input)
{
  while (std::isblank(input.peek()))
  {
    input.ignore();
  }
  return input;
}

bool operator<(const DataStruct &firstData, const DataStruct &secondData)
{
  if (firstData.key1 != secondData.key1)
  {
    return firstData.key1 < secondData.key1;
  }
  else if (firstData.key2 != secondData.key2)
  {
    return firstData.key2 < secondData.key2;
  }
  else
  {
    return firstData.str.length() < secondData.str.length();
  }
}
