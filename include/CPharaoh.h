#ifndef CPHARAOH_H
#define CPHARAOH_H

#include <CRGBA.h>

class CPharaoh {
 private:
  static const char *colors[];

  double canvas_xmin;
  double canvas_ymin;
  double canvas_xmax;
  double canvas_ymax;

  double invert_x;
  double invert_y;
  double invert_r;
  double invert_rs;

 public:
  CPharaoh();

  virtual ~CPharaoh() { }

  void draw();

  virtual void setDataRange(double xmin, double ymin,
                            double xmax, double ymax) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void fillCircle(double x, double y, double r) = 0;

 private:
  void generateCircle(double, double, double, int);
  void invertCircle(double, double, double, int);
  void invertPoint(double *, double *);
};

#endif
