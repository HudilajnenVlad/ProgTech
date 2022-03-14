#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "circle.hpp"
#include "base-types.hpp"

const double eps = 0.000001;

BOOST_AUTO_TEST_SUITE(Circle_CircleConstruct)

  BOOST_AUTO_TEST_CASE(Circle_PositiveNumberAsRadius_noException)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_NO_THROW(hudilajnen::Circle(radius, position));
  }

  BOOST_AUTO_TEST_CASE(Circle_NegativeNumberAsRadius_ThrownException)
  {
    double radius = -69.42;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_THROW(hudilajnen::Circle(radius, position), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Circle_ZeroNumberAsRadius_ThrownException)
  {
    double radius = 0.0;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_THROW(hudilajnen::Circle(radius, position), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Circle_Move_AtPoint)

  BOOST_AUTO_TEST_CASE(Move_RectanglePositiveCoordsAsPoint_EqualCircleCenterAndMovingPoint)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);

    hudilajnen::point_t newPosition{14.0, 26.0};
    circle.move(newPosition);
    BOOST_CHECK_EQUAL(circle.getCenter().x, newPosition.x);
    BOOST_CHECK_EQUAL(circle.getCenter().y, newPosition.y);
  }

  BOOST_AUTO_TEST_CASE(Move_CircleRectangleFrame_constantRectangleFrameAfterMovingAtPoint)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);

    hudilajnen::point_t newPosition{14.0, 26.0};
    hudilajnen::rectangle_t startFrameRect = circle.getFrameRect();
    circle.move(newPosition);
    BOOST_CHECK_EQUAL(circle.getFrameRect().width, startFrameRect.width);
    BOOST_CHECK_EQUAL(circle.getFrameRect().height, startFrameRect.height);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.x, newPosition.x);
    BOOST_CHECK_EQUAL(circle.getFrameRect().pos.y, newPosition.y);
  }

  BOOST_AUTO_TEST_CASE(Move_PositiveNumberAtMovingPointAndCircleRectangleFrame_constantArea)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);

    hudilajnen::point_t newPosition{14.0, 26.0};
    double area = circle.getArea();
    circle.move(newPosition);
    BOOST_CHECK_EQUAL(circle.getArea(), area);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Circle_Move_ToCoords)

  BOOST_AUTO_TEST_CASE(Move_PositiveDeltaCoords_EqualCircleCenterAndPointAfterMoving)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);

    double dx = 8.4;
    double dy = 9.1;
    circle.move(dx, dy);
    BOOST_CHECK_CLOSE(circle.getCenter().x, position.x + dx, eps);
    BOOST_CHECK_CLOSE(circle.getCenter().y, position.y + dy, eps);
  }

  BOOST_AUTO_TEST_CASE(Move_CircleRectangleFrame_constantRectangleFrameAfterMovingByCoords)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);

    double dx = 8.4;
    double dy = 9.1;
    hudilajnen::rectangle_t startFrameRect = circle.getFrameRect();
    circle.move(dx, dy);
    BOOST_CHECK_EQUAL(circle.getFrameRect().width, startFrameRect.width);
    BOOST_CHECK_EQUAL(circle.getFrameRect().height, startFrameRect.height);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.x, position.x + dx, eps);
    BOOST_CHECK_CLOSE(circle.getFrameRect().pos.y, position.y + dy, eps);
  }

  BOOST_AUTO_TEST_CASE(Move_CircleArea_ConstantAreaAfterMovingByCoords)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);

    double dx = 8.4;
    double dy = 9.1;
    double area = circle.getArea();
    circle.move(dx, dy);
    BOOST_CHECK_EQUAL(circle.getArea(), area);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Circle_Scale)

  BOOST_AUTO_TEST_CASE(Scale_PositiveNumberAsCoefficiente_noException)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);
    double k = 3.0;
    BOOST_CHECK_NO_THROW(circle.scale(k));
  }

  BOOST_AUTO_TEST_CASE(Scale_NegetiveNumberAsCoefficiente_ThrowException)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);
    double k = -3.0;
    BOOST_CHECK_THROW(circle.scale(k), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_ZeroNumberAsCoefficiente_ThrowException)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);
    double k = 0.0;
    BOOST_CHECK_THROW(circle.scale(k), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Circle_Scale)

  BOOST_AUTO_TEST_CASE(Scale_PositiveCoefficient_SquareAreaChange)
  {
    double radius = 69.42;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Circle circle(radius, position);
    double area = circle.getArea();
    double k = 3.0;
    circle.scale(k);
    BOOST_CHECK_CLOSE(circle.getArea(), area * k * k, eps);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Circle_Rotate)

BOOST_AUTO_TEST_CASE(Rotate_AnyAngle_ConstantArea)
  {
    double radius = 5;
    hudilajnen::point_t position{4, 7};
    hudilajnen::Circle circle(radius, position);
    double oldArea = circle.getArea();

    circle.rotate(42);
    BOOST_CHECK_CLOSE(oldArea, circle.getArea(), eps);
  }

  BOOST_AUTO_TEST_CASE(Rotate_AnyAngle_ConstantPosition)
  {
    double radius = 60;
    hudilajnen::point_t position{2, 3};
    hudilajnen::Circle circle(radius, position);

    circle.rotate(42);
    BOOST_CHECK_CLOSE(position.x, circle.getCenter().x, eps);
    BOOST_CHECK_CLOSE(position.y, circle.getCenter().y, eps);
  }

BOOST_AUTO_TEST_SUITE_END();
