#ifndef CQMANDELBROT_H
#define CQMANDELBROT_H

#include <CQPointFractal.h>

class CMandelbrot;

class CQMandelbrot : public CQPointFractal {
  Q_OBJECT

 public:
  CQMandelbrot(QWidget *parent = 0);

  virtual ~CQMandelbrot();

  CMandelbrot *getMandelbrot() const { return mandelbrot_; }

 private:
  CMandelbrot *mandelbrot_;
};

#endif
