#include <cmath>
#include "base-types.hpp"

bool implementationDetails::isOverlap(const hudilajnen::rectangle_t &frame1, const hudilajnen::rectangle_t &frame2)
{
  double dx = abs(frame1.pos.x - frame2.pos.x);
  double dy = abs(frame1.pos.y - frame2.pos.y);

  return (dx < ((frame1.width + frame2.width) / 2) && (dy < (frame1.width + frame2.width) / 2));
}
