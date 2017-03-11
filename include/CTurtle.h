#ifndef CTURTLE_H
#define CTURTLE_H

#include <CRGBA.h>
#include <CMatrix2D.h>

class CTurtle {
 public:
  CTurtle();
  CTurtle(const CTurtle &turtle);

  virtual ~CTurtle();

  CTurtle &operator=(const CTurtle &turtle);

  virtual CTurtle *dup() const;

  double getX    () const { return x_    ; }
  double getY    () const { return y_    ; }
  double getAngle() const { return angle_; }

  void setX    (double x    ) { x_     = x    ; }
  void setY    (double y    ) { y_     = y    ; }
  void setAngle(double angle) { angle_ = angle; }

  const CRGBA &getColor() const { return color_; }

  virtual void setColor(const CRGBA &color);

  virtual void reset();

  virtual void move(double x, double y);
  virtual void step(double length);
  virtual void skip(double length);
  virtual void turn(double angle);

  virtual void drawLine(double x1, double y1, double x2, double y2);

 private:
  static double deg2rad(double deg) {
    static double degrees_to_radians = M_PI/180.0;

    return deg*degrees_to_radians;
  }

  static double rad2deg(double rad) {
    static double radians_to_degrees = 180.0/M_PI;

    return rad*radians_to_degrees;
  }

 protected:
  double    prev_x_, prev_y_;
  double    prev_angle_;
  double    x_, y_;
  double    angle_;
  CRGBA     color_;
  CMatrix2D m_;
};

#endif
