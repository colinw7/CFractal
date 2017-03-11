#include <CPikePeak.h>
#include <CXLib.h>
#include <CMathRand.h>

class CXPikePeak : public CXWindow, public CPikePeak {
 public:
  CXPikePeak();

  bool exposeEvent();

  bool resizeEvent();

  void clear(const CRGBA &rgba);

  void setForeground(const CRGBA &rgba);

  void fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3);
};

int
main(int, char **)
{
  CXPikePeak *peak = new CXPikePeak;

  CMathRand::seedRand(time(NULL));

  peak->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXPikePeak::
CXPikePeak() :
 CXWindow(600, 600)
{
}

bool
CXPikePeak::
exposeEvent()
{
  CPikePeak::draw(CXWindow::getWidth(), CXWindow::getHeight());

  return true;
}

bool
CXPikePeak::
resizeEvent()
{
  return true;
}

void
CXPikePeak::
clear(const CRGBA &rgba)
{
  CXWindow::setBackground(rgba);

  CXWindow::clear();
}

void
CXPikePeak::
setForeground(const CRGBA &rgba)
{
  CXWindow::setForeground(rgba);
}

void
CXPikePeak::
fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3)
{
  double x[3];
  double y[3];

  x[0] = p1.x; y[0] = p1.y;
  x[1] = p2.x; y[1] = p2.y;
  x[2] = p3.x; y[2] = p3.y;

  CXWindow::fillPolygon(x, y, 3);
}
