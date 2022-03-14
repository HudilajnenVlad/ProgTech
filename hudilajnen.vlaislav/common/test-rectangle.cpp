#include <stdexcept>
#include <boost/test/unit_test.hpp>
#include "rectangle.hpp"
#include "base-types.hpp"

const double eps = 0.000001;

BOOST_AUTO_TEST_SUITE(Rectangle_RectangleConstruct)

  BOOST_AUTO_TEST_CASE(Rectangle_PositiveNumberAsWidthAndHeight_noException)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_NO_THROW(hudilajnen::Rectangle(width, height, position));
  }

  BOOST_AUTO_TEST_CASE(Rectangle_NegativeNumberAsWidth_ThrownException)
  {
    double width = -69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_THROW(hudilajnen::Rectangle rectangle(width, height, position), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_NegativeNumberAsHeight_ThrownException)
  {
    double width = 69.42;
    double height = -13.3;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_THROW(hudilajnen::Rectangle rectangle(width, height, position), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_ZeroNumberAsWidth_ThrownException)
  {
    double width = 0.0;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_THROW(hudilajnen::Rectangle rectangle(width, height, position), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Rectangle_ZeroNumberAsHeight_ThrownException)
  {
    double width = 69.42;
    double height = 0.0;
    hudilajnen::point_t position{1.4, 2.6};
    BOOST_CHECK_THROW(hudilajnen::Rectangle rectangle(width, height, position), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE(Rectangle_Move_AtPoint)

  BOOST_AUTO_TEST_CASE(Move_RectanglePositiveCoords_EqualCoordsAfterMovingAndMovingPoint)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);

    hudilajnen::point_t newPosition{14.0, 26.0};
    rectangle.move(newPosition);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, newPosition.x, eps);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, newPosition.y, eps);
  }

  BOOST_AUTO_TEST_CASE(Move_RectangleParametrs_ConstantFrameRectangleParametrsStartAndAfterMovingAtPoint)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);

    hudilajnen::point_t newPosition{14.0, 26.0};
    hudilajnen::rectangle_t startRect = rectangle.getFrameRect();
    rectangle.move(newPosition);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, startRect.width, eps);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, startRect.height, eps);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, newPosition.x, eps);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, newPosition.y, eps);

  }

  BOOST_AUTO_TEST_CASE(Move_RectangleArea_ConstanRectangleAreaAfterMovingAtPoint)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);

    hudilajnen::point_t newPosition{14.0, 26.0};
    double area = rectangle.getArea();
    rectangle.move(newPosition);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area, eps);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Rectangle_Move_ToCoords)

  BOOST_AUTO_TEST_CASE(Move_PositiveDeltaCoords_EqualRectangleCenterAfterMovingAndChangedCoords)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);

    double dx = 8.4;
    double dy = 9.1;
    rectangle.move(dx, dy);
    BOOST_CHECK_CLOSE(rectangle.getCenter().x, position.x + dx, eps);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, position.y + dy, eps);
  }

  BOOST_AUTO_TEST_CASE(Move_RectangleParametrs_ConstantFrameRectangleParametrsAfterMovingToCoords)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);

    double dx = 8.4;
    double dy = 9.1;
    hudilajnen::rectangle_t startRect = rectangle.getFrameRect();
    rectangle.move(dx, dy);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().width, startRect.width, eps);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().height, startRect.height, eps);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.x, position.x + dx, eps);
    BOOST_CHECK_CLOSE(rectangle.getFrameRect().pos.y, position.y + dy, eps);
  }

  BOOST_AUTO_TEST_CASE(Move_RectangleArea_ConstantRectangleParametrsAfterMovingToCoords)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);

    double dx = 8.54;
    double dy = 9.1;
    double area = rectangle.getArea();
    rectangle.move(dx, dy);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area, eps);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Rectangle_Scale)

  BOOST_AUTO_TEST_CASE(Scale_PositiveNumberAsCoefficient_noException)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);
    double k = 3.0;
    BOOST_CHECK_NO_THROW(rectangle.scale(k));
  }

  BOOST_AUTO_TEST_CASE(Scale_NegativeNumberAsCoefficient_ThrownException)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);
    double k = -3.0;
    BOOST_CHECK_THROW(rectangle.scale(k), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(Scale_ZeroNumberAsCoefficient_ThrownException)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);
    double k = 0.0;
    BOOST_CHECK_THROW(rectangle.scale(k), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Rectangle_Scale)

  BOOST_AUTO_TEST_CASE(Scale_PositiveNumberAsCoefficient_SquareChangeInArea)
  {
    double width = 69.42;
    double height = 13.3;
    hudilajnen::point_t position{1.4, 2.6};
    hudilajnen::Rectangle rectangle(width, height, position);
    double area = rectangle.getArea();
    double k = 3.0;
    rectangle.scale(k);
    BOOST_CHECK_CLOSE(rectangle.getArea(), area * k * k, eps);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Rectangle_Rotate)

  BOOST_AUTO_TEST_CASE(Rotate_Angle_ConstantPosition)
  {
    double width = 31;
    double height = 27;
    double angle = 90;
    hudilajnen::point_t position{2, 2};
    hudilajnen::Rectangle rectangle(width, height, position);
    rectangle.rotate(angle);


    BOOST_CHECK_CLOSE(rectangle.getCenter().x, position.x, eps);
    BOOST_CHECK_CLOSE(rectangle.getCenter().y, position.y, eps);
  }

  BOOST_AUTO_TEST_CASE(Rotate_Angle_ConstantArea)
  {
    double width = 2;
    double height = 4;
    double angle = 42;
    hudilajnen::point_t pos{31, 22};
    hudilajnen::Rectangle rect(width, height, pos);
    double oldArea = rect.getArea();

    rect.rotate(angle);

    BOOST_CHECK_CLOSE(rect.getArea(), oldArea, eps);
  }

  BOOST_AUTO_TEST_CASE(Rotate_WideAngle_ConstantFrameRect)
  {
    double width = 8;
    double height = 9;
    double angle = 180;
    hudilajnen::point_t pos{0, 0};
    hudilajnen::Rectangle rect(width, height, pos);
    hudilajnen::rectangle_t frameRect = rect.getFrameRect();

    rect.rotate(angle);

    BOOST_CHECK_CLOSE(rect.getFrameRect().width, frameRect.width, eps);
    BOOST_CHECK_CLOSE(rect.getFrameRect().height, frameRect.height, eps);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.x, frameRect.pos.x, eps);
    BOOST_CHECK_CLOSE(rect.getFrameRect().pos.y, frameRect.pos.y, eps);
  }

BOOST_AUTO_TEST_SUITE_END();
