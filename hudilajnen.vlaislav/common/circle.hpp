#ifndef HUDILAJNEN_VLADISLAV_CIRCLE_HPP
#define HUDILAJNEN_VLADISLAV_CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace hudilajnen
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t &pos);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t &pos) noexcept override;

    void scale(double k) override;

    point_t getCenter() const noexcept override;

    void rotate(double) noexcept override;

    void print() const noexcept override;

  private:
    double radius_;
    point_t pos_;
  };
}

#endif //HUDILAJNEN_VLADISLAV_CIRCLE_HPP
