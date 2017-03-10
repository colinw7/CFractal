#include <CPointFractal.h>
#include <CRGBA.h>
#include <CTransform2D.h>
#include <CThread.h>

struct CPointFractalThreadData {
  CPointFractal     *fractal;
  int                pixel_xmin, pixel_ymin, pixel_xmax, pixel_ymax;
  double             xmin, ymin, xmax, ymax;
  int                pos;
  int                xpos, ypos;
  int                max_iterations;
  int               *color;
  CPointFractalCalc *calc;
};

static void CPointFractalThreadDraw(void *d);

//------

CPointFractal::
CPointFractal(CPointFractalCalc *calc) :
 calc_(calc)
{
}

CPointFractal::
~CPointFractal()
{
}

void
CPointFractal::
conv(double px, double py, double *wx, double *wy)
{
  double xc = (transform_.getXMin1() + transform_.getXMax1())/2;
  double yc = (transform_.getYMin1() + transform_.getYMax1())/2;

  px -= xc;
  py -= yc;

  double x = px*c_ - py*s_;
  double y = px*s_ + py*c_;

  x += xc;
  y += yc;

  transform_.conv(x, y, wx, wy);
}

void
CPointFractal::
iconv(double wx, double wy, double *px, double *py)
{
  double xc = (transform_.getXMin1() + transform_.getXMax1())/2;
  double yc = (transform_.getYMin1() + transform_.getYMax1())/2;

  double x, y;

  transform_.iconv(wx, wy, &x, &y);

  x -= xc;
  y -= yc;

  *px = x*c_ + y*s_;
  *py = y*c_ - x*s_;

  *px += xc;
  *py += yc;
}

void
CPointFractal::
draw(int pixel_xmin, int pixel_ymin, int pixel_xmax, int pixel_ymax,
     double xmin, double ymin, double xmax, double ymax, int max_iterations)
{
  double a = calc_->getAngle();

  s_ = sin(a);
  c_ = cos(a);

  transform_.setFrom(pixel_xmin, pixel_ymax, pixel_xmax, pixel_ymin);
  transform_.setTo  (xmin, ymin, xmax, ymax);

  calc_->setRange(xmin, ymin, xmax, ymax);

  calc_->initCalc(pixel_xmin, pixel_ymin, pixel_xmax, pixel_ymax,
                  xmin, ymin, xmax, ymax, max_iterations);

  for (int j = pixel_ymin, jj = 0; j <= pixel_ymax; ++j, ++jj) {
    for (int i = pixel_xmin, ii = 0; i <= pixel_xmax; ++i, ++ii) {
      double x, y;

      conv(ii, jj, &x, &y);

      int color = calc_->calc(x, y, max_iterations);

      if (color >= 0)
        setForeground(colors_.getColor(color));

      drawPoint(i, j);
    }
  }
}

void
CPointFractal::
threadDraw(int pixel_xmin, int pixel_ymin, int pixel_xmax, int pixel_ymax,
           double xmin, double ymin, double xmax, double ymax, int max_iterations,
           uint nx, uint ny)
{
  static CPointFractalThreadData threadData[16];

  static std::vector<int> color;

  // setup
  uint pixel_width  = pixel_xmax - pixel_xmin + 1;
  uint pixel_height = pixel_ymax - pixel_ymin + 1;

  uint pdx = pixel_width /nx;
  uint pdy = pixel_height/ny;

  pixel_width  = nx*pdx;
  pixel_height = ny*pdy;

  pixel_xmax = pixel_xmin + pixel_width  - 1;
  pixel_ymax = pixel_ymin + pixel_height - 1;

  double w = xmax - xmin;
  double h = ymax - ymin;

  double dx = w/nx;
  double dy = h/ny;

  int s = pdx*pdy;

  uint n = nx*ny;

  //----

  double a = calc_->getAngle();

  s_ = sin(a);
  c_ = cos(a);

  transform_.setFrom(pixel_xmin, pixel_ymax, pixel_xmax, pixel_ymin);
  transform_.setTo  (xmin, ymin, xmax, ymax);

  calc_->setRange(xmin, ymin, xmax, ymax);

  calc_->initCalc(pixel_xmin, pixel_ymin, pixel_xmax, pixel_ymax,
                  xmin, ymin, xmax, ymax, max_iterations);

  color.resize(pixel_width*pixel_height);

  // process
  double y  = ymin;
  int    py = pixel_ymin;

  for (uint iy = 0, i = 0, pos = 0, ypos = 0; iy < ny; ++iy, ypos += pdy, y += dy, py += pdy) {
    double x  = xmin;
    int    px = pixel_xmin;

    for (uint ix = 0, xpos = 0; ix < nx; ++ix, pos += s, ++i, xpos += pdx, x += dx, px += pdx) {
      CPointFractalThreadData &data = threadData[i];

      data.fractal        = this;
      data.pixel_xmin     = px;
      data.pixel_ymin     = py;
      data.pixel_xmax     = px + pdx - 1;
      data.pixel_ymax     = py + pdy - 1;
      data.xmin           = x;
      data.ymin           = y;
      data.xmax           = x + dx;
      data.ymax           = y + dy;
      data.pos            = pos;
      data.xpos           = xpos;
      data.ypos           = ypos;
      data.max_iterations = max_iterations;
      data.color          = &color[0];
      data.calc           = calc_->dup();
    }
  }

#ifndef NO_THREAD
  std::vector<CThread> threads;

  threads.resize(n);

  for (uint i = 0; i < n; ++i)
    threads[i].start((CThreadProc) CPointFractalThreadDraw, (void *) &threadData[i]);

  // collect
  for (uint i = 0; i < n; ++i)
    threads[i].join();
#else
  for (uint i = 0; i < n; ++i)
    CPointFractalThreadDraw((void *) &threadData[i]);
#endif

  for (uint iy = 0, i = 0; iy < ny; ++iy) {
    for (uint ix = 0; ix < nx; ++ix, ++i) {
      CPointFractalThreadData &data = threadData[i];

      for (int y = data.pixel_ymin, pos = data.pos; y <= data.pixel_ymax; ++y) {
        for (int x = data.pixel_xmin; x <= data.pixel_xmax; ++x, ++pos) {
          int color1 = color[pos];

          if (color1 >= 0)
            setForeground(colors_.getColor(color1));

          drawPoint(x, y);
        }
      }

      delete data.calc;
    }
  }
}

void
CPointFractalThreadDraw(void *d)
{
  CPointFractalThreadData *data = (CPointFractalThreadData *) d;

  int pos = data->pos;

  for (int j = data->pixel_ymin, jj = data->ypos; j <= data->pixel_ymax; ++j, ++jj) {
    for (int i = data->pixel_xmin, ii = data->xpos; i <= data->pixel_xmax; ++i, ++ii, ++pos) {
      double x, y;

      data->fractal->conv(ii, jj, &x, &y);

      data->color[pos] = data->calc->calc(x, y, data->max_iterations);
    }
  }
}
