#include <CCircles.h>
#include <CXLib.h>
#include <CXLibRenderer2D.h>

class CXCircles : public CXWindow, public CCircles {
 private:
  CXLibRenderer2D *renderer_;

 public:
  CXCircles(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  void setDataRange(double xmin, double ymin, double xmax, double ymax);

  void setForeground(const CRGBA &rgba);

  void drawCircle(double x, double y, double r);
  void fillCircle(double x, double y, double r);
};

int
main(int, char **)
{
  CXCircles *circles = new CXCircles(600, 600);

  circles->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXCircles::
CXCircles(int width, int height) :
 CXWindow(width, height)
{
  renderer_ = new CXLibRenderer2D(this);
}

bool
CXCircles::
exposeEvent()
{
  draw();

  return true;
}

bool
CXCircles::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

void
CXCircles::
setDataRange(double xmin, double ymin, double xmax, double ymax)
{
  renderer_->setDataRange(xmin, ymin, xmax, ymax);
}

void
CXCircles::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CXCircles::
drawCircle(double x, double y, double r)
{
  renderer_->drawCircle(CPoint2D(x, y), r);
}

void
CXCircles::
fillCircle(double x, double y, double r)
{
  renderer_->fillCircle(CPoint2D(x, y), r);
}
