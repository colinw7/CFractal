#include <CLunar.h>
#include <CXLib.h>
#include <CMathGen.h>
#include <CMathRand.h>

class CXLunar : public CXWindow, public CLunar {
 public:
  CXLunar();

  bool exposeEvent();

  bool resizeEvent();

  void clear(const CRGBA &rgba);

  void setForeground(const CRGBA &rgba);

  void fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3);

  void fillEllipse(const CIPoint2D &c, int cx, int yr);

  void drawPoint(const CIPoint2D &p);
};

int
main(int, char **)
{
  CXLunar *lunar = new CXLunar;

  CMathRand::seedRand(time(NULL));

  lunar->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXLunar::
CXLunar() :
 CXWindow(600, 600)
{
}

bool
CXLunar::
exposeEvent()
{
  CLunar::draw(CXWindow::getWidth(), CXWindow::getHeight());

  return true;
}

bool
CXLunar::
resizeEvent()
{
  return true;
}

void
CXLunar::
clear(const CRGBA &rgba)
{
  CXWindow::setBackground(rgba);

  CXWindow::clear();
}

void
CXLunar::
setForeground(const CRGBA &rgba)
{
  CXWindow::setForeground(rgba);
}

void
CXLunar::
fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3)
{
  double x[3];
  double y[3];

  x[0] = p1.x; y[0] = p1.y;
  x[1] = p2.x; y[1] = p2.y;
  x[2] = p3.x; y[2] = p3.y;

  CXWindow::fillPolygon(x, y, 3);
}

void
CXLunar::
fillEllipse(const CIPoint2D &c, int xr, int yr)
{
  CXWindow::fillEllipse(c.x, c.y, xr, yr);
}

void
CXLunar::
drawPoint(const CIPoint2D &p)
{
  CXWindow::drawPoint(p.x, p.y);
}
