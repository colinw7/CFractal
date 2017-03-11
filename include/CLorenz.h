#ifndef CLORENZ_H
#define CLORENZ_H

#include <CLorenzCalc.h>
#include <CRGBA.h>
#include <vector>

class CRenderer2D;

class CLorenz : public CLorenzCalc {
 public:
  enum DisplayType {
    XYZ_PROJECTION,
    XY_PLANE,
    XZ_PLANE,
    YZ_PLANE
  };

 private:
  typedef std::vector<CRGBA> ColorList;

  CRenderer2D *renderer_;
  ColorList    colors_;
  int          color_num_;
  DisplayType  display_type_;
  double       x_angle_, y_angle_, z_angle_;
  double       sx_, sy_, sz_;
  double       cx_, cy_, cz_;
  double       x1_, y1_, x2_, y2_;

 public:
  CLorenz(CRenderer2D *renderer);

  void setDisplayType(DisplayType display_type) {
    display_type_ = display_type;
  }

  DisplayType getDisplayType() const {
    return display_type_;
  }

  void setXAngle(double x_angle) { x_angle_ = x_angle; }
  double getXAngle() { return x_angle_; }

  void setYAngle(double y_angle) { y_angle_ = y_angle; }
  double getYAngle() { return y_angle_; }

  void setZAngle(double z_angle) { z_angle_ = z_angle; }
  double getZAngle() { return z_angle_; }

  void addColors();

  void addColor(const CRGBA &rgb);

  void nextColor();

  void draw();

  void drawPoint(double x, double y, double z);
};

#endif
