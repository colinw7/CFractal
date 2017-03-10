#ifndef CJULIA_H
#define CJULIA_H

#include <CPointFractal.h>

class CTranscendental : public CPointFractalCalc {
 public:
  enum Type {
    SIN,
    COS,
    SINH,
    COSH,
    EXP
  };

 public:
  CTranscendental();

  virtual ~CTranscendental() { }

  CTranscendental *dup() const;

  double getXMin() const { return xmin_; }
  double getYMin() const { return ymin_; }
  double getXMax() const { return xmax_; }
  double getYMax() const { return ymax_; }

  void setType(Type type);

  int calc(double x, double y, int max_iterations) const;

  int iterate_cos (double x, double y, int max_iterations) const;
  int iterate_sin (double x, double y, int max_iterations) const;
  int iterate_exp (double x, double y, int max_iterations) const;
  int iterate_cosh(double x, double y, int max_iterations) const;
  int iterate_sinh(double x, double y, int max_iterations) const;

 private:
  mutable double zr_, zi_;

  Type   type_;
  double xmin_, ymin_, xmax_, ymax_;
};

#endif
