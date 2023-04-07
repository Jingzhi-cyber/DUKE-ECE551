#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D ans;
  ans.x = this->x + rhs.x;
  ans.y = this->y + rhs.y;

  return ans;
}

Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  this->x += rhs.x;
  this->y += rhs.y;

  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return this->x * rhs.x + this->y * rhs.y;
}
