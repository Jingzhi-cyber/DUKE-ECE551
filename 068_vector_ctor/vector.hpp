/* write your class interface in this file
   write function definitions only if they are very short
 */
#include <cmath>  // why can we just write using std::sqrt;
#include <cstdio>

class Vector2D {
 private:
  double x;
  double y;

 public:
  Vector2D() : x(0), y(0) {}

  Vector2D(double x, double y) : x(x), y(y) {}

  double getMagnitude() const {
    return std::sqrt(x * x + y * y);
  }  // What if we omit std:: ?

  Vector2D operator+(const Vector2D & rhs) const;

  Vector2D & operator+=(const Vector2D & rhs);

  double dot(const Vector2D & rhs) const;

  void print() const { std::printf("<%.2f, %.2f>", this->x, this->y); }
};
