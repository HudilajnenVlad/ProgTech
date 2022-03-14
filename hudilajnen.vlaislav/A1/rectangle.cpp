#include "rectangle.hpp"
#include <cassert>
#include "base-types.hpp"

Rectangle::Rectangle(double width, double height, const point_t &pos):
    rectangle_{width, height, pos}
{
  assert((width > 0.0) && (height > 0.0));
}

double Rectangle::getArea() const
{
  return rectangle_.width * rectangle_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rectangle_;
}

void Rectangle::move(double x, double y)
{
  rectangle_.pos.x += x;
  rectangle_.pos.y += y;
}

void Rectangle::move(const point_t &pos)
{
  rectangle_.pos = pos;
}
