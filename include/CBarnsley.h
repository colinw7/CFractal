#ifndef CBARNSLEY_H
#define CBARNSLEY_H

#include <CPointFractal.h>

class CBarnsley : public CPointFractalCalc {
 public:
  enum Type {
    B1,
    B2,
    B3,
    B4
  };

 public:
  CBarnsley();
  CBarnsley(const CBarnsley &barnsley);

  virtual ~CBarnsley() { }

  CBarnsley *dup() const;

  double getXMin() const { return xmin_; }
  double getYMin() const { return ymin_; }
  double getXMax() const { return xmax_; }
  double getYMax() const { return ymax_; }

  void setType(Type type);

  int calc(double x, double y, int max_iterations) const;

  int iterate_b1(double x, double y, int max_iterations) const;
  int iterate_b2(double x, double y, int max_iterations) const;
  int iterate_b3(double x, double y, int max_iterations) const;
  int iterate_b4(double x, double y, int max_iterations) const;

 private:
  mutable double zr_, zi_;

  Type   type_;
  double xmin_, ymin_, xmax_, ymax_;
  double p_, q_;
};

#endif
