#include <CDragonOutline.h>
#include <CXLib.h>
#include <CMathGen.h>

class CXDragonOutline : public CXWindow, public CDragonOutline {
 public:
  CXDragonOutline(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  void draw();

  void drawPoint(const CIPoint2D &p);
};

int
main(int argc, char **argv)
{
  CXDragonOutline *outline = new CXDragonOutline(600, 600);

  if (argc == 3) {
    double p, q;

    if (CStrUtil::toReal(argv[1], &p) && CStrUtil::toReal(argv[2], &q))
      outline->setParams(p, q);
  }

  outline->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXDragonOutline::
CXDragonOutline(int width, int height) :
 CXWindow(width, height), CDragonOutline()
{
}

bool
CXDragonOutline::
exposeEvent()
{
  CXWindow::setBackground(CRGBA(1,1,1));

  CXWindow::clear();

  CDragonOutline::draw(CXWindow::getWidth(), CXWindow::getHeight());

  return true;
}

bool
CXDragonOutline::
resizeEvent()
{
  return true;
}

void
CXDragonOutline::
drawPoint(const CIPoint2D &p)
{
  CXWindow::drawPoint(p.x, p.y);
}
