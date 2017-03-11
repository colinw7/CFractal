struct Point {
  Point(double x1=0.0, double y1=0.0) :
   x(x1), y(y1) {
  }

  double x, y;

  Point operator-() const {
    return Point(-x, -y);
  }

  const Point &operator+=(const Point &rhs) {
    x += rhs.x; y += rhs.y;

    return *this;
  }

  const Point &operator-=(const Point &rhs) {
    x -= rhs.x; y -= rhs.y;

    return *this;
  }

  const Point &operator*=(double f) {
    x *= f; y *= f;

    return *this;
  }

  const Point &operator/=(double f) {
    x /= f; y /= f;

    return *this;
  }

  friend Point operator+(const Point &lhs, const Point &rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
  }

  friend Point operator-(const Point &lhs, const Point &rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
  }

  friend Point operator*(const Point &lhs, double rhs) {
    return Point(lhs.x * rhs, lhs.y * rhs);
  }

  friend Point operator/(const Point &lhs, double rhs) {
    return Point(lhs.x / rhs, lhs.y / rhs);
  }

  friend Point operator*(double lhs, const Point &rhs) {
    return Point(lhs * rhs.x, lhs * rhs.y);
  }
};
