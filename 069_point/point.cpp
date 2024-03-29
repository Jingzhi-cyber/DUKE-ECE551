#include "point.hpp"

#include <cmath>

void Point::move(double dx, double dy) {
  this->x += dx;
  this->y += dy;
}

double Point::distanceFrom(const Point & p) {
  return std::sqrt((this->x - p.x) * (this->x - p.x) + (this->y - p.y) * (this->y - p.y));
}
