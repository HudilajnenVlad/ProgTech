#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <memory>
#include "matrix.hpp"
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

const double eps = 0.000001;

BOOST_AUTO_TEST_SUITE(Matrix_add)

  BOOST_AUTO_TEST_CASE(add_nullShape_ThrownException)
  {
    hudilajnen::Shape::ShapeSharedPtr rect = nullptr;
    hudilajnen::Matrix matrix;

    BOOST_CHECK_THROW(matrix.add(rect), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(add_validShape_noThrownException)
  {
    double width = 5;
    double height = 6;
    hudilajnen::point_t pos = {3, 4};
    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::Matrix matrix;

    BOOST_CHECK_NO_THROW(matrix.add(rect));
  }

  BOOST_AUTO_TEST_CASE(add_validShape_correctAddedToLayers)
  {
    double width1 = 5;
    double height1 = 6;
    double width2 = 7;
    double height2 = 8;
    double width3 = 10;
    double height3 = 10;
    double width4 = 5;
    double height4 = 5;
    hudilajnen::point_t pos1 = {3, 4};
    hudilajnen::point_t pos2 = {3, 4};
    hudilajnen::point_t pos3 = {30, 40};
    hudilajnen::point_t pos4 = {30, 40};
    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width1, height1, pos1));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width2, height2, pos2));
    hudilajnen::Shape::ShapeSharedPtr rect3(new hudilajnen::Rectangle(width3, height3, pos3));
    hudilajnen::Shape::ShapeSharedPtr rect4(new hudilajnen::Rectangle(width4, height4, pos4));

    hudilajnen::Matrix matrix;
    matrix.add(rect1);
    matrix.add(rect2);
    matrix.add(rect3);
    matrix.add(rect4);

    size_t layers = 2;
    size_t shapesOnLayers = 2;

    BOOST_CHECK_EQUAL(matrix.getCountOfLayer(), layers);
    BOOST_CHECK_EQUAL(matrix.getNumberOfShapesOnLayer(0), shapesOnLayers);
    BOOST_CHECK_EQUAL(matrix.getNumberOfShapesOnLayer(1), shapesOnLayers);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Matrix_getNumberOFShapeOnLayer)

  BOOST_AUTO_TEST_CASE(getNumberOfShapeOnLayer_invalidNumberOfLayer_ThrownException)
  {
    double width = 15;
    double height = 16;
    hudilajnen::point_t pos{3, 7};
    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));

    hudilajnen::Matrix matrix;
    matrix.add(rect);

    BOOST_CHECK_THROW(matrix.getNumberOfShapesOnLayer(4), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(getNumberOfShapeOnLayer_validNumberOfLayer_noThrownException)
  {
    double width = 1;
    double height = 1;
    hudilajnen::point_t pos{13, 27};
    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));

    hudilajnen::Matrix matrix;
    matrix.add(rect);

    BOOST_CHECK_NO_THROW(matrix.getNumberOfShapesOnLayer(0));
  }


BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(Matrix_index)

  BOOST_AUTO_TEST_CASE(index_invalidParametrs_ThrownException)
  {
    double width = 10;
    double height = 15;
    hudilajnen::point_t pos{14, 17};
    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));

    hudilajnen::Matrix matrix;
    matrix.add(rect);

    BOOST_CHECK_THROW(matrix[2][0], std::out_of_range);
    BOOST_CHECK_THROW(matrix[0][2], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(index_nullMatrix_ThrownException)
  {
    hudilajnen::Matrix matrix;

    BOOST_CHECK_THROW(matrix[0][0], std::logic_error);
  }

  BOOST_AUTO_TEST_CASE(index_validParametrs_noThrownException)
  {
    double width1 = 1;
    double height1 = 1;
    double width2 = 4;
    double height2 = 4;
    hudilajnen::point_t pos{1, 1};
    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width1, height1, pos));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width2, height2, pos));

    hudilajnen::Matrix matrix;
    matrix.add(rect1);
    matrix.add(rect2);

    BOOST_CHECK_NO_THROW(matrix[0][0]);
    BOOST_CHECK_NO_THROW(matrix[1][0]);
  }

  BOOST_AUTO_TEST_CASE(index_validParametrs_getCorrectFrameRectParametrs)
  {
    double width = 5;
    double height = 6;
    hudilajnen::point_t pos{3, 4};
    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::rectangle_t frameRectOfStartRect = rect->getFrameRect();

    hudilajnen::Matrix matrix;
    matrix.add(rect);
    hudilajnen::rectangle_t frameRectOnMatrixRect = matrix[0][0]->getFrameRect();

    BOOST_CHECK_CLOSE(frameRectOfStartRect.width, frameRectOnMatrixRect.width, eps);
    BOOST_CHECK_CLOSE(frameRectOfStartRect.height, frameRectOnMatrixRect.height, eps);
    BOOST_CHECK_CLOSE(frameRectOfStartRect.pos.x, frameRectOnMatrixRect.pos.x, eps);
    BOOST_CHECK_CLOSE(frameRectOfStartRect.pos.y, frameRectOnMatrixRect.pos.y, eps);
  }

BOOST_AUTO_TEST_SUITE_END();
