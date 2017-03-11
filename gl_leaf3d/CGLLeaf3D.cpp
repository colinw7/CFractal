#include <CGLApp.h>
#include <CGLWindow.h>
#include <CGLRenderer3D.h>
#include <CMathRand.h>

class CGLLeaf3DCalc;

class CGLLeaf3DWindow : public CGLWindow {
 private:
  CGLRenderer3D *renderer_;

 public:
  CGLLeaf3DWindow(int x, int y, uint w, uint h);

  void setup();

  void createList();

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

  CGLLeaf3DWindow *window = new CGLLeaf3DWindow(0, 0, 400, 400);

  window->setup();

  CGLAppInst->mainLoop();

  return 0;
}

//---------

CGLLeaf3DWindow::
CGLLeaf3DWindow(int x, int y, uint w, uint h)
{
  init(x, y, w, h);
}

void
CGLLeaf3DWindow::
setup()
{
  renderer_ = new CGLRenderer3D(this);

  addControl();
}

void
CGLLeaf3DWindow::
createList()
{
  glNewList(1, GL_COMPILE);

  uint   nd   = 4;
  double a[4] = { 0.00,  0.83,  0.22, -0.22};
  double b[4] = { 0.00,  0.00, -0.23,  0.23};
  double c[4] = { 0.00,  0.00,  0.00,  0.00};
  double d[4] = { 0.06,  0.00,  0.24,  0.24};
  double e[4] = { 0.18,  0.86,  0.22,  0.22};
  double f[4] = { 0.00,  0.10,  0.00,  0.00};
  double g[4] = { 0.00,  0.00,  0.00,  0.00};
  double h[4] = { 0.00, -0.12,  0.00,  0.00};
  double m[4] = { 0.00,  0.84,  0.32,  0.32};
  double n[4] = { 0.00,  0.00,  0.00,  0.00};
  double q[4] = { 0.00,  1.62,  0.82,  0.82};
  double r[4] = { 0.00,  0.00,  0.00,  0.00};
  uint   p[4] = {    1,    85,    92,   100};

  double x = 0;
  double y = 0;
  double z = 0;

  uint num_iterations = 50000;

  for (uint i = 0; i < num_iterations; ++i) {
    uint percent = CMathRand::randInRange(0, 99);

    double x1, y1, z1;

    CRGBA rgba(0.4,1,0.4);

    for (uint j = 0; j < nd; ++j) {
      if (percent < p[j]) {
        x1 = a[j]*x + b[j]*y + c[j]*z + n[j];
        y1 = d[j]*x + e[j]*y + f[j]*z + q[j];
        z1 = g[j]*x + h[j]*y + m[j]*z + r[j];
        break;
      }
    }

    x = x1;
    y = y1;
    z = z1;

    renderer_->setForeground(rgba);

    renderer_->drawPoint(x, y, z);
  }

  glEndList();
}

bool
CGLLeaf3DWindow::
resizeEvent()
{
  return true;
}

bool
CGLLeaf3DWindow::
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
CGLLeaf3DWindow::
buttonPressEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLLeaf3DWindow::
buttonMotionEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLLeaf3DWindow::
buttonReleaseEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLLeaf3DWindow::
keyPressEvent(const CKeyEvent &)
{
  return true;
}
