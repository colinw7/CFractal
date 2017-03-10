#ifndef CPHOENIX_H
#define CPHOENIX_H

#include <CPointFractal.h>

class CPhoenix : public CPointFractalCalc {
 private:
  double p_, q_;

 public:
  CPhoenix();

  virtual ~CPhoenix() { }

  CPhoenix *dup() const;

  void setParams(double p, double q) { p_ = p; q_ = q; }

  double getXMin() const { return -1.4; }
  double getYMin() const { return -1.4; }
  double getXMax() const { return  1.4; }
  double getYMax() const { return  1.4; }

  int calc(double x, double y, int max_iterations) const;
};

#endif
