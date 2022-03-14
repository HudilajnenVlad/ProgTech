#ifndef HUDILAJNEN_VLADISLAV_RECTANGLE_HPP
#define HUDILAJNEN_VLADISLAV_RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(double width, double height, const point_t &pos);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(double x, double y) override;


  void move(const point_t &pos) override;

private:
  rectangle_t rectangle_;
};

#endif //HUDILAJNEN_VLADISLAV_RECTANGLE_HPP
