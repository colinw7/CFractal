#ifndef CQMandelbrotGradient_H
#define CQMandelbrotGradient_H

#include <CGradientPalette.h>
#include <CMandelbrot.h>
#include <QWidget>

class CQMandelbrotGradient : public QWidget {
 public:
  CQMandelbrotGradient();

  void paintEvent(QPaintEvent *);

 private:
  CMandelbrot      mandelbrot_;
  CGradientPalette palette_;
};

#endif
