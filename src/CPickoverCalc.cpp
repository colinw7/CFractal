#include <CPickoverCalc.h>
#include <cmath>

double CPickoverCalc::xmin_ = -1.96;
double CPickoverCalc::ymin_ = -1.85;
double CPickoverCalc::zmin_ = -1.00;
double CPickoverCalc::xmax_ =  1.96;
double CPickoverCalc::ymax_ =  1.94;
double CPickoverCalc::zmax_ =  1.00;

CPickoverCalc::
CPickoverCalc() :
 iteration_start_(0),
 iteration_end_  (50000)
{
}

void
CPickoverCalc::
draw()
{
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;

  double a =  2.24;
  double b =  0.43;
  double c = -0.65;
  double d = -2.43;
  double e =  1.00;

  for (int i = 0; i < iteration_end_; i++) {
    double xt =   sin(a*y) - z*cos(b*y);
    double yt = z*sin(c*x) -   cos(d*y);
    double zt = e*sin(x);

    x = xt;
    y = yt;
    z = zt;

    if (i >= iteration_start_)
      drawPoint(x, y, z);
  }
}
