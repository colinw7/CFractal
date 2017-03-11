#include <CGLApp.h>
#include <CGLWindow.h>
#include <CPickoverCalc.h>
#include <CGLRenderer3D.h>

class CGLPickoverCalc;

class CGLPickoverWindow : public CGLWindow {
 private:
  CGLPickoverCalc *calc_;
  CGLRenderer3D   *renderer_;
  uint             ind_;

 public:
  CGLPickoverWindow(int x, int y, uint w, uint h);

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

class CGLPickoverCalc : public CPickoverCalc {
 private:
  CGLPickoverWindow *window_;

 public:
  CGLPickoverCalc(CGLPickoverWindow *window);

  void drawPoint(double x, double y, double z);
};

//---------

int
main(int argc, char **argv)
{
  CGLAppInst->init(argc, argv);

  CGLPickoverWindow *window = new CGLPickoverWindow(0, 0, 400, 400);

  window->setup();

  CGLAppInst->mainLoop();

  return 0;
}

//---------

CGLPickoverWindow::
CGLPickoverWindow(int x, int y, uint w, uint h)
{
  init(x, y, w, h);
}

void
CGLPickoverWindow::
setup()
{
  calc_ = new CGLPickoverCalc(this);

  renderer_ = new CGLRenderer3D(this);

  addControl();
}

void
CGLPickoverWindow::
createList()
{
  glNewList(1, GL_COMPILE);

  ind_ = 0;

  calc_->draw();

  glEndList();
}

void
CGLPickoverWindow::
drawPoint(double x, double y, double z)
{
#if 0
  int i1 = ind_ - 1000*(ind_/1000);
  int i2 = i1   -  100*(  i1/ 100);
  int i3 = i2   -   10*(  i2/  10);

  i1 -= i2 + i3;
  i2 -= i3;

  double b = i1/1000.0;
  double g = i2/100.0;
  double r = i3/10.0;
#endif

  double dist = (x*x + y*y + z*z);

  renderer_->setForeground(CRGBA(dist/8.0, dist/8.0, dist/8.0));

  glPointSize(1.0);

  renderer_->drawPoint(x, y, z);

  ++ind_;
}

bool
CGLPickoverWindow::
resizeEvent()
{
  return true;
}

bool
CGLPickoverWindow::
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
CGLPickoverWindow::
buttonPressEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLPickoverWindow::
buttonMotionEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLPickoverWindow::
buttonReleaseEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLPickoverWindow::
keyPressEvent(const CKeyEvent &)
{
  return true;
}

//---------

CGLPickoverCalc::
CGLPickoverCalc(CGLPickoverWindow *window) :
 window_(window)
{
}

void
CGLPickoverCalc::
drawPoint(double x, double y, double z)
{
  window_->drawPoint(x, y, z);
}
