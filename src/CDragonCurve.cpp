#include <CDragonCurve.h>
#include <CMathGen.h>

CDragonCurve *
CDragonCurve::
dup() const
{
  return new CDragonCurve;
}

int
CDragonCurve::
calc(double x, double y, int max_iterations) const
{
  int iteration = -1;

  double xx = 0;
  double yy = 0;
  double xy = 0;

  while (iteration < max_iterations && (xx + yy) < 4.0) {
    xx = x*x;
    yy = y*y;
    xy = x*y;

    double t1 = yy - xx;
    double t2 = 2.0*xy;

    double x1 = p_*(t1 + x) + q_*(t2 - y);
    double y1 = q_*(t1 + x) - p_*(t2 - y);

    x = x1;
    y = y1;

    ++iteration;
  }

  int color = 0;

  if (iteration < max_iterations)
    color = 254*iteration/(max_iterations - 1) + 1;

  return color;
}
