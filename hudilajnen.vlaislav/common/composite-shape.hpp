#ifndef COMPOSITESHAPE_HPP
#define COMPOSITESHAPE_HPP

#include <memory>
#include "shape.hpp"
#include "base-types.hpp"

namespace hudilajnen
{
  class CompositeShape : public Shape
  {
  public:

    CompositeShape(const ShapeSharedPtr &shape);

    CompositeShape(const CompositeShape &compShape);

    CompositeShape(CompositeShape &&compShape) = default;

    ~CompositeShape() = default;

    CompositeShape &operator=(const CompositeShape &compShape);

    CompositeShape &operator=(CompositeShape &&compShape) = default;

    ShapeSharedPtr operator[](size_t i);

    const ShapeSharedPtr operator[](size_t i) const;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    point_t getCenter() const override;

    double getSize() const;

    void move(const point_t &pos) override;

    void move(double dx, double dy) override;

    void scale(double k) override;

    void add(ShapeSharedPtr &shape);

    void remove(size_t i);

    void rotate(double angle) override;

    void print() const noexcept override;

  private:
    std::unique_ptr<ShapeSharedPtr[]> arrayShape_;
    size_t size_;
  };
}


#endif //COMPOSITESHAPE_HPP
