#ifndef SPBSPU_LABS_2020_904_3_MATRIX_HPP
#define SPBSPU_LABS_2020_904_3_MATRIX_HPP

#include <memory>
#include "composite-shape.hpp"
#include "shape.hpp"
#include "base-types.hpp"

namespace hudilajnen
{

  class Matrix
  {
  public:

    class Layer
    {
    public:

      const Shape::ShapeSharedPtr operator[](size_t index) const;

      Shape::ShapeSharedPtr operator[](size_t index);

    private:
      friend class Matrix;

      Shape::ShapeSharedPtr *layer_;
      size_t size_;

      Layer(Shape::ShapeSharedPtr *firstShape, size_t sizeOfLayer) noexcept;
    };

    Matrix() noexcept;

    Matrix(const Matrix &otherMatrix) noexcept;

    Matrix(Matrix &&otherMatrix) noexcept;

    Matrix &operator=(const Matrix &otherMatrix) noexcept;

    Matrix &operator=(Matrix &&otherMatrix) noexcept;

    Layer operator[](size_t index);

    const Layer operator[](size_t index) const;

    void add(Shape::ShapeSharedPtr &shape);

    size_t getCountOfLayer() const noexcept;

    size_t getCountOfShape() const noexcept;

    size_t getNumberOfShapesOnLayer(size_t layer) const;

    void printMatrix() const noexcept;

  private:
    size_t rows_;
    size_t columns_;
    std::unique_ptr<size_t[]> shapeInLayer_;
    std::unique_ptr<Shape::ShapeSharedPtr[]> shapeInMatrix_;

    void extendMatrixPerRows() noexcept;

    void extendMatrixPerColumns() noexcept;

    size_t getNumberOfLayerForShape(Shape::ShapeSharedPtr& shape) const;
  };

}
#endif //SPBSPU_LABS_2020_904_3_MATRIX_HPP
