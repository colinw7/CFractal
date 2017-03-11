struct IPoint {
  IPoint(int x1=0, int y1=0) :
   x(x1), y(y1) {
  }

  int x, y;

  IPoint operator-() const {
    return IPoint(-x, -y);
  }

  const IPoint &operator+=(const IPoint &rhs) {
    x += rhs.x; y += rhs.y;

    return *this;
  }

  const IPoint &operator-=(const IPoint &rhs) {
    x -= rhs.x; y -= rhs.y;

    return *this;
  }

  const IPoint &operator*=(int f) {
    x *= f; y *= f;

    return *this;
  }

  friend IPoint operator+(const IPoint &lhs, const IPoint &rhs) {
    return IPoint(lhs.x + rhs.x, lhs.y + rhs.y);
  }

  friend IPoint operator-(const IPoint &lhs, const IPoint &rhs) {
    return IPoint(lhs.x - rhs.x, lhs.y - rhs.y);
  }

  friend IPoint operator*(const IPoint &lhs, int rhs) {
    return IPoint(lhs.x * rhs, lhs.y * rhs);
  }

  friend IPoint operator*(int lhs, const IPoint &rhs) {
    return IPoint(lhs * rhs.x, lhs * rhs.y);
  }
};
