#ifndef CORTHOGONAL_H
#define CORTHOGONAL_H

#include <CPointFractal.h>

class COrthogonal : public CPointFractalCalc {
 public:
  enum Type {
    T5,
    C6,
    P4,
    P6,
    L4,
    H4
  };

 public:
  COrthogonal(Type type=T5);

  virtual ~COrthogonal() { }

  COrthogonal *dup() const;

  double getXMin() const { return xmin_; }
  double getYMin() const { return ymin_; }
  double getXMax() const { return xmax_; }
  double getYMax() const { return ymax_; }

  void setType(Type type);

  int calc(double x, double y, int max_iterations) const;

  int iterate_t5(double x, double y, int max_iterations) const;
  int iterate_c6(double x, double y, int max_iterations) const;
  int iterate_p4(double x, double y, int max_iterations) const;
  int iterate_p6(double x, double y, int max_iterations) const;
  int iterate_l4(double x, double y, int max_iterations) const;
  int iterate_h4(double x, double y, int max_iterations) const;

 private:
  mutable double zr_, zi_;

  Type   type_;
  double xmin_, ymin_, xmax_, ymax_;
};

#endif
