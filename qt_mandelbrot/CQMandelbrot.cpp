#include <CQMandelbrot.h>
#include <CMandelbrot.h>

CQMandelbrot::
CQMandelbrot(QWidget *parent) :
 CQPointFractal(parent)
{
  mandelbrot_ = new CMandelbrot;

  setFractal(mandelbrot_);
}

CQMandelbrot::
~CQMandelbrot()
{
  delete mandelbrot_;
}
