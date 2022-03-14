#include "../common/circle.hpp"
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"


hudilajnen::Circle::Circle(double radius, const point_t &pos):
    radius_{radius},
    pos_{pos.x, pos.y}
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Invalid radius: circle's radius can't be less or equal then zero");
  }
}

double hudilajnen::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

hudilajnen::rectangle_t hudilajnen::Circle::getFrameRect() const noexcept
{
  return {radius_ * 2, radius_ * 2, pos_};
}

hudilajnen::point_t hudilajnen::Circle::getCenter() const noexcept
{
  return pos_;
}

void hudilajnen::Circle::move(double x, double y) noexcept
{
  pos_.x += x;
  pos_.y += y;
}

void hudilajnen::Circle::move(const hudilajnen::point_t &pos) noexcept
{
  pos_ = pos;
}

void hudilajnen::Circle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Invalid scale coefficient: scale coefficient can not be less then zero");
  }

  radius_ *= k;
}

void hudilajnen::Circle::rotate(double) noexcept
{}

void hudilajnen::Circle::print() const noexcept
{
  std::cout << "Circle (radius = " << radius_ << ", pos(" << pos_.x << ", " << pos_.y << "))";
}
