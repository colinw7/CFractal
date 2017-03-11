#include <CScenery.h>
#include <CXLib.h>
#include <CXLibPixelRenderer.h>

class CXScenery : public CXWindow, public CScenery {
 private:
  CXLibPixelRenderer *renderer_;

 public:
  CXScenery(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  bool buttonPressEvent(const CMouseEvent &event);

  bool keyPressEvent(const CKeyEvent &event);

  void setForeground(const CRGBA &rgba);

  void drawPoint(uint x, uint y);
};

int
main(int, char **)
{
  CXScenery *plasma = new CXScenery(600, 600);

  plasma->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXScenery::
CXScenery(int width, int height) :
 CXWindow(width, height)
{
  renderer_ = new CXLibPixelRenderer(this);
}

bool
CXScenery::
exposeEvent()
{
  clear();

  draw();

  return true;
}

bool
CXScenery::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

bool
CXScenery::
buttonPressEvent(const CMouseEvent &)
{
  grow();

  expose();

  return true;
}

bool
CXScenery::
keyPressEvent(const CKeyEvent &)
{
  grow();

  expose();

  return true;
}

void
CXScenery::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CXScenery::
drawPoint(uint x, uint y)
{
  renderer_->drawPoint(CIPoint2D(x, y));
}
