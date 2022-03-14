#include "matrix.hpp"
#include <memory>
#include <stdexcept>
#include <iostream>
#include "composite-shape.hpp"
#include "base-types.hpp"

hudilajnen::Matrix::Layer::Layer(hudilajnen::Shape::ShapeSharedPtr *firstShape, size_t sizeOfLayer) noexcept:
    layer_{firstShape},
    size_(sizeOfLayer)
{}

hudilajnen::Shape::ShapeSharedPtr hudilajnen::Matrix::Layer::operator[](size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("Error. Index is out of range of layer\n");
  }

  return layer_[index];
}

const hudilajnen::Shape::ShapeSharedPtr hudilajnen::Matrix::Layer::operator[](size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("Error. Index is out of range of layer\n");
  }

  return layer_[index];
}

hudilajnen::Matrix::Matrix() noexcept:
    rows_{0},
    columns_{0},
    shapeInLayer_{nullptr},
    shapeInMatrix_{nullptr}
{}

hudilajnen::Matrix::Matrix(const Matrix &otherMatrix) noexcept:
    rows_{otherMatrix.rows_},
    columns_{otherMatrix.columns_},
    shapeInLayer_{std::make_unique<size_t[]>(rows_)},
    shapeInMatrix_{std::make_unique<hudilajnen::Shape::ShapeSharedPtr[]>(rows_ * columns_)}
{
  for (size_t i = 0; i < rows_; ++i)
  {
    shapeInLayer_[i] = otherMatrix.shapeInLayer_[i];
  }

  for (size_t i = 0; i < rows_ * columns_; ++i)
  {
    shapeInMatrix_[i] = otherMatrix.shapeInMatrix_[i];
  }
}

hudilajnen::Matrix &hudilajnen::Matrix::operator=(const hudilajnen::Matrix &otherMatrix) noexcept
{
  if (this == &otherMatrix)
  {
    return *this;
  }

  rows_ = otherMatrix.rows_;
  columns_ = otherMatrix.columns_;

  shapeInMatrix_ = std::make_unique<hudilajnen::Shape::ShapeSharedPtr[]>(rows_ * columns_);
  for (size_t i = 0; i < rows_; ++i)
  {
    shapeInLayer_[i] = otherMatrix.shapeInLayer_[i];
  }

  for (size_t i = 0; i < rows_; ++i)
  {
    for (size_t j = 0; j < shapeInLayer_[i]; ++j)
    {
      shapeInMatrix_[j] = otherMatrix.shapeInMatrix_[j];
    }
  }

  return *this;
}

hudilajnen::Matrix::Matrix(Matrix &&otherMatrix) noexcept:
    rows_{otherMatrix.rows_},
    columns_{otherMatrix.columns_},
    shapeInLayer_{std::move(otherMatrix.shapeInLayer_)},
    shapeInMatrix_{std::move(otherMatrix.shapeInMatrix_)}
{
  otherMatrix.rows_ = 0;
  otherMatrix.columns_ = 0;
}

hudilajnen::Matrix &hudilajnen::Matrix::operator=(Matrix &&otherMatrix) noexcept
{
  if (this == &otherMatrix)
  {
    return *this;
  }

  rows_ = otherMatrix.rows_;
  otherMatrix.rows_ = 0;

  columns_ = otherMatrix.columns_;
  otherMatrix.columns_ = 0;

  shapeInLayer_ = std::move(otherMatrix.shapeInLayer_);
  shapeInMatrix_ = std::move(otherMatrix.shapeInMatrix_);

  return *this;
}

hudilajnen::Matrix::Layer hudilajnen::Matrix::operator[](size_t index)
{
  if (!shapeInMatrix_)
  {
    throw std::logic_error("Error. Matrix does not exist\n");
  }
  if (index >= rows_)
  {
    throw std::out_of_range("Error. Index is out of range of rows in matrix\n");
  }

  return Layer(&shapeInMatrix_[index * columns_], shapeInLayer_[index]);
}

const hudilajnen::Matrix::Layer hudilajnen::Matrix::operator[](size_t index) const
{
  if (!shapeInMatrix_)
  {
    throw std::logic_error("Error. Matrix does not exist\n");
  }
  if (index >= rows_)
  {
    throw std::out_of_range("Error. Index is out of range of rows in matrix\n");
  }

  return Layer(&shapeInMatrix_[index * columns_], shapeInLayer_[index]);
}

void hudilajnen::Matrix::add(Shape::ShapeSharedPtr &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Error. Added shape is nullptr.\n");
  }

  size_t shapeLayer = getNumberOfLayerForShape(shape);

  if (shapeLayer >= rows_)
  {
    extendMatrixPerRows();
    shapeInMatrix_[shapeLayer * columns_] = shape;
    shapeInLayer_[rows_ - 1] = 1;
  }
  else if (shapeInLayer_[shapeLayer] >= columns_)
  {
    extendMatrixPerColumns();
    shapeInMatrix_[shapeLayer * columns_ + shapeInLayer_[shapeLayer]] = shape;
    ++shapeInLayer_[shapeLayer];
  }
  else
  {
    shapeInMatrix_[shapeLayer * columns_ + shapeInLayer_[shapeLayer]] = shape;
    ++shapeInLayer_[shapeLayer];
  }
}

size_t hudilajnen::Matrix::getCountOfLayer() const noexcept
{
  return rows_;
}

void hudilajnen::Matrix::printMatrix() const noexcept
{
  std::cout << "\nMatrix consists of rows = " << rows_ << " and columns = " << columns_ << ". Shape in layers:";
  for (size_t i = 0; i < rows_; ++i)
  {
    std::cout << "\nLayer" << i << ": \n";
    for (size_t j = 0; j < shapeInLayer_[i]; ++j)
    {
      shapeInMatrix_[i * columns_ + j]->print();
      std::cout << '\n';
    }
  }
}

size_t hudilajnen::Matrix::getNumberOfShapesOnLayer(size_t layer) const
{
  if (layer >= rows_)
  {
    throw std::invalid_argument("Error. This layer doesn't exist.");
  }

  return shapeInLayer_[layer];
}

size_t hudilajnen::Matrix::getCountOfShape() const noexcept
{
  if (!shapeInMatrix_)
  {
    return 0;
  }

  size_t countOfShape = 0;
  for (size_t i = 0; i < rows_; ++i)
  {
    countOfShape += shapeInLayer_[i];
  }
  return countOfShape;
}

size_t hudilajnen::Matrix::getNumberOfLayerForShape(Shape::ShapeSharedPtr &shape) const
{
  size_t shapeLayer = 0;
  for (size_t i = 0; i < rows_; ++i)
  {
    for (size_t j = 0; j < shapeInLayer_[i]; ++j)
    {
      if (shapeInMatrix_[columns_ * i + j] == shape)
      {
        throw std::invalid_argument("Error. This shape now in matrix.");
      }
      if (implementationDetails::isOverlap(shape->getFrameRect(), shapeInMatrix_[columns_ * i + j]->getFrameRect()))
      {
        shapeLayer = i + 1;
      }
    }
  }

  return shapeLayer;
}

void hudilajnen::Matrix::extendMatrixPerRows() noexcept
{
  if (columns_ == 0)
  {
    columns_ = 1;
  }

  std::unique_ptr<Shape::ShapeSharedPtr[]> tmpArrayShape = {nullptr};
  tmpArrayShape.swap(shapeInMatrix_);

  shapeInMatrix_ = std::make_unique<Shape::ShapeSharedPtr[]>((rows_ + 1) * columns_);

  std::unique_ptr<size_t[]> tmpArraySize = {nullptr};
  tmpArraySize.swap(shapeInLayer_);

  shapeInLayer_ = std::make_unique<size_t[]>(rows_ + 1);

  for (size_t i = 0; i < rows_; ++i)
  {
    shapeInLayer_[i] = tmpArraySize[i];
  }
  for (size_t i = 0; i < rows_; ++i)
  {
    for (size_t j = 0; j < shapeInLayer_[i]; ++j)
    {
      shapeInMatrix_[i * columns_ + j] = tmpArrayShape[i * columns_ + j];
    }
  }
  rows_++;
}

void hudilajnen::Matrix::extendMatrixPerColumns() noexcept
{
  ++columns_;

  std::unique_ptr<Shape::ShapeSharedPtr[]> tmpArrayShape = {nullptr};
  tmpArrayShape.swap(shapeInMatrix_);
  shapeInMatrix_ = std::make_unique<Shape::ShapeSharedPtr[]>(rows_ * columns_);

  for (size_t i = 0; i < rows_; ++i)
  {
    for (size_t j = 0; j < shapeInLayer_[i]; ++j)
    {
      shapeInMatrix_[i * columns_ + j] = tmpArrayShape[i * (columns_ - 1) + j];
    }
  }
}
