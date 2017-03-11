#ifndef CGEN_POINT_FRACTAL_H
#define CGEN_POINT_FRACTAL_H

#include <CPointFractal.h>

class CGenPointFractal : public CPointFractalCalc {
 private:
  enum Type {
    VALUE,
    POS,
    NEG
  };

 public:
  CGenPointFractal();

  virtual ~CGenPointFractal() { }

  CGenPointFractal *dup() const;

  double getXMin() const { return xmin_; }
  double getYMin() const { return ymin_; }
  double getXMax() const { return xmax_; }
  double getYMax() const { return ymax_; }

  void setPQ(double p, double q) { p_ = p; q_ = q; }

  void mandelbrot();
  void julia();
  void dragon();
  void dragonSet();

  int calc(double x, double y, int max_iterations) const;

  int iterate(double x, double y, int max_iterations) const;

 private:
  double xmin_, ymin_, xmax_, ymax_;

  double p_, q_;

  Type xi_type_; double xi_;
  Type yi_type_; double yi_;
  Type a_type_;  double a_;
  Type b_type_;  double b_;
  Type c_type_;  double c_;
  Type d_type_;  double d_;
  Type e_type_;  double e_;
  Type f_type_;  double f_;

  mutable double zr_, zi_;
};

#endif
