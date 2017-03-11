#ifndef CDragonOutline_H
#define CDragonOutline_H

#include <CIPoint2D.h>

class CDragonOutline {
 private:
  double p_, q_;

 public:
  CDragonOutline();

  virtual ~CDragonOutline() { }

  void setParams(double p, double q);

  void draw(int w, int h);

  virtual void drawPoint(const CIPoint2D &p) = 0;
};

#endif
