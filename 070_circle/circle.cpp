#include "circle.hpp"

#include <cmath>

#define PI 3.1415926

Circle::Circle(Point new_center, double new_radius) :
    center(new_center), radius(new_radius) {
}

void Circle::move(double dx, double dy) {
  this->center.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double centerDistance = this->center.distanceFrom(otherCircle.center);

  // Do not intersect
  if (centerDistance >= (this->radius + otherCircle.radius)) {
    return 0.0;
  }
  // Contain
  if (centerDistance <= std::abs(this->radius - otherCircle.radius)) {
    if (this->radius <= otherCircle.radius) {
      return PI * this->radius * this->radius;
    }
    else {
      return PI * otherCircle.radius * otherCircle.radius;
    }
  }

  // Intersect
  double ang1 = std::acos((this->radius * this->radius + centerDistance * centerDistance -
                           otherCircle.radius * otherCircle.radius) /
                          (2 * this->radius * centerDistance));
  double ang2 =
      std::acos((otherCircle.radius * otherCircle.radius +
                 centerDistance * centerDistance - this->radius * this->radius) /
                (2 * otherCircle.radius * centerDistance));
  return ang1 * this->radius * this->radius +
         ang2 * otherCircle.radius * otherCircle.radius -
         this->radius * centerDistance * std::sin(ang1);
}
