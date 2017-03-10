#ifndef CDRAGON_H
#define CDRAGON_H

#include <CPointFractal.h>

class CDragon : public CPointFractalCalc {
 public:
  CDragon() { }

  virtual ~CDragon() { }

  CDragon *dup() const;

  double getXMin() const { return -2.2; }
  double getYMin() const { return -1.5; }
  double getXMax() const { return  4.2; }
  double getYMax() const { return  1.5; }

  int calc(double x, double y, int max_iterations) const;
};

#endif
