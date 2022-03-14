#include <boost/test/unit_test.hpp>
#include <stdexcept>
#include <memory>
#include "composite-shape.hpp"
#include "rectangle.hpp"
#include "circle.hpp"
#include "base-types.hpp"

const double eps = 0.000001;

BOOST_AUTO_TEST_SUITE(compositeShape_constructor)

  BOOST_AUTO_TEST_CASE (construct_notNullRectInConstruct_noException)
  {
    double width = 5;
    double height = 6;
    hudilajnen::point_t pos = {3, 4};
    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));

    BOOST_CHECK_NO_THROW(hudilajnen::CompositeShape compShape{rect});
  }

  BOOST_AUTO_TEST_CASE (construct_notNullCircleInConstruct_noException)
  {
    double radius = 5;
    hudilajnen::point_t pos = {3, 4};
    hudilajnen::Shape::ShapeSharedPtr circle(new hudilajnen::Circle(radius, pos));

    BOOST_CHECK_NO_THROW(hudilajnen::CompositeShape compShape{circle});
  }

  BOOST_AUTO_TEST_CASE (construct_NullptrShapeInCOnstruct_ThrownEception)
  {
    hudilajnen::Shape::ShapeSharedPtr rectangle = nullptr;

    BOOST_CHECK_THROW(hudilajnen::CompositeShape compShape(rectangle), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE (construct_notNullCircleInConstruct_correctCreated)
  {
    double radius = 8;
    hudilajnen::point_t pos = {-5, 9};

    hudilajnen::Shape::ShapeSharedPtr circle(new hudilajnen::Circle(radius, pos));
    hudilajnen::rectangle_t frameRect = circle->getFrameRect();

    hudilajnen::CompositeShape compShape{circle};
    hudilajnen::rectangle_t compFrameRect = compShape.getFrameRect();

    BOOST_CHECK_CLOSE(circle->getArea(), compShape.getArea(), eps);
    BOOST_CHECK_CLOSE(frameRect.width, compFrameRect.width, eps);
    BOOST_CHECK_CLOSE(frameRect.height, compFrameRect.height, eps);
    BOOST_CHECK_CLOSE(frameRect.pos.x, compFrameRect.pos.x, eps);
    BOOST_CHECK_CLOSE(frameRect.pos.y, compFrameRect.pos.y, eps);
  }

  BOOST_AUTO_TEST_CASE (construct_notNullRectInConstruct_correctCreated)
  {
    double width = 10;
    double height = 12;
    hudilajnen::point_t pos = {16, 23};

    std::shared_ptr<hudilajnen::Rectangle> rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::rectangle_t frameRect = rect->getFrameRect();

    hudilajnen::CompositeShape compShape{rect};
    hudilajnen::rectangle_t compFrameRect = compShape.getFrameRect();

    BOOST_CHECK_CLOSE(rect->getArea(), compShape.getArea(), eps);
    BOOST_CHECK_CLOSE(frameRect.width, compFrameRect.width, eps);
    BOOST_CHECK_CLOSE(frameRect.height, compFrameRect.height, eps);
    BOOST_CHECK_CLOSE(frameRect.pos.x, compFrameRect.pos.x, eps);
    BOOST_CHECK_CLOSE(frameRect.pos.y, compFrameRect.pos.y, eps);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_index)

  BOOST_AUTO_TEST_CASE(index_RectangleWithParametrValidIndex_EqualRect)
  {
    double width = 2;
    double height = 8;
    hudilajnen::point_t pos = {4, 3};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_EQUAL(rect, compShape[0]);
  }

  BOOST_AUTO_TEST_CASE (index_validIndex_ThrownException)
  {
    double width = 8;
    double height = 12;
    hudilajnen::point_t pos = {4, 3};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_NO_THROW(compShape[0]);
  }

  BOOST_AUTO_TEST_CASE (index_invalidIndexEqualSize_ThrownException)
  {
    double width = 16;
    double height = 21;
    hudilajnen::point_t pos = {10, 20};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_THROW(compShape[compShape.getSize()], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE (index_invalidIndex_ThrownException)
  {
    double width = 27;
    double height = 28;
    hudilajnen::point_t pos = {12, 13};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_THROW(compShape[3], std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(index_nullPtrWithMoveConstruct_ThrownException)
  {
    double width = 12;
    double height = 13;
    hudilajnen::point_t pos = {17, 21};
    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));

    hudilajnen::CompositeShape compShape1(rect);
    hudilajnen::CompositeShape compShape2(std::move(compShape1));

    BOOST_CHECK_THROW(compShape1[0], std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_add)

  BOOST_AUTO_TEST_CASE (add_nullPtrParametr_ThrowException)
  {
    double width = 3;
    double height = 2.5;
    hudilajnen::point_t pos = {1, 0};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    hudilajnen::Shape::ShapeSharedPtr rect2 = nullptr;

    BOOST_CHECK_THROW(compShape.add(rect2), std::invalid_argument);

  }

  BOOST_AUTO_TEST_CASE (add_rectangleWithParametr_noThrowException)
  {
    double width = 16.4;
    double height = 21.3;
    hudilajnen::point_t pos1 = {4, 5};
    hudilajnen::point_t pos2 = {-3, -4};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::CompositeShape compShape(rect);

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));

    BOOST_CHECK_NO_THROW(compShape.add(rect2));

  }

  BOOST_AUTO_TEST_CASE (add_rectangleWithParametr_EqualRectanglesInCompShape)
  {
    double width = 12;
    double height = 16;
    hudilajnen::point_t pos1 = {78, 21};
    hudilajnen::point_t pos2 = {-78, -21};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::CompositeShape compShape(rect);

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    compShape.add(rect2);

    BOOST_CHECK_EQUAL(rect2, compShape[1]);
  }

  BOOST_AUTO_TEST_CASE(add_someShapeToNullShape_ThorwnException)
  {
    double width1 = 17;
    double height1 = 23;
    double width2 = 37;
    double height2 = 43;
    hudilajnen::point_t pos = {17, 21};
    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width1, height1, pos));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width2, height2, pos));

    hudilajnen::CompositeShape compShape1(rect1);
    hudilajnen::CompositeShape compShape2(std::move(compShape1));

    BOOST_CHECK_THROW(compShape1.add(rect2), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_remove)

  BOOST_AUTO_TEST_CASE(remove_sizeIndexAndMoreSizeIndex_ThrownException)
  {
    double width = 13;
    double height = 45;
    hudilajnen::point_t pos = {14, 17};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_THROW(compShape.remove(compShape.getSize()), std::out_of_range);
    BOOST_CHECK_THROW(compShape.remove(compShape.getSize() + 1), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(remove_lastOneIndex_ThrownException)
  {
    double width = 12;
    double height = 3;
    hudilajnen::point_t pos = {4, 1};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_THROW(compShape.remove(0), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(remove_correctIndex_noThrow)
  {
    double width = 11;
    double height = 11;
    hudilajnen::point_t pos1 = {12, 14};
    hudilajnen::point_t pos2 = {-24, -19};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::CompositeShape compShape(rect);

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    compShape.add(rect2);

    BOOST_CHECK_NO_THROW(compShape.remove(compShape.getSize() - 1));
  }

  BOOST_AUTO_TEST_CASE(remove_correctIndex_correctDelteObject)
  {
    double width = 5;
    double height = 6;
    hudilajnen::point_t pos1 = {13, 14};
    hudilajnen::point_t pos2 = {-63, -24};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::CompositeShape compShape(rect);

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    compShape.add(rect2);

    double oldSize = compShape.getSize();
    compShape.remove(1);

    BOOST_CHECK_EQUAL(compShape.getSize(), oldSize - 1);
  }

  BOOST_AUTO_TEST_CASE(remove_ShapeIntoNullCompositeShape_ThorwnException)
  {
    double width1 = 27;
    double height1 = 13;
    double width2 = 39;
    double height2 = 46;
    hudilajnen::point_t pos = {17, 21};
    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width1, height1, pos));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width2, height2, pos));

    hudilajnen::CompositeShape compShape1(rect1);
    compShape1.add(rect2);
    hudilajnen::CompositeShape compShape2(std::move(compShape1));

    BOOST_CHECK_THROW(compShape1.remove(1), std::invalid_argument);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_getFrameRect)

  BOOST_AUTO_TEST_CASE(getFrameRect_TwoCombiniedRectangles_compShapeFrameEqualSumRectangles)
  {
    double width = 2;
    double height = 2;
    hudilajnen::point_t pos1 = {0, 0};
    hudilajnen::point_t pos2 = {2, 0};
    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    double area = rect1->getArea() + rect2->getArea();
    hudilajnen::rectangle_t rect1Frame = rect1->getFrameRect();
    hudilajnen::rectangle_t rect2Frame = rect2->getFrameRect();

    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    hudilajnen::rectangle_t compShapeFrameRect = compShape.getFrameRect();
    double areaCompShape = compShape.getArea();

    BOOST_CHECK_CLOSE(area, areaCompShape, eps);
    BOOST_CHECK_CLOSE(rect1Frame.width + rect2Frame.width, compShapeFrameRect.width, eps);
    BOOST_CHECK_CLOSE(rect1Frame.height, compShapeFrameRect.height, eps);
    BOOST_CHECK_CLOSE((rect1Frame.pos.x + rect2Frame.pos.x) / 2, compShapeFrameRect.pos.x, eps);
    BOOST_CHECK_CLOSE((rect1Frame.pos.y + rect2Frame.pos.y) / 2, compShapeFrameRect.pos.y, eps);
  }

  BOOST_AUTO_TEST_CASE(remove_ShapeIntoNullCompositeShape_ThorwnException)
  {
    double width1 = 11;
    double height1 = 27;
    double width2 = 32;
    double height2 = 41;
    hudilajnen::point_t pos = {17, 21};
    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width1, height1, pos));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width2, height2, pos));

    hudilajnen::CompositeShape compShape1(rect1);
    compShape1.add(rect2);
    hudilajnen::CompositeShape compShape2(std::move(compShape1));

    BOOST_CHECK_CLOSE(compShape1.getFrameRect().width, -1, eps);
    BOOST_CHECK_CLOSE(compShape1.getFrameRect().height, -1, eps);
  }


BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_moveByCoords)

  BOOST_AUTO_TEST_CASE(moveByCoords_positiveCoords_correctMove)
  {
    double dx = 5;
    double dy = 5;
    double width = 4;
    double height = 4;
    hudilajnen::point_t pos1 = {0, 0};
    hudilajnen::point_t pos2 = {2, 0};

    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::point_t oldPositionRect1 = rect1->getCenter();

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    hudilajnen::point_t oldPositionRect2 = rect2->getCenter();

    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    hudilajnen::point_t oldPositionCompShape = compShape.getCenter();

    compShape.move(dx, dy);

    BOOST_CHECK_CLOSE(oldPositionCompShape.x + dx, compShape.getCenter().x, eps);
    BOOST_CHECK_CLOSE(oldPositionCompShape.y + dy, compShape.getCenter().y, eps);

    BOOST_CHECK_CLOSE(oldPositionRect1.x + dx, compShape[0]->getCenter().x, eps);
    BOOST_CHECK_CLOSE(oldPositionRect1.y + dy, compShape[0]->getCenter().y, eps);

    BOOST_CHECK_CLOSE(oldPositionRect2.x + dx, compShape[1]->getCenter().x, eps);
    BOOST_CHECK_CLOSE(oldPositionRect2.y + dy, compShape[1]->getCenter().y, eps);

  }

  BOOST_AUTO_TEST_CASE(movingByCoords_positiveCoords_constantFrameRects)
  {
    double dx = 5;
    double dy = 5;
    double width = 6;
    double height = 6;
    hudilajnen::point_t pos1 = {12, 21};
    hudilajnen::point_t pos2 = {14, 21};

    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::rectangle_t rect1FrameOld = rect1->getFrameRect();

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    hudilajnen::rectangle_t rect2FrameOld = rect2->getFrameRect();

    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    hudilajnen::rectangle_t compShapeFrameOld = compShape.getFrameRect();

    compShape.move(dx, dy);

    BOOST_CHECK_CLOSE(compShapeFrameOld.width, compShape.getFrameRect().width, eps);
    BOOST_CHECK_CLOSE(compShapeFrameOld.height, compShape.getFrameRect().height, eps);

    BOOST_CHECK_CLOSE(rect1FrameOld.width, compShape[0]->getFrameRect().width, eps);
    BOOST_CHECK_CLOSE(rect1FrameOld.height, compShape[0]->getFrameRect().height, eps);

    BOOST_CHECK_CLOSE(rect2FrameOld.width, compShape[1]->getFrameRect().width, eps);
    BOOST_CHECK_CLOSE(rect2FrameOld.height, compShape[1]->getFrameRect().height, eps);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(compositeShape_moveToPoint)

  BOOST_AUTO_TEST_CASE(moveToPoin_positivePoint_correctMove)
  {
    double width = 10;
    double height = 10;
    hudilajnen::point_t pos1 = {0, 0};
    hudilajnen::point_t pos2 = {2, 0};
    hudilajnen::point_t newPos = {5, 5};

    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::point_t oldPositionRect1 = rect1->getCenter();

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    hudilajnen::point_t oldPositionRect2 = rect2->getCenter();

    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    hudilajnen::point_t oldPositionCompShape = compShape.getCenter();

    compShape.move(newPos);
    hudilajnen::point_t compShapeNewPos = compShape.getCenter();
    hudilajnen::point_t rect1NewPos = compShape[0]->getCenter();
    hudilajnen::point_t rect2NewPos = compShape[1]->getCenter();

    BOOST_CHECK_CLOSE(compShapeNewPos.x, newPos.x, eps);
    BOOST_CHECK_CLOSE(compShapeNewPos.y, newPos.y, eps);

    BOOST_CHECK_CLOSE(oldPositionCompShape.x - oldPositionRect1.x, compShapeNewPos.x - rect1NewPos.x, eps);
    BOOST_CHECK_CLOSE(oldPositionCompShape.y - oldPositionRect1.y, compShapeNewPos.y - rect1NewPos.y, eps);

    BOOST_CHECK_CLOSE(oldPositionCompShape.x - oldPositionRect2.x, compShapeNewPos.x - rect2NewPos.x, eps);
    BOOST_CHECK_CLOSE(oldPositionCompShape.y - oldPositionRect2.y, compShapeNewPos.y - rect2NewPos.y, eps);
  }

  BOOST_AUTO_TEST_CASE(moveByCoords_positivePoint_constantFrameRects)
  {
    double width = 18;
    double height = 18;
    hudilajnen::point_t pos1 = {0, 0};
    hudilajnen::point_t pos2 = {2, 0};
    hudilajnen::point_t newPos = {5, 5};

    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::rectangle_t rect1FrameOld = rect1->getFrameRect();

    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    hudilajnen::rectangle_t rect2FrameOld = rect2->getFrameRect();

    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    hudilajnen::rectangle_t compShapeFrameOld = compShape.getFrameRect();

    compShape.move(newPos);

    BOOST_CHECK_CLOSE(compShapeFrameOld.width, compShape.getFrameRect().width, eps);
    BOOST_CHECK_CLOSE(compShapeFrameOld.height, compShape.getFrameRect().height, eps);

    BOOST_CHECK_CLOSE(rect1FrameOld.width, compShape[0]->getFrameRect().width, eps);
    BOOST_CHECK_CLOSE(rect1FrameOld.height, compShape[0]->getFrameRect().height, eps);

    BOOST_CHECK_CLOSE(rect2FrameOld.width, compShape[1]->getFrameRect().width, eps);
    BOOST_CHECK_CLOSE(rect2FrameOld.height, compShape[1]->getFrameRect().height, eps);
  }

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(CompositeShape_scale)

  BOOST_AUTO_TEST_CASE(scale_nullCoeficient_ThrowException)
  {
    double k = 0;
    double width = 3;
    double height = 8;
    hudilajnen::point_t pos = {3, 4};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_THROW(compShape.scale(k), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scale_negativeCoeficient_ThrowException)
  {
    double k = -5;
    double width = 5;
    double height = 6;
    hudilajnen::point_t pos = {3, 4};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_THROW(compShape.scale(k), std::invalid_argument);
  }

  BOOST_AUTO_TEST_CASE(scale_positiveCoeficient_noThrowException)
  {
    double k = 5;
    double width = 5;
    double height = 3;
    hudilajnen::point_t pos = {3, 4};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos));
    hudilajnen::CompositeShape compShape(rect);

    BOOST_CHECK_NO_THROW(compShape.scale(k));
  }

  BOOST_AUTO_TEST_CASE(scale_positiveCoeficient_constantCenter)
  {
    double k = 5;
    double width = 3;
    double height = 6;
    hudilajnen::point_t pos1 = {0, 0};
    hudilajnen::point_t pos2 = {2, 0};

    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));

    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    hudilajnen::point_t compShapeOldPos = compShape.getCenter();

    compShape.scale(k);
    hudilajnen::point_t compShapeNewPos = compShape.getCenter();

    BOOST_CHECK_CLOSE(compShapeOldPos.x, compShapeNewPos.x, eps);
    BOOST_CHECK_CLOSE(compShapeOldPos.y, compShapeNewPos.y, eps);
  }

  BOOST_AUTO_TEST_CASE(scale_positiveCoeficient_correctMoveCenterOfSheps)
  {
    double k = 5;
    double width = 5;
    double height = 6;
    hudilajnen::point_t pos1 = {14, 2};
    hudilajnen::point_t pos2 = {4, 9};

    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::point_t rect1OldPosition = rect1->getCenter();
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));
    hudilajnen::point_t rect2OldPosition = rect2->getCenter();

    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    hudilajnen::point_t compShapePos = compShape.getCenter();
    compShape.scale(k);

    BOOST_CHECK_CLOSE((rect1OldPosition.x - compShapePos.x) * k, compShape[0]->getCenter().x - compShapePos.x, eps);
    BOOST_CHECK_CLOSE((rect2OldPosition.y - compShapePos.y) * k, compShape[1]->getCenter().y - compShapePos.y, eps);
  }


BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CompositeShape_rotate)

  BOOST_AUTO_TEST_CASE(rotate_Angle_constantArea)
  {
    double width = 4;
    double height = 8;
    hudilajnen::point_t pos1 = {1, 2};
    hudilajnen::point_t pos2 = {7, 9};

    hudilajnen::Shape::ShapeSharedPtr rect1(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::Shape::ShapeSharedPtr rect2(new hudilajnen::Rectangle(width, height, pos2));


    hudilajnen::CompositeShape compShape(rect1);
    compShape.add(rect2);
    double oldArea = compShape.getArea();

    compShape.rotate(42);

    BOOST_CHECK_CLOSE(oldArea, compShape.getArea(), eps);
  }

  BOOST_AUTO_TEST_CASE(rotate_WideAngle_constantFrameRect)
  {
    double width = 3;
    double height = 9;
    double angle = 180;
    double radius = 1.2;
    hudilajnen::point_t pos1 = {1, 2};
    hudilajnen::point_t pos2 = {6, 3};

    hudilajnen::Shape::ShapeSharedPtr rect(new hudilajnen::Rectangle(width, height, pos1));
    hudilajnen::Shape::ShapeSharedPtr circ(new hudilajnen::Circle(radius, pos2));


    hudilajnen::CompositeShape compShape(rect);
    compShape.add(circ);
    hudilajnen::rectangle_t frameRect = compShape.getFrameRect();

    compShape.rotate(angle);

    BOOST_CHECK_CLOSE(compShape.getFrameRect().width, frameRect.width, eps);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().height, frameRect.height, eps);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.x, frameRect.pos.x, eps);
    BOOST_CHECK_CLOSE(compShape.getFrameRect().pos.y, frameRect.pos.y, eps);
  }

BOOST_AUTO_TEST_SUITE_END();
