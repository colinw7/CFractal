#include <CPharaoh.h>
#include <CXLib.h>
#include <CXLibRenderer2D.h>

class CXPharaoh : public CXWindow, public CPharaoh {
 private:
  CXLibRenderer2D *renderer_;

 public:
  CXPharaoh(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  void setDataRange(double xmin, double ymin, double xmax, double ymax);

  void setForeground(const CRGBA &rgba);

  void fillCircle(double x, double y, double r);
};

int
main(int, char **)
{
  CXPharaoh *pharaoh = new CXPharaoh(400, 400);

  pharaoh->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXPharaoh::
CXPharaoh(int width, int height) :
 CXWindow(width, height)
{
  renderer_ = new CXLibRenderer2D(this);
}

bool
CXPharaoh::
exposeEvent()
{
  clear();

  draw();

  return true;
}

bool
CXPharaoh::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

void
CXPharaoh::
setDataRange(double xmin, double ymin, double xmax, double ymax)
{
  renderer_->setDataRange(xmin, ymin, xmax, ymax);
}

void
CXPharaoh::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CXPharaoh::
fillCircle(double x, double y, double r)
{
  renderer_->fillCircle(CPoint2D(x, y), r);
}
