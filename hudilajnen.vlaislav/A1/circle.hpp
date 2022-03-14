#ifndef HUDILAJNEN_VLADISLAV_CIRCLE_HPP
#define HUDILAJNEN_VLADISLAV_CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Circle: public Shape
{
public:
  Circle(double radius, const point_t &pos);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(double x, double y) override;

  void move(const point_t &pos) override;

private:
  double radius_;
  point_t pos_;
};

#endif //HUDILAJNEN_VLADISLAV_CIRCLE_HPP
