#include <CGLApp.h>
#include <CGLWindow.h>
#include <CGLTexture.h>
#include <CLorenzCalc.h>
#include <CGLRenderer3D.h>

class CGLLorenzCalc;

class CGLLorenzWindow : public CGLWindow {
 private:
  CGLLorenzCalc *calc_;
  CGLRenderer3D *renderer_;
  uint           ind_;
  CGLTexture    *texture_;

 public:
  CGLLorenzWindow(int x, int y, uint w, uint h);

  void setup();

  void createList();

  void drawPoint(double x, double y, double z);

  bool resizeEvent();
  bool exposeEvent();

  bool buttonPressEvent  (const CMouseEvent &event);
  bool buttonMotionEvent (const CMouseEvent &event);
  bool buttonReleaseEvent(const CMouseEvent &event);

  bool keyPressEvent(const CKeyEvent &event);
};

class CGLLorenzCalc : public CLorenzCalc {
 private:
  CGLLorenzWindow *window_;

 public:
  CGLLorenzCalc(CGLLorenzWindow *window);

  void drawPoint(double x, double y, double z);
};

//---------

int
main(int argc, char **argv)
{
  CGLAppInst->init(argc, argv);

  CGLLorenzWindow *window = new CGLLorenzWindow(0, 0, 400, 400);

  window->setup();

  CGLAppInst->mainLoop();

  return 0;
}

//---------

CGLLorenzWindow::
CGLLorenzWindow(int x, int y, uint w, uint h)
{
  init(x, y, w, h);
}

void
CGLLorenzWindow::
setup()
{
  calc_ = new CGLLorenzCalc(this);

  renderer_ = new CGLRenderer3D(this);

  texture_ = new CGLTexture;

  CImageFileSrc src("particle.png");

  CImagePtr image = CImageMgrInst->createImage(src);

  texture_->setImage(image);

  addControl();
}

void
CGLLorenzWindow::
createList()
{
  glNewList(1, GL_COMPILE);

  ind_ = 0;

  calc_->draw();

  glEndList();
}

void
CGLLorenzWindow::
drawPoint(double x, double y, double z)
{
  int i1 = ind_ - 1000*(ind_/1000);
  int i2 = i1   -  100*(  i1/ 100);
  int i3 = i2   -   10*(  i2/  10);

  i1 -= i2 + i3;
  i2 -= i3;

  double b = i1/1000.0;
  double g = i2/100.0;
  double r = i3/10.0;

  renderer_->setForeground(CRGBA(r, g, b));

  renderer_->drawPoint(CPoint3D(x, y, z), texture_);

  //glPointSize(2.0);

  //renderer_->drawPoint(CPoint3D(x, y, z));

  ++ind_;
}

bool
CGLLorenzWindow::
resizeEvent()
{
  return true;
}

bool
CGLLorenzWindow::
exposeEvent()
{
  static bool has_list;

  renderer_->clear(CRGBA(0,0,0));

  renderer_->setForeground(CRGBA(1,1,1));

  if (! has_list) {
    createList();

    has_list = true;
  }

  glCallList(1);

  return true;
}

bool
CGLLorenzWindow::
buttonPressEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLLorenzWindow::
buttonMotionEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLLorenzWindow::
buttonReleaseEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLLorenzWindow::
keyPressEvent(const CKeyEvent &)
{
  return true;
}

//---------

CGLLorenzCalc::
CGLLorenzCalc(CGLLorenzWindow *window) :
 window_(window)
{
}

void
CGLLorenzCalc::
drawPoint(double x, double y, double z)
{
  window_->drawPoint(x, y, z);
}
