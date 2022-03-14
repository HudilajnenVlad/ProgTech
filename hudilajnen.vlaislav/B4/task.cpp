#include "task.hpp"
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "data-struct.hpp"

void task(std::istream &input, std::ostream &output)
{
  std::vector<DataStruct> vector{std::istream_iterator<DataStruct>(input), std::istream_iterator<DataStruct>()};
  if (input.fail() && !input.eof())
  {
    throw std::invalid_argument("Input Error");
  }
  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(output, "\n"));
}
