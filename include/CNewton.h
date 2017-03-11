#ifndef CJULIA_H
#define CJULIA_H

#include <CPointFractal.h>

class CNewton : public CPointFractalCalc {
 public:
  CNewton();

  virtual ~CNewton() { }

  CNewton *dup() const;

  double getXMin() const { return -3.5; }
  double getYMin() const { return -2.5; }
  double getXMax() const { return  3.5; }
  double getYMax() const { return  2.5; }

  int calc(double x, double y, int max_iterations) const;

 private:
  int calc1(double x, double y, int max_iterations) const;
  int calc2(double x, double y, int max_iterations) const;
};

#endif
