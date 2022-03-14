#include "guard.hpp"
#include <istream>

Guard::Guard(std::istream &input) :
    stream_(input),
    flags_(input.flags())
{
}

Guard::~Guard()
{
  stream_.setf(flags_);
}
