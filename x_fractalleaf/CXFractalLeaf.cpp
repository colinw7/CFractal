#include <CFractalLeaf.h>
#include <CXLib.h>

class CXFractalLeaf : public CXWindow, public CFractalLeaf {
 public:
  CXFractalLeaf(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  void setForeground(const CRGBA &fg);

  void drawPoint(const CIPoint2D &p);
};

int
main(int argc, char **argv)
{
  CXFractalLeaf *leaf = new CXFractalLeaf(600, 600);

  for (int i = 1; i < argc; ++i) {
    if      (strcmp(argv[i], "-sierpinski") == 0)
      leaf->setType(CXFractalLeaf::SIERPINSKI);
    else if (strcmp(argv[i], "-fern") == 0)
      leaf->setType(CXFractalLeaf::FERN);
    else if (strcmp(argv[i], "-tree") == 0)
      leaf->setType(CXFractalLeaf::TREE);
    else if (strcmp(argv[i], "-cantor") == 0)
      leaf->setType(CXFractalLeaf::CANTOR);
    else if (strcmp(argv[i], "-circle") == 0)
      leaf->setType(CXFractalLeaf::CIRCLE);
    else if (strcmp(argv[i], "-maple") == 0)
      leaf->setType(CXFractalLeaf::MAPLE);
  }

  leaf->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXFractalLeaf::
CXFractalLeaf(int width, int height) :
 CXWindow(width, height)
{
}

bool
CXFractalLeaf::
exposeEvent()
{
  CXWindow::setBackground(CRGBA(1,1,1));

  CXWindow::clear();

  CFractalLeaf::draw(CXWindow::getWidth(), CXWindow::getHeight());

  return true;
}

bool
CXFractalLeaf::
resizeEvent()
{
  return true;
}

void
CXFractalLeaf::
setForeground(const CRGBA &fg)
{
  CXWindow::setForeground(fg);
}

void
CXFractalLeaf::
drawPoint(const CIPoint2D &p)
{
  CXWindow::drawPoint(p.x, p.y);
}
