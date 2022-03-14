#include <iostream>
#include <stdexcept>

#include "../common/composite-shape.hpp"
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"

void printRectangle(const hudilajnen::rectangle_t &rect, double area);

void printCircle(const hudilajnen::rectangle_t &circleFrameRect, double area);

void printCompositeShape(const hudilajnen::rectangle_t &compShapeFrameRect, double area, size_t size);

int main(int, char **)
{
  const int width = 6;
  const int height = 5;
  const hudilajnen::point_t pos = {3, 4};
  const hudilajnen::point_t pos2 = {6, 8};
  const hudilajnen::point_t pos3 = {0, 0};
  const int dx = 6;
  const int dy = 7;
  const int rad = 5;
  const double k = 3;
  hudilajnen::Shape *shape = nullptr;

  std::cout << "Create rectangle with width=" << width << ", height=" << height << " at point (" << pos.x << ","
      << pos.y << ").\n";
  try
  {
    shape = new hudilajnen::Rectangle{width, height, pos};
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  printRectangle(shape->getFrameRect(), shape->getArea());

  std::cout << ".\n\nMoving start rectangle at point (" << pos2.x << ',' << pos2.y << ")\n";
  shape->move(pos2);
  printRectangle(shape->getFrameRect(), shape->getArea());

  std::cout << "\n\nMove the starting rectangle to " << dx << " and " << dy << " on the x and y axes\n";
  shape->move(dx, dy);
  printRectangle(shape->getFrameRect(), shape->getArea());

  std::cout << "\n\n Scale the starting rectangle on" << k << '\n';
  try
  {
    shape->scale(k);
  }
  catch (const std::invalid_argument &err)
  {
    delete shape;
    std::cerr << err.what();
    return 1;
  }
  printRectangle(shape->getFrameRect(), shape->getArea());

  std::cout << "\n\nCreate Circle with radius=" << rad << " at point (" << pos.x << ',' << pos.y << ").\n";
  try
  {
    shape = new hudilajnen::Circle{rad, pos};
  }
  catch (const std::invalid_argument &err)
  {
    delete shape;
    std::cerr << err.what();
    return 1;
  }
  printCircle(shape->getFrameRect(), shape->getArea());

  std::cout << ".\n\nMoving start circle at point (" << pos2.x << ',' << pos2.y << ")\n";
  shape->move(pos2);
  printCircle(shape->getFrameRect(), shape->getArea());

  std::cout << "\n\nMove the starting circle to " << dx << " and " << dy << " on the x and y axes\n";
  shape->move(dx, dy);
  printCircle(shape->getFrameRect(), shape->getArea());

  std::cout << "\n\n Scale the starting circle on" << k << '\n';
  try
  {
    shape->scale(k);
  }
  catch (const std::invalid_argument &err)
  {
    delete shape;
    std::cerr << err.what();
    return 1;
  }
  printCircle(shape->getFrameRect(), shape->getArea());
  delete shape;


  std::unique_ptr<hudilajnen::CompositeShape> compShape = nullptr;
  hudilajnen::Rectangle rectangle{width, height, pos};
  std::cout << "Created composite shape with rectangle as parameter (width=" << width << ", height=" << height
      << " at point (" << pos.x << "," << pos.y << ").\n";
  try
  {
    compShape = std::make_unique<hudilajnen::CompositeShape>(std::make_shared<hudilajnen::Rectangle>(rectangle));
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  printCompositeShape(compShape->getFrameRect(), compShape->getArea(), compShape->getSize());

  std::cout << "\n\nCreate Circle with radius=" << rad << " at point (" << pos.x << ',' << pos.y << ")."
    <<"Add this Circle in composite Shape\n";
  try
  {
    std::shared_ptr<hudilajnen::Shape> circle = std::make_shared<hudilajnen::Circle>(rad, pos2);
    compShape->add(circle);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  printCompositeShape(compShape->getFrameRect(), compShape->getArea(), compShape->getSize());

  std::cout << ".\n\nMoving composite Shape at point (" << pos3.x << ',' << pos3.y << ")\n";
  compShape->move(pos3);
  printCompositeShape(compShape->getFrameRect(), compShape->getArea(), compShape->getSize());

  std::cout << ".\n\nMoving composite Shape by Coords (" << dx << ',' << dy << ")\n";
  compShape->move(dx, dy);
  printCompositeShape(compShape->getFrameRect(), compShape->getArea(), compShape->getSize());

  std::cout << "\n\n Scale the composite Shape on" << k << '\n';
  try
  {
    compShape->scale(k);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  printCompositeShape(compShape->getFrameRect(), compShape->getArea(), compShape->getSize());

  std::cout<<"In composite shape "<<compShape->getSize()<<"shapes. Remove first one";
  try
  {
    compShape->remove(1);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  printCompositeShape(compShape->getFrameRect(), compShape->getArea(), compShape->getSize());


  return 0;
}

void printRectangle(const hudilajnen::rectangle_t &rect, double area)
{
  std::cout << "Area of Rectangle = " << area
      << "\nposition of FrameRect (" << rect.pos.x << ','
      << rect.pos.y << ")\n"
      << "width of FrameRect = " << rect.width
      << "\nheight of FrameRect = " << rect.height;
}

void printCircle(const hudilajnen::rectangle_t &circleFrameRect, double area)
{
  std::cout << "Area of start Circle = " << area
      << "\nposition of FrameRect (" << circleFrameRect.pos.x << ','
      << circleFrameRect.pos.y << ")\n"
      << "width of FrameRect = " << circleFrameRect.width
      << "\nheight of FrameRect = " << circleFrameRect.height;
}

void printCompositeShape(const hudilajnen::rectangle_t &compShapeFrameRect, double area, size_t size)
{
  std::cout <<"Composite shape included " <<size<<"shapes. "
      << "Area of composite shape = " << area
      << "\nposition of FrameRect (" << compShapeFrameRect.pos.x << ','
      << compShapeFrameRect.pos.y << ")\n"
      << "width of FrameRect = " << compShapeFrameRect.width
      << "\nheight of FrameRect = " << compShapeFrameRect.height;
}
