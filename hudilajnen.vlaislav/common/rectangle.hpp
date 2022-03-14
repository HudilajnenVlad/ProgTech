#ifndef HUDILAJNEN_VLADISLAV_RECTANGLE_HPP
#define HUDILAJNEN_VLADISLAV_RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace hudilajnen
{
  class Rectangle : public Shape
  {
  public:

    Rectangle(double width, double height, const point_t &pos, double angle = 0);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t &pos) noexcept override;

    void scale(double k) override;

    point_t getCenter() const noexcept override;

    void rotate(double angle) noexcept override;

    void print() const noexcept override;

  private:
    point_t top_[4];
  };
}
#endif //HUDILAJNEN_VLADISLAV_RECTANGLE_HPP
