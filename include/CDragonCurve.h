#ifndef CDRAGON_CURVE_H
#define CDRAGON_CURVE_H

#include <CPointFractal.h>

class CDragonCurve : public CPointFractalCalc {
 public:
  CDragonCurve() : p_(1.646009), q_(0.967049) { }

  virtual ~CDragonCurve() { }

  CDragonCurve *dup() const;

  double getXMin() const { return -0.2; }
  double getYMin() const { return -0.7; }
  double getXMax() const { return  1.2; }
  double getYMax() const { return  0.7; }

  void setParams(double p, double q) { p_ = p; q_ = q; }

  int calc(double x, double y, int max_iterations) const;

 private:
  double p_, q_;
};

#endif
