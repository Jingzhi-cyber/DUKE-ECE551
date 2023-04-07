#include "point.hpp"

class Circle {
 private:
  Point center;
  const double radius;

 public:
  Circle(Point new_center, double new_radius);

  void move(double dx, double dy);

  double intersectionArea(const Circle & otherCircle);
};
