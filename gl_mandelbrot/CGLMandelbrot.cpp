#include <CGLApp.h>
#include <CGLWindow.h>
#include <CGLRenderer3D.h>
#include <CMandelbrot.h>
#include <vector>
#include <iostream>

class CGLMandelbrot : public CGLWindow {
 private:
  CGLRenderer3D *renderer_;
  CMandelbrot   *mandelbrot_;

 public:
  CGLMandelbrot();

  void setup();

  void setRange(double xmin, double ymin, double xmax, double ymax) {
    mandelbrot_->setRange(xmin, ymin, xmax, ymax);
  }

  bool resizeEvent();
  bool exposeEvent();

  bool buttonPressEvent  (const CMouseEvent &event);
  bool buttonMotionEvent (const CMouseEvent &event);
  bool buttonReleaseEvent(const CMouseEvent &event);

  bool keyPressEvent(const CKeyEvent &event);

  void createList();

  void draw();
};

int
main(int argc, char **argv)
{
  CGLAppInst->init(argc, argv);

  CGLMandelbrot *mandelbrot = new CGLMandelbrot;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (argv[i][1] == 'r') {
        if (i >= argc - 4)
          std::cerr << "Missing values for " << argv[i] << std::endl;
        else {
          double xmin, ymin, xmax, ymax;

          if (CStrUtil::toReal(argv[i + 1], &xmin) &&
              CStrUtil::toReal(argv[i + 2], &ymin) &&
              CStrUtil::toReal(argv[i + 3], &xmax) &&
              CStrUtil::toReal(argv[i + 4], &ymax)) {
            mandelbrot->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  mandelbrot->setup();

  CGLAppInst->mainLoop();

  return 0;
}

CGLMandelbrot::
CGLMandelbrot()
{
  init(0, 0, 400, 400);
}

void
CGLMandelbrot::
setup()
{
  renderer_ = new CGLRenderer3D(this);

  mandelbrot_ = new CMandelbrot;

  mandelbrot_->setDistance(true);

  addControl();

  enableDispAttr();
}

bool
CGLMandelbrot::
resizeEvent()
{
  return true;
}

bool
CGLMandelbrot::
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
CGLMandelbrot::
buttonPressEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLMandelbrot::
buttonMotionEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLMandelbrot::
buttonReleaseEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLMandelbrot::
keyPressEvent(const CKeyEvent &)
{
  return true;
}

void
CGLMandelbrot::
createList()
{
  glNewList(1, GL_COMPILE);

  draw();

  glEndList();
}

void
CGLMandelbrot::
draw()
{
  CColorRange colors;

  int s = 400;

  CTransform2D transform_;

  transform_.setFrom(0, 0, s - 1, s - 1);

  double xmin = mandelbrot_->getXMin();
  double ymin = mandelbrot_->getYMin();
  double xmax = mandelbrot_->getXMax();
  double ymax = mandelbrot_->getYMax();

  int max_iterations = 128;

  transform_.setTo(xmin, ymin, xmax, ymax);

  std::vector<double> x_store, y_store;

  x_store.resize(s);
  y_store.resize(s);

  double dummy;

  for (int i = 0, ii = 0; i < s; ++i, ++ii)
    transform_.conv(i, 0, &x_store[ii], &dummy);

  for (int j = 0, jj = 0; j < s; ++j, ++jj)
    transform_.conv(0, j, &dummy, &y_store[jj]);

  mandelbrot_->setRange(xmin, ymin, xmax, ymax);

  mandelbrot_->initCalc(0, 0, s - 1, s - 1, xmin, ymin, xmax, ymax,
                        max_iterations);

  std::vector<int> data;

  double s2 = s*s;

  data.resize(s2);

  for (int j = 0; j < s; ++j) {
    double y = y_store[j];

    for (int i = 0; i < s; ++i) {
      double x = x_store[i];

      data[j*s + i] = mandelbrot_->calc(x, y, max_iterations);
    }
  }

  std::vector<CPoint3D> points;

  points.resize(4);

  for (int j = 1; j < s; ++j) {
    for (int i = 1; i < s; ++i) {
      int color1 = data[ j     *s + i - 1];
      int color2 = data[ j     *s + i    ];
      int color3 = data[(j - 1)*s + i    ];
      int color4 = data[(j - 1)*s + i - 1];

      int color = (color1 + color2 + color3 + color4)/4;

      renderer_->setForeground(colors.getColor(color));

      points[0] = CPoint3D(i - 1, j    , color1/10.0);
      points[1] = CPoint3D(i    , j    , color2/10.0);
      points[2] = CPoint3D(i    , j - 1, color3/10.0);
      points[3] = CPoint3D(i - 1, j - 1, color4/10.0);

      renderer_->fillPolygon(points);
    }
  }
}
