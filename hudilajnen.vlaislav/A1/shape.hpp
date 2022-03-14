#ifndef HUDILAJNEN_VLADISLAV_SHAPE_HPP
#define HUDILAJNEN_VLADISLAV_SHAPE_HPP

struct rectangle_t;
struct point_t;

class Shape
{
public:
  virtual ~Shape() = default;

  virtual double getArea() const = 0;

  virtual rectangle_t getFrameRect() const = 0;

  virtual void move(double x, double y) = 0;

  virtual void move(const point_t &pos) = 0;
};

#endif //HUDILAJNEN_VLADISLAV_SHAPE_HPP
