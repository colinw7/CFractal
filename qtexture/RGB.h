struct RGB {
  static RGB fromInt(unsigned int pixel) {
    int ir = (pixel & 0xFF0000) >> 16;
    int ig = (pixel & 0x00FF00) >>  8;
    int ib = (pixel & 0x0000FF) >>  0;

    return RGB(ir/255.0, ig/255.0, ib/255.0);
  }

  RGB(double gray=0.0) :
   r(gray), g(gray), b(gray) {
  }

  RGB(double red, double green, double blue) :
   r(red), g(green), b(blue) {
  }

  RGB operator-() const {
    return RGB(-r, -g, -b);
  }

  const RGB &operator+=(const RGB &rhs) {
    r += rhs.r; g += rhs.g; b += rhs.b;

    return *this;
  }

  const RGB &operator-=(const RGB &rhs) {
    r -= rhs.r; g -= rhs.g; b -= rhs.b;

    return *this;
  }

  friend RGB operator+(const RGB &lhs, const RGB &rhs) {
    return RGB(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b);
  }

  friend RGB operator-(const RGB &lhs, const RGB &rhs) {
    return RGB(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b);
  }

  friend RGB operator*(const RGB &lhs, const RGB &rhs) {
    return RGB(lhs.r*rhs.r, lhs.g*rhs.g, lhs.b*rhs.b);
  }

  friend RGB operator*(const RGB &lhs, double rhs) {
    return RGB(lhs.r*rhs, lhs.g*rhs, lhs.b*rhs);
  }

  friend RGB operator/(const RGB &lhs, double rhs) {
    return RGB(lhs.r/rhs, lhs.g/rhs, lhs.b/rhs);
  }

  const RGB &operator*=(double f) {
    r *= f; g *= f; b *= f;

    return *this;
  }

  const RGB &operator/=(double f) {
    r /= f; g /= f; b /= f;

    return *this;
  }

  uint toInt() const {
    int ir = int(r*255), ig = int(g*255), ib = int(b*255);

    if (ir < 0) ir = 0; if (ir > 255) ir = 255;
    if (ig < 0) ig = 0; if (ig > 255) ig = 255;
    if (ib < 0) ib = 0; if (ib > 255) ib = 255;

    return 0xFF000000U | (ir << 16) | (ig << 8) | ib;
  }

  double r, g, b;
};
