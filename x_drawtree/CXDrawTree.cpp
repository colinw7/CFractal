#include <CDrawTree.h>
#include <CXLib.h>
#include <CXLibRenderer2D.h>

class CXDrawTree : public CXWindow, public CDrawTree {
 public:
  CXDrawTree(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  void setDataRange(double xmin, double ymin, double xmax, double ymax);

  void setForeground(const CRGBA &rgba);

  void setLineWidth(double width);

  void drawLine(double x1, double y1, double x2, double y2);

 private:
  CXLibRenderer2D *renderer_;
};

int
main(int argc, char **argv)
{
  CXDrawTree *tree = new CXDrawTree(600, 600);

  std::string filename;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-')
      continue;
    else
      filename = argv[i];
  }

  if (filename != "")
    tree->read(filename);

  tree->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXDrawTree::
CXDrawTree(int width, int height) :
 CXWindow(width, height)
{
  renderer_ = new CXLibRenderer2D(this);
}

bool
CXDrawTree::
exposeEvent()
{
  clear();

  draw();

  return true;
}

bool
CXDrawTree::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

void
CXDrawTree::
setDataRange(double xmin, double ymin, double xmax, double ymax)
{
  renderer_->setDataRange(xmin, ymin, xmax, ymax);
}

void
CXDrawTree::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CXDrawTree::
drawLine(double x1, double y1, double x2, double y2)
{
  renderer_->drawLine(CPoint2D(x1, y1), CPoint2D(x2, y2));
}

void
CXDrawTree::
setLineWidth(double width)
{
  renderer_->setLineWidth(width);
}
