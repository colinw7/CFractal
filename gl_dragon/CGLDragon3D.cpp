#include <CGLApp.h>
#include <CGLWindow.h>
#include <CGLRenderer3D.h>
#include <CMathRand.h>
#include <CStrUtil.h>

class CGLDragon3DWindow : public CGLWindow {
 private:
  CGLRenderer3D *renderer_;
  double         qval_;

 public:
  CGLDragon3DWindow(int x, int y, uint w, uint h);

  void setQ(double q) { qval_ = q; }

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

//---------

int
main(int argc, char **argv)
{
  CGLAppInst->init(argc, argv);

  CGLDragon3DWindow *dragon = new CGLDragon3DWindow(0, 0, 400, 400);

  if (argc == 2) {
    double q;

    if (CStrUtil::toReal(argv[1], &q))
      dragon->setQ(q);
  }

  dragon->setup();

  CGLAppInst->mainLoop();

  return 0;
}

//---------

CGLDragon3DWindow::
CGLDragon3DWindow(int x, int y, uint w, uint h)
{
  qval_ = 0.967;

  init(x, y, w, h);
}

void
CGLDragon3DWindow::
setup()
{
  renderer_ = new CGLRenderer3D(this);

  addControl();
}

void
CGLDragon3DWindow::
drawPoint(double x, double y, double z)
{
  //glPointSize(2.0);

  renderer_->drawPoint(x, y, z);
}

bool
CGLDragon3DWindow::
resizeEvent()
{
  return true;
}

bool
CGLDragon3DWindow::
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
CGLDragon3DWindow::
buttonPressEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLDragon3DWindow::
buttonMotionEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLDragon3DWindow::
buttonReleaseEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLDragon3DWindow::
keyPressEvent(const CKeyEvent &)
{
  return true;
}

void
CGLDragon3DWindow::
createList()
{
  glNewList(1, GL_COMPILE);

  uint num_iterations = 5000;

  double kmin = -3.0;
  double kmax =  3.0;
  double kd   =  0.1;

  for (double k = kmin; k <= kmax; k += kd) {
    double g = (k - kmin)/(kmax - kmin);

    renderer_->setForeground(CRGBA(g, g, g));

    double x = 0.500001;
    double y = 0;

    double mag, q;

    if (qval_ == 0.0) {
      mag = 1;
      q   = 4*sqrt(1 - k*k);
    }
    else {
      mag = k*k + qval_*qval_;
      q   = -4*qval_/mag;
    }

    double p = 4*k/mag;

    for (uint i = 0; i < num_iterations; ++i) {
      double tx = x*p - y*q;

      y = x*q + y*p;

      double ty = y;

      x = 1 - tx;

      mag = sqrt(x*x + y*y);

      y = sqrt((-x + mag)/2);
      x = sqrt(( x + mag)/2);

      if (ty < 0)
        x = -x;

      int b = CMathRand::randInRange(0, 1);

      if (b) {
        x = -x;
        y = -y;
      }

      x = (1 - x)/2;
      y = y/2;

      double z = p/2;

      if (i > 20)
        drawPoint(x, y, z);
    }
  }

  glEndList();
}
