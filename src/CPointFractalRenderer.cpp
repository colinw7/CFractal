#include <CPointFractalRenderer.h>
#include <CPointFractal.h>
#include <CTransform2D.h>

CPointFractalRenderer::
CPointFractalRenderer(CPointFractalCalc *calc) :
 CPointFractal(calc), calc_(calc)
{
  max_iterations_ = 128;

  xmin_ = calc->getXMin();
  ymin_ = calc->getYMin();
  xmax_ = calc->getXMax();
  ymax_ = calc->getYMax();
}

CPointFractalRenderer::
~CPointFractalRenderer()
{
}

bool
CPointFractalRenderer::
getShowVector() const
{
  return CPointFractal::getShowVector();
}

void
CPointFractalRenderer::
setShowVector(bool show_vector)
{
  CPointFractal::setShowVector(show_vector);
}

void
CPointFractalRenderer::
resetRange()
{
  xmin_ = calc_->getXMin();
  ymin_ = calc_->getYMin();
  xmax_ = calc_->getXMax();
  ymax_ = calc_->getYMax();
}

void
CPointFractalRenderer::
conv(double px, double py, double *wx, double *wy)
{
  CPointFractal::conv(px, py, wx, wy);
}

void
CPointFractalRenderer::
iconv(double wx, double wy, double *px, double *py)
{
  CPointFractal::iconv(wx, wy, px, py);
}

void
CPointFractalRenderer::
draw(int iwidth, int iheight)
{
  CPointFractal::draw(0, 0, iwidth - 1, iheight - 1, xmin_, ymin_, xmax_, ymax_, max_iterations_);
}

void
CPointFractalRenderer::
threadDraw(int iwidth, int iheight)
{
  CPointFractal::threadDraw(0, 0, iwidth - 1, iheight - 1,
                            xmin_, ymin_, xmax_, ymax_, max_iterations_, 4, 4);
}
