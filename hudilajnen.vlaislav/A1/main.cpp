#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

void printRectangle(const Rectangle &rect);

void printCircle(const Circle &circle);

int main(int, char **)
{
  const int width = 6;
  const int height = 5;
  const point_t pos = {3, 4};
  const point_t pos2 = {6, 8};
  const int dx = 6;
  const int dy = 7;
  const int rad = 5;

  std::cout << "Create rectangle with width=" << width << ", height=" << height << " at point (" << pos.x << ","
      << pos.y << ").\n";
  Rectangle rect = {width, height, pos};
  printRectangle(rect);

  std::cout << ".\n\nMoving start rectangle at point (" << pos2.x << ',' << pos2.y << ")\n";
  rect.move(pos2);
  printRectangle(rect);

  std::cout << "\n\nMove the starting rectangle to " << dx << " and " << dy << " on the x and y axes\n";
  rect.move(dx, dy);
  printRectangle(rect);

  std::cout << "\n\nCreate Circle with radius=" << rad << " at point (" << pos.x << ',' << pos.y << ").\n";
  Circle circle = {rad, pos};
  printCircle(circle);

  std::cout << ".\n\nMoving start circle at point (" << pos2.x << ',' << pos2.y << ")\n";
  circle.move(pos2);
  printCircle(circle);

  std::cout << "\n\nMove the starting circle to " << dx << " and " << dy << " on the x and y axes\n";
  circle.move(dx, dy);
  printCircle(circle);

  return 0;
}

void printRectangle(const Rectangle &rect)
{
  std::cout << "Area of Rectangle = " << rect.getArea()
      << "\nposition of FrameRect (" << rect.getFrameRect().pos.x << ','
      << rect.getFrameRect().pos.y << ")\n"
      << "width of FrameRect = " << rect.getFrameRect().width
      << "\nheight of FrameRect = " << rect.getFrameRect().height;
}

void printCircle(const Circle &circle)
{
  std::cout << "Area of start Circle = " << circle.getArea()
      << "\nposition of FrameRect (" << circle.getFrameRect().pos.x << ','
      << circle.getFrameRect().pos.y << ")\n"
      << "width of FrameRect = " << circle.getFrameRect().width
      << "\nheight of FrameRect = " << circle.getFrameRect().height;
}
