#ifndef CMANDEL_PHOENIX_H
#define CMANDEL_PHOENIX_H

#include <CPointFractal.h>

class CMandelPhoenix : public CPointFractalCalc {
 public:
  CMandelPhoenix() { }

  virtual ~CMandelPhoenix() { }

  CMandelPhoenix *dup() const;

  double getXMin() const { return -2.0; }
  double getYMin() const { return -2.0; }
  double getXMax() const { return  1.0; }
  double getYMax() const { return  2.0; }

  int calc(double x, double y, int max_iterations) const;
};

#endif
