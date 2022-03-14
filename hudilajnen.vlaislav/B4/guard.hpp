#ifndef GUARD_HPP
#define GUARD_HPP

#include <istream>

class Guard
{
public:
  Guard(std::istream& input);
  ~Guard();

private:
  std::istream& stream_;
  std::istream::fmtflags flags_;
};


#endif
