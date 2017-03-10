#ifndef CJULIA_H
#define CJULIA_H

#include <CPointFractal.h>

class CJulia : public CPointFractalCalc {
 public:
  CJulia(double cr = 0.238498, double ci = 0.519198);

  virtual ~CJulia() { }

  CJulia *dup() const { return new CJulia(cr_, ci_); }

  void setC(double cr, double ci) { cr_ = cr; ci_ = ci; }

  void setTime(double t);

  double getXMin() const { return -1.6; }
  double getYMin() const { return -1.2; }
  double getXMax() const { return  1.6; }
  double getYMax() const { return  1.2; }

  int calc(double x, double y, int max_iterations) const;

  int iterate(double x, double y, int max_iterations) const;

 private:
  double cr_, ci_;

  mutable double zr_, zi_;
};

#endif
