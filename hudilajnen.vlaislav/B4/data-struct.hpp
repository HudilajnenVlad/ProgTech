#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>


const int MAX_VALUE = 5;
const int MIN_VALUE = -5;
const char SEPARATOR = ',';

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

bool operator<(const DataStruct &firstData, const DataStruct &secondData);

std::istream &operator>>(std::istream &input, DataStruct &data);

std::ostream &operator<<(std::ostream &output, const DataStruct &data);

std::istream &skipSpace(std::istream &input);

#endif
