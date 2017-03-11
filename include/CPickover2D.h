#ifndef CPICKOVER2D_H
#define CPICKOVER2D_H

#include <CPickoverCalc.h>
#include <CPoint2D.h>
#include <CRGBA.h>
#include <vector>

class CPickover2D : public CPickoverCalc {
 public:
  enum DisplayType {
    XYZ_PROJECTION,
    XY_PLANE,
    XZ_PLANE,
    YZ_PLANE
  };

 private:
  typedef std::vector<CRGBA> ColorList;

  ColorList   colors_;
  int         color_num_;
  DisplayType display_type_;
  double      x_angle_, y_angle_, z_angle_;
  double      sx_, sy_, sz_;
  double      cx_, cy_, cz_;
  double      x1_, y1_, x2_, y2_;

 public:
  CPickover2D();

  void setDisplayType(DisplayType display_type) {
    display_type_ = display_type;
  }

  DisplayType getDisplayType() const {
    return display_type_;
  }

  double getXAngle() const { return x_angle_; }
  double getYAngle() const { return y_angle_; }
  double getZAngle() const { return z_angle_; }

  void setXAngle(double x_angle) { x_angle_ = x_angle; }
  void setYAngle(double y_angle) { y_angle_ = y_angle; }
  void setZAngle(double z_angle) { z_angle_ = z_angle; }

  void addColors();

  void addColor(const CRGBA &rgb);

  void nextColor();

  void draw();

  virtual void drawPoint(double x, double y, double z);

  virtual void setForeground(const CRGBA &rgba);

  virtual void drawLine(const CPoint2D &p1, const CPoint2D &p2);
};

#endif
