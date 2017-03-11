#include <CLorenzCalc.h>
#include <CRungeKutta.h>

double CLorenzCalc::xmin_ = -17.99;
double CLorenzCalc::ymin_ = -24.15;
double CLorenzCalc::zmin_ =   0.00;
double CLorenzCalc::xmax_ =  19.83;
double CLorenzCalc::ymax_ =  27.64;
double CLorenzCalc::zmax_ =  48.31;

class FnX {
 public:
  double operator()(double, double x, double y, double) {
    return 10.0*(y - x);
  }
};

class FnY {
 public:
  double operator()(double, double x, double y, double z) {
    return (x*(28.0 - z) - y);
  }
};

class FnZ {
 private:
  double c_;

 public:
  FnZ() { c_ = 8.0/3.0; }

  double operator()(double, double x, double y, double z) {
    return (x*y - c_*z);
  }
};

CLorenzCalc::
CLorenzCalc() :
 iteration_start_(0),
 iteration_end_  (8000)
{
}

void
CLorenzCalc::
draw()
{
  double ix = 0.0;
  double iy = 1.0;
  double iz = 0.0;

  double dt = 0.01;

  CRungeKuttaXYZ<FnX, FnY, FnZ> runge_kutta(0, ix, iy, iz, dt);

  for (int i = 0; i < iteration_end_; i++) {
    runge_kutta.step();

    if (i >= iteration_start_)
      drawPoint(runge_kutta.getX(),
                runge_kutta.getY(),
                runge_kutta.getZ());
  }
}
