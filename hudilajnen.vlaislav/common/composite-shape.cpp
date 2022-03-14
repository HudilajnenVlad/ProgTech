#include "composite-shape.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <algorithm>
#include "base-types.hpp"

hudilajnen::CompositeShape::CompositeShape(const ShapeSharedPtr &shape) :
    arrayShape_{std::make_unique<ShapeSharedPtr[]>(1)},
    size_{1}
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Object does not exist");
  }

  arrayShape_[0] = shape;
}

hudilajnen::CompositeShape::CompositeShape(const CompositeShape &compShape) :
    arrayShape_{std::make_unique<ShapeSharedPtr[]>(compShape.size_)},
    size_{compShape.size_}
{
  for (size_t i = 0; i < size_; ++i)
  {
    arrayShape_[i] = compShape.arrayShape_[i];
  }
}

hudilajnen::CompositeShape &hudilajnen::CompositeShape::operator=(const CompositeShape &compShape)
{
  if (this == &compShape)
  {
    return *this;
  }

  size_ = compShape.size_;

  arrayShape_ = std::make_unique<ShapeSharedPtr[]>(compShape.size_);

  for (size_t i = 0; i < size_; ++i)
  {
    arrayShape_[i] = compShape.arrayShape_[i];
  }

  return *this;
}

hudilajnen::Shape::ShapeSharedPtr hudilajnen::CompositeShape::operator[](size_t i)
{
  if (!arrayShape_)
  {
    throw std::invalid_argument("Error! You can not choose empty figure.");
  }

  if (i >= size_)
  {
    throw std::out_of_range("Error. Index is out of Range of Shape Array");
  }
  return arrayShape_[i];
}

const hudilajnen::Shape::ShapeSharedPtr hudilajnen::CompositeShape::operator[](size_t i) const
{
  if (!arrayShape_)
  {
    throw std::invalid_argument("Error! You can not choose empty figure.");
  }

  if (i >= size_)
  {
    throw std::out_of_range("Error. Index is out of Range of Shape Array");
  }
  return arrayShape_[i];
}

double hudilajnen::CompositeShape::getArea() const
{
  if (!arrayShape_)
  {
    return 0;
  }

  double finArea = 0;
  for (size_t i = 0; i < size_; ++i)
  {
    finArea += arrayShape_[i]->getArea();
  }

  return finArea;
}

hudilajnen::rectangle_t hudilajnen::CompositeShape::getFrameRect() const
{
  if (!arrayShape_)
  {
    return hudilajnen::rectangle_t{-1, -1, {-1, -1}};
  }

  hudilajnen::rectangle_t shapeFrameRect = arrayShape_[0]->getFrameRect();
  hudilajnen::point_t shapePosition = arrayShape_[0]->getCenter();

  double minY = shapePosition.y - (shapeFrameRect.height / 2);
  double maxY = shapePosition.y + (shapeFrameRect.height / 2);
  double minX = shapePosition.x - (shapeFrameRect.width / 2);
  double maxX = shapePosition.x + (shapeFrameRect.width / 2);

  for (size_t i = 1; i < size_; ++i)
  {
    shapeFrameRect = arrayShape_[i]->getFrameRect();
    shapePosition = shapeFrameRect.pos;

    minY = std::min(minY, shapePosition.y - (shapeFrameRect.height / 2));
    maxY = std::max(maxY, shapePosition.y + (shapeFrameRect.height / 2));
    minX = std::min(minX, shapePosition.x - (shapeFrameRect.width / 2));
    maxX = std::max(maxX, shapePosition.x + (shapeFrameRect.height / 2));
  }

  double newWidth = maxX - minX;
  double newHeight = maxY - minY;
  hudilajnen::point_t newPosition{minX + (newWidth / 2), minY + (newHeight / 2)};

  return rectangle_t{newWidth, newHeight, newPosition};
}

hudilajnen::point_t hudilajnen::CompositeShape::getCenter() const
{
  return getFrameRect().pos;
}

double hudilajnen::CompositeShape::getSize() const
{
  if (!arrayShape_)
  {
    return 0;
  }

  return size_;
}

void hudilajnen::CompositeShape::move(const hudilajnen::point_t &pos)
{
  if (!arrayShape_)
  {
    return;
  }

  hudilajnen::point_t oldPosition = getCenter();

  double dx = pos.x - oldPosition.x;
  double dy = pos.y - oldPosition.y;

  move(dx, dy);
}

void hudilajnen::CompositeShape::move(double dx, double dy)
{
  if (!arrayShape_)
  {
    return;
  }

  for (size_t i = 0; i < size_; ++i)
  {
    arrayShape_[i]->move(dx, dy);
  }
}

void hudilajnen::CompositeShape::scale(double k)
{
  if (!arrayShape_)
  {
    return;
  }

  if (k <= 0)
  {
    throw std::invalid_argument("Error. Negative coefficient.");
  }
  hudilajnen::point_t oldPosition = getCenter();

  for (size_t i = 0; i < size_; ++i)
  {
    double posX = k * arrayShape_[i]->getCenter().x - (k - 1) * oldPosition.x;
    double posY = k * arrayShape_[i]->getCenter().y - (k - 1) * oldPosition.y;
    arrayShape_[i]->move({posX, posY});
    arrayShape_[i]->scale(k);
  }
}

void hudilajnen::CompositeShape::add(ShapeSharedPtr &shape)
{
  if (!arrayShape_)
  {
    throw std::invalid_argument("Error. You can not add shape to null composite shape.");
  }

  if (!shape)
  {
    throw std::invalid_argument("Error. Shape does not exist.");
  }

  std::unique_ptr<ShapeSharedPtr[]> newArray = std::make_unique<ShapeSharedPtr[]>(size_ + 1);

  for (size_t i = 0; i < size_; ++i)
  {
    newArray[i] = arrayShape_[i];
  }

  newArray[size_] = shape;
  newArray.swap(arrayShape_);
  ++size_;
}

void hudilajnen::CompositeShape::remove(size_t i)
{
  if (!arrayShape_)
  {
    throw std::invalid_argument("Error. You can not remove shape into composite-shape");
  }

  if (i >= size_)
  {
    throw std::out_of_range("Error. Argument" + std::to_string(i) + "is out of size CompShape Array");
  }
  if (size_ == 1)
  {
    throw std::invalid_argument("Error. You can't remove last shape into compositeShape");
  }

  std::unique_ptr<ShapeSharedPtr[]> newArray = std::make_unique<ShapeSharedPtr[]>(size_ - 1);
  for (size_t j = 0; j < size_; ++j)
  {
    if (j == i)
    {
      continue;
    }
    newArray[j] = arrayShape_[j];
  }

  newArray.swap(arrayShape_);
  --size_;

}

void hudilajnen::CompositeShape::rotate(double angle)
{
  if (!arrayShape_)
  {
    std::invalid_argument("Error. You can't rotate null composite-shape");
  }

  double radianAngle = (angle * M_PI) / 180;

  point_t center = getCenter();

  for (size_t i = 0; i < size_; ++i)
  {
    point_t shapeCent = arrayShape_[i]->getCenter();
    double posX = center.x + (shapeCent.x - center.x) * cos(radianAngle) - (shapeCent.y - center.y) * sin(radianAngle);
    double posY = center.y + (shapeCent.x - center.x) * sin(radianAngle) + (shapeCent.y - center.y) * cos(radianAngle);

    arrayShape_[i]->move({posX, posY});
    arrayShape_[i]->rotate(angle);
  }
}

void hudilajnen::CompositeShape::print() const noexcept
{
  std::cout << "Composite-shape consist of ";
  for (size_t i = 0; i < getSize(); ++i)
  {
    arrayShape_[i]->print();
    std::cout << ", \n";
  }
}
