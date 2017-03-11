#include <CPlasma.h>
#include <CXLib.h>
#include <CXLibPixelRenderer.h>

class CXPlasma : public CXWindow, public CPlasma {
 private:
  CXLibPixelRenderer *renderer_;

 public:
  CXPlasma(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  bool idleEvent();

  void setForeground(const CRGBA &rgba);

  void drawPoint(uint x, uint y);

  void drawLine(uint x1, uint y1, uint x2, uint y2);
};

int
main(int, char **)
{
  CXPlasma *plasma = new CXPlasma(600, 600);

  plasma->map();

  CXMachineInst->mainLoop(10000, plasma->getXEventAdapter());

  return 0;
}

CXPlasma::
CXPlasma(int width, int height) :
 CXWindow(width, height), CPlasma(width, height)
{
  renderer_ = new CXLibPixelRenderer(this);
}

bool
CXPlasma::
exposeEvent()
{
  clear();

  //drawSimpleSine();
  //drawSine();
  //drawDoubleSine();
  //drawMovingSine();
  //drawBasicPlasma();
  drawRealPlasma();

  return true;
}

bool
CXPlasma::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

bool
CXPlasma::
idleEvent()
{
  //exposeEvent();

  expose();

  return true;
}

void
CXPlasma::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CXPlasma::
drawPoint(uint x, uint y)
{
  renderer_->drawPoint(CIPoint2D(x, y));
}

void
CXPlasma::
drawLine(uint x1, uint y1, uint x2, uint y2)
{
  renderer_->drawLine(CIPoint2D(x1, y1), CIPoint2D(x2, y2));
}
