#include <iostream>
#include <stdexcept>

#include "../common/composite-shape.hpp"
#include "../common/rectangle.hpp"
#include "../common/circle.hpp"
#include "../common/matrix.hpp"


int main(int, char **)
{

  const int width = 6;
  const int height = 5;
  const hudilajnen::point_t pos = {3, 4};
  const hudilajnen::point_t pos2 = {10, 15};
  const hudilajnen::point_t pos3 = {0, 0};
  const int dx = 6;
  const int dy = 7;
  const int rad = 5;
  const double k = 3;
  const double angle = 90;
  std::shared_ptr<hudilajnen::Shape> shape = nullptr;

  std::cout << "Create rectangle with width=" << width << ", height=" << height << " at point (" << pos.x << ","
      << pos.y << ").\n";
  try
  {
    shape = std::make_shared<hudilajnen::Rectangle>(hudilajnen::Rectangle{width, height, pos});
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  shape->print();

  std::cout << ".\n\nMoving start rectangle at point (" << pos2.x << ',' << pos2.y << ")\n";
  shape->move(pos2);
  shape->print();

  std::cout << "\n\nMove the starting rectangle to " << dx << " and " << dy << " on the x and y axes\n";
  shape->move(dx, dy);
  shape->print();

  std::cout << "\n\n Scale the starting rectangle on" << k << '\n';
  try
  {
    shape->scale(k);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  shape->print();

  std::cout << "\n Rotate starting rectangle on " << angle << " angels\n";
  try
  {
    shape->rotate(angle);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  shape->print();

  std::cout << "\n\nCreate Circle with radius=" << rad << " at point (" << pos.x << ',' << pos.y << ").\n";
  try
  {
    shape = std::make_shared<hudilajnen::Circle>(hudilajnen::Circle{rad, pos});
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  shape->print();

  std::cout << ".\n\nMoving start circle at point (" << pos2.x << ',' << pos2.y << ")\n";
  shape->move(pos2);
  shape->print();

  std::cout << "\n\nMove the starting circle to " << dx << " and " << dy << " on the x and y axes\n";
  shape->move(dx, dy);
  shape->print();

  std::cout << "\n\n Scale the starting circle on" << k << '\n';
  try
  {
    shape->scale(k);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  shape->print();

  std::cout << "\n Rotate starting circle on " << angle << " angels\n";
  try
  {
    shape->rotate(angle);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  shape->print();


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
  compShape->print();

  std::cout << "\n\nCreate Circle with radius=" << rad << " at point (" << pos.x << ',' << pos.y << ")."
      << "Add this Circle in composite Shape\n";
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
  compShape->print();

  std::cout << ".\n\nMoving composite Shape at point (" << pos3.x << ',' << pos3.y << ")\n";
  compShape->move(pos3);
  compShape->print();

  std::cout << ".\n\nMoving composite Shape by Coords (" << dx << ',' << dy << ")\n";
  compShape->move(dx, dy);
  compShape->print();

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
  compShape->print();

  std::cout << "In composite shape " << compShape->getSize() << "shapes. Remove first one";
  try
  {
    compShape->remove(1);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  catch (const std::out_of_range &err)
  {
    std::cerr << err.what();
    return 1;
  }
  compShape->print();
  std::cout << "\n Rotate compositeShape on " << angle << " angels\n";
  try
  {
    compShape->rotate(angle);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  compShape->print();

  std::cout << "Create matrix\n";
  hudilajnen::Matrix matrix;

  std::cout << "Add circle in matrix\n";
  try
  {
    std::shared_ptr<hudilajnen::Shape> circle = std::make_shared<hudilajnen::Circle>(rad, pos2);
    circle->print();
    matrix.add(circle);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  matrix.printMatrix();

  std::cout << "\nAdd rectangle in matrix\n";
  try
  {
    std::shared_ptr<hudilajnen::Shape> rect = std::make_shared<hudilajnen::Rectangle>(width, height, pos2);
    rect->print();
    matrix.add(rect);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  matrix.printMatrix();

  std::cout << "Add rectangle not overlap a circle in matrix\n";
  try
  {
    std::shared_ptr<hudilajnen::Shape> rect = std::make_shared<hudilajnen::Rectangle>(width, height, pos);
    rect->print();
    matrix.add(rect);
  }
  catch (const std::invalid_argument &err)
  {
    std::cerr << err.what();
    return 1;
  }
  matrix.printMatrix();

  std::cout << "\nDisplay information about each element of the matrix\n";
  try
  {
    matrix[0][0]->print();
    std::cout << '\n';
    matrix[0][1]->print();
    std::cout << '\n';
    matrix[1][0]->print();
  }
  catch (const std::out_of_range &err)
  {
    std::cout << err.what();
    return 1;
  }
  catch (const std::logic_error &err)
  {
    std::cout << err.what();
    return 1;
  }

  return 0;
}
