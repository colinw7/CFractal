#include <CSedona.h>
#include <CXLib.h>
#include <CMathRand.h>

class CXSedona : public CXWindow, public CSedona {
 public:
  CXSedona();

  bool exposeEvent();

  bool resizeEvent();

  void clear(const CRGBA &rgba);

  void setForeground(const CRGBA &rgba);

  void fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3);
};

int
main(int, char **)
{
  CXSedona *sedona = new CXSedona;

  CMathRand::seedRand(time(NULL));

  sedona->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXSedona::
CXSedona() :
 CXWindow(600, 600)
{
}

bool
CXSedona::
exposeEvent()
{
  CSedona::draw(CXWindow::getWidth(), CXWindow::getHeight());

  return true;
}

bool
CXSedona::
resizeEvent()
{
  return true;
}

void
CXSedona::
clear(const CRGBA &rgba)
{
  CXWindow::setBackground(rgba);

  CXWindow::clear();
}

void
CXSedona::
setForeground(const CRGBA &rgba)
{
  CXWindow::setForeground(rgba);
}

void
CXSedona::
fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3)
{
  double x[3];
  double y[3];

  x[0] = p1.x; y[0] = p1.y;
  x[1] = p2.x; y[1] = p2.y;
  x[2] = p3.x; y[2] = p3.y;

  CXWindow::fillPolygon(x, y, 3);
}
