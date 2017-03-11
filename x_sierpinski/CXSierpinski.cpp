#include <CXLib.h>
#include <CSierpinski.h>
#include <CXLibPixelRenderer.h>

class CXSierpinski : public CXWindow, public CSierpinski {
 private:
  CXLibPixelRenderer *renderer_;

 public:
  CXSierpinski(int width, int height);

  bool exposeEvent();

  bool resizeEvent();
};

class CXSierpinskiRenderer : public CSierpinskiRenderer {
 public:
  CXSierpinskiRenderer(CXLibPixelRenderer *renderer) :
   renderer_(renderer) {
  }

  void clear(const CRGBA &bg);

  void drawPoint(const CIPoint2D &p);

  void setForeground(const CRGBA &fg);

  void fillRectangle(const CIBBox2D &bbox);

 private:
  CXLibPixelRenderer *renderer_;
};

int
main(int argc, char **argv)
{
  CXSierpinski *sierpinski = new CXSierpinski(600, 600);

  for (int i = 1; i < argc; ++i) {
    if      (strcmp(argv[1], "-third") == 0)
      sierpinski->setType(CXSierpinski::TYPE_THIRD);
    else if (strcmp(argv[1], "-root") == 0)
      sierpinski->setType(CXSierpinski::TYPE_ROOT);
    else if (strcmp(argv[1], "-box") == 0)
      sierpinski->setType(CXSierpinski::TYPE_BOX);
  }

  sierpinski->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXSierpinski::
CXSierpinski(int width, int height) :
 CXWindow(width, height)
{
  renderer_ = new CXLibPixelRenderer(this);
}

bool
CXSierpinski::
exposeEvent()
{
  CXSierpinskiRenderer sr(renderer_);

  draw(&sr, renderer_->getWidth(), renderer_->getHeight());

  return true;
}

bool
CXSierpinski::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

//-------

void
CXSierpinskiRenderer::
clear(const CRGBA &bg)
{
  renderer_->setBackground(bg);

  renderer_->clear();
}

void
CXSierpinskiRenderer::
drawPoint(const CIPoint2D &p)
{
  renderer_->drawPoint(p);
}

void
CXSierpinskiRenderer::
setForeground(const CRGBA &fg)
{
  renderer_->setForeground(fg);
}

void
CXSierpinskiRenderer::
fillRectangle(const CIBBox2D &bbox)
{
  renderer_->fillRectangle(bbox);
}
