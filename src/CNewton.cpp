#include <CNewton.h>
#include <CMathGen.h>

CNewton::
CNewton()
{
}

CNewton *
CNewton::
dup() const
{
  return new CNewton;
}

int
CNewton::
calc(double x, double y, int max_iterations) const
{
  return calc2(x, y, max_iterations);
}

int
CNewton::
calc1(double x, double y, int max_iterations) const
{
  int num_iterations = -1;

  double xx = 0;
  double yy = 0;

  double x1 = 1E50;
  double y1 = 1E50;

  while (num_iterations < max_iterations) {
    xx = x*x;
    yy = y*y;

    double denom = 3*((xx - yy)*(xx - yy) + 4*xx*yy);

    if (denom == 0.0)
      denom = 1E-6;

    x = 2.0*x/3.0 + (xx - yy)/denom;
    y = 2.0*y/3.0 - 2.0*x*y/denom;

    if (fabs(x1 - x) < 1E-6 && fabs(y1 - y) < 1E-6) break;

    x1 = x;
    y1 = y;

    ++num_iterations;
  }

  // roots x =  1  , y =  0.0000
  //       x = -0.5, y =  0.8666
  //       x = -0.5, y = -0.8666

  int color;

  double d = (1.0*(max_iterations - num_iterations))/max_iterations;

  double d1 = fabs((x - 1.0)*(x - 1.0) + (y - 0.0000)*(y - 0.0000));
  double d2 = fabs((x + 0.5)*(x + 0.5) + (y - 0.8666)*(y - 0.8666));
  double d3 = fabs((x + 0.5)*(x + 0.5) + (y + 0.8666)*(y + 0.8666));

  if      (d1 < d2 && d1 < d3)
    color = 85*d + 1;
  else if (d2 < d3)
    color = 85*d + 86;
  else
    color = 85*d + 171;

  return color;
}

int
CNewton::
calc2(double x, double y, int max_iterations) const
{
  int num_iterations = -1;

  double xx = 0;
  double yy = 0;

  double x1 = 1E50;
  double y1 = 1E50;

  while (num_iterations < max_iterations) {
    xx = x*x;
    yy = y*y;

    double denom = 3*xx - 3*yy - 2;

    denom = denom*denom + 36*xx*yy;

    if (denom == 0.0)
      denom = 1E-6;

    double t1 = x*xx - 3*x*yy - 2*x - 5;
    double t2 = 3*xx - 3*yy - 2;
    double t3 = 3*xx*y - yy*y - 2*y;

    x = x - (t1*t2 - 6*x*y*t3)/denom;
    y = y - (t2*t3 - 6*x*y*t1)/denom;

    if (fabs(x1 - x) < 1E-6 && fabs(y1 - y) < 1E-6) break;

    x1 = x;
    y1 = y;

    ++num_iterations;
  }

  int color;

  double d = (1.0*(max_iterations - num_iterations))/max_iterations;

  if      (x > 0)
    color = 85*d + 1;
  else if (y > 0)
    color = 85*d + 86;
  else
    color = 85*d + 171;

  return color;
}
