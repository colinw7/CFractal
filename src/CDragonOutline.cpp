#include <CDragonOutline.h>
#include <CMathRand.h>

CDragonOutline::
CDragonOutline()
{
  p_ = 1.646009;
  q_ = 0.967049;
}

void
CDragonOutline::
setParams(double p, double q)
{
  p_ = p;
  q_ = q;
}

void
CDragonOutline::
draw(int w, int h)
{
  //double xmin =  1E50; double ymin =  1E50;
  //double xmax = -1E50; double ymax = -1E50;
  double xmin = -0.2;
  double ymin = -0.7;
  double xmax =  1.2;
  double ymax =  0.7;

  double x = 0.500001;
  double y = 0;

  double mag = p_*p_ + q_*q_;

  double p =  4*p_/mag;
  double q = -4*q_/mag;

  //double scale = 1.0;

  uint num_iterations = 50000;

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

    //xmin = min(x, xmin); ymin = min(y, ymin);
    //xmax = max(x, xmax); ymax = max(y, ymax);

    int x1 = (w - 1)*((x - xmin)/(xmax - xmin));
    int y1 = (h - 1)*((y - ymax)/(ymin - ymax));

    drawPoint(CIPoint2D(x1, y1));
  }

  //cerr << xmin << " " << ymin << " " << xmax << " " << ymax << endl;
}
