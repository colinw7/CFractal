#ifndef CMANDELDIFF_H
#define CMANDELDIFF_H

#include <CPointFractal.h>
#include <CJulia.h>

class CMandelDiff : public CPointFractalCalc {
 public:
  CMandelDiff();

  virtual ~CMandelDiff() { }

  CMandelDiff *dup() const;

  void setC(double cr, double ci) { cr_ = cr; ci_ = ci; }

  double getXMin() const { return -2.0; }
  double getYMin() const { return -1.2; }
  double getXMax() const { return  1.2; }
  double getYMax() const { return  1.2; }

  void setRange(double xmin, double ymin, double xmax, double ymax);

  int calc(double x, double y, int max_iterations) const;

 private:
  mutable CJulia julia_;

  double cr_, ci_;
};

#endif
