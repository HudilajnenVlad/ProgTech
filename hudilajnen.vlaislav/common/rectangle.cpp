#include "../common/rectangle.hpp"
#include <stdexcept>
#include <iostream>
#include <cmath>
#include "base-types.hpp"

hudilajnen::Rectangle::Rectangle(double width, double height, const point_t &pos, double angle):
    top_{{pos.x - width / 2, pos.y - height / 2},
         {pos.x - width / 2, pos.y + height / 2},
         {pos.x + width / 2, pos.y + height / 2},
         {pos.x + width / 2, pos.y - height / 2}}
{
  if (width <= 0)
  {
    throw std::invalid_argument("Invalid width: rectangle's width can not be less or equal then zero");
  }
  if (height <= 0)
  {
    throw std::invalid_argument("Invalid height: rectangle's width can not be less or equal then zero");
  }
  rotate(angle);
}

double hudilajnen::Rectangle::getArea() const noexcept
{
  return sqrt(pow(top_[0].x - top_[1].x, 2) + pow(top_[0].y - top_[1].y, 2)) *
         sqrt(pow(top_[1].x - top_[2].x, 2) + pow(top_[1].y - top_[2].y, 2));
}

hudilajnen::rectangle_t hudilajnen::Rectangle::getFrameRect() const noexcept
{
  double minX = top_[0].x;
  double maxX = top_[0].x;
  double minY = top_[0].y;
  double maxY = top_[0].y;

  for (size_t i = 1; i < 4; ++i)
  {
    minX = std::min(minX, top_[i].x);
    minY = std::min(minY, top_[i].y);
    maxX = std::max(maxX, top_[i].x);
    maxY = std::max(maxY, top_[i].y);
  }

  return {maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2}};
}

hudilajnen::point_t hudilajnen::Rectangle::getCenter() const noexcept
{
  double maxX = std::max(std::max(top_[0].x, top_[1].x), std::max(top_[2].x, top_[3].x));
  double maxY = std::max(std::max(top_[0].y, top_[1].y), std::max(top_[2].y, top_[3].y));
  double minX = std::min(std::min(top_[0].x, top_[1].x), std::min(top_[2].x, top_[3].x));
  double minY = std::min(std::min(top_[0].y, top_[1].y), std::min(top_[2].y, top_[3].y));

  return {(maxX + minX) / 2, (maxY + minY) / 2};
}

void hudilajnen::Rectangle::move(double x, double y) noexcept
{
  for (size_t i = 0; i < 4; ++i)
  {
    top_[i].x += x;
    top_[i].y += y;
  }
}

void hudilajnen::Rectangle::move(const point_t &pos) noexcept
{
  double dx = pos.x - getCenter().x;
  double dy = pos.y - getCenter().y;

  for (size_t i = 0; i < 4; ++i)
  {
    top_[i].x += dx;
    top_[i].y += dy;
  }
}

void hudilajnen::Rectangle::scale(double k)
{
  if (k <= 0)
  {
    throw std::invalid_argument("Invalid scale coefficient: scale coefficient can not be less or equal then zero");
  }

  hudilajnen::point_t center = getCenter();
  for (size_t i = 0; i < 4; ++i)
  {
    top_[i] = {center.x + (top_[i].x - center.x) * k, center.y + (top_[i].y - center.y) * k};
  }
}

void hudilajnen::Rectangle::rotate(double angle) noexcept
{
  double radianAngle = (angle * M_PI) / 180;
  hudilajnen::point_t center = getCenter();

  for (size_t i = 0; i < 4; ++i)
  {
    double posX = center.x + (top_[i].x - center.x) * cos(radianAngle) - (top_[i].y - center.y) * sin(radianAngle);
    double posY = center.y + (top_[i].x - center.x) * sin(radianAngle) - (top_[i].y - center.y) * cos(radianAngle);
    top_[i] = {posX, posY};
  }

}

void hudilajnen::Rectangle::print() const noexcept
{
  std::cout << "Rectangle (width = " << sqrt(pow(top_[0].x - top_[1].x, 2) + pow(top_[0].y - top_[1].y, 2))
      << ", height = " << sqrt(pow(top_[1].x - top_[2].x, 2) + pow(top_[1].y - top_[2].y, 2)) << ", pos("
      << getCenter().x << ", " << getCenter().y << "))";
}
