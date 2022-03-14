#include "circle.hpp"
#include <cmath>
#include <cassert>
#include "base-types.hpp"


Circle::Circle(double radius, const point_t &pos):
    radius_{radius},
    pos_{pos.x, pos.y}
{
  assert(radius > 0.0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return {radius_ * 2, radius_ * 2, pos_};
}

void Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Circle::move(const point_t &pos)
{
  pos_ = pos;
}
