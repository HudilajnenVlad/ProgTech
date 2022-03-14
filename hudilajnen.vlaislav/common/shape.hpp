#ifndef HUDILAJNEN_VLADISLAV_SHAPE_HPP
#define HUDILAJNEN_VLADISLAV_SHAPE_HPP

#include <memory>

namespace hudilajnen
{
  struct rectangle_t;
  struct point_t;

  class Shape
  {
  public:
    using ShapeSharedPtr = std::shared_ptr<Shape>;

    virtual ~Shape() = default;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(double x, double y) = 0;

    virtual void move(const point_t &pos) = 0;

    virtual void scale(double k) = 0;

    virtual void rotate(double angle) = 0;

    virtual point_t getCenter() const = 0;

    virtual void print() const = 0;

  };
}

#endif //HUDILAJNEN_VLADISLAV_SHAPE_HPP
