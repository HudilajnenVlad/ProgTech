#ifndef HUDILAJNEN_VLADISLAV_BASE_TYPES_HPP
#define HUDILAJNEN_VLADISLAV_BASE_TYPES_HPP

namespace hudilajnen
{
  struct point_t
  {
    double x;
    double y;
  };

  struct rectangle_t
  {
    double width;
    double height;
    point_t pos;
  };

}
namespace implementationDetails
{
  bool isOverlap(const hudilajnen::rectangle_t &frame1, const hudilajnen::rectangle_t &frame2);
}

#endif //HUDILAJNEN_VLADISLAV_BASE_TYPES_HPP
