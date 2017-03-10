#include <CBifuricationLib.h>
#include <algorithm>

CBifurication::
CBifurication()
{
  feigenbaum_ = false;

  min_iterations_ = 64;
  max_iterations_ = 256;

  rmin_ = 0.0;
  rmax_ = 4.0;
  ymin_ = 0.0;
  ymax_ = 1.0;
  yset_ = false;
}

CBifurication::
~CBifurication()
{
}

void
CBifurication::
setFeigenbaum(bool feigenbaum)
{
  feigenbaum_ = feigenbaum;
}

void
CBifurication::
setRRange(double rmin, double rmax)
{
  rmin_ = rmin;
  rmax_ = rmax;
}

void
CBifurication::
draw(int width, int height)
{
  if (! yset_) {
    double rinc = (rmax_ - rmin_)/99;

    double r = rmin_ + rinc;

    bool range_set = false;

    for (int px = 0; px < 100; ++px) {
      double y = 0.5;

      for (int i = 0; i < max_iterations_; i++) {
        y = r*y*(1.0 - y);

        if (y < -1E6 || y > 1E6)
          break;

        if (i < min_iterations_ || y < 0.0)
          continue;

        double y1 = y;

        if (feigenbaum_)
          y1 /= r;

        if (! range_set) {
          ymin_ = y1;
          ymax_ = y1;

          range_set = true;
        }
        else {
          ymin_ = std::min(ymin_, y1);
          ymax_ = std::max(ymax_, y1);
        }
      }

      r += rinc;
    }

    yset_ = true;
  }

  double rinc = (rmax_ - rmin_)/(width - 1);

  double r = rmin_ + rinc;

  for (int px = 0; px < width; ++px) {
    double y = 0.5;

    for (int i = 0; i < max_iterations_; i++) {
      y = r*y*(1.0 - y);

      if (y < -1E6 || y > 1E6)
        break;

      if (i < min_iterations_ || y < 0.0)
        continue;

      double y1 = y;

      if (feigenbaum_)
        y1 /= r;

      int py = (int) ((height - 1)*(ymax_ - y1)/(ymax_ - ymin_));

      drawPoint(px, py);
    }

    r += rinc;
  }
}
