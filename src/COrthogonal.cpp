#include <COrthogonal.h>
#include <CMathGen.h>

#include <complex>

COrthogonal::
COrthogonal(Type type) :
 type_(type)
{
  setType(type_);
}

COrthogonal *
COrthogonal::
dup() const
{
  return new COrthogonal(type_);
}

void
COrthogonal::
setType(Type type)
{
  type_ = type;

  switch (type_) {
    case T5:
      xmin_ = -1.60; ymin_ = -0.75; xmax_ = 1.6; ymax_ = 0.75;
      break;
    case C6:
      xmin_ = -1.00; ymin_ = -0.32; xmax_ = 1.0; ymax_ = 0.32;
      break;
    case P4:
      xmin_ = -0.60; ymin_ = -0.40; xmax_ = 0.6; ymax_ = 0.40;
      break;
    case P6:
      xmin_ = -0.60; ymin_ = -0.40; xmax_ = 0.6; ymax_ = 0.40;
      break;
    case L4:
      xmin_ =  0.25; ymin_ = -1.40; xmax_ = 4.0; ymax_ = 1.40;
      break;
    case H4:
      xmin_ = -0.10; ymin_ = -0.60; xmax_ = 0.1; ymax_ = 0.06;
      break;
  }
}

int
COrthogonal::
calc(double x, double y, int max_iterations) const
{
  int iteration = 0;

  if      (type_ == T5)
    iteration = iterate_t5(x, y, max_iterations);
  else if (type_ == C6)
    iteration = iterate_c6(x, y, max_iterations);
  else if (type_ == P4)
    iteration = iterate_p4(x, y, max_iterations);
  else if (type_ == P6)
    iteration = iterate_p6(x, y, max_iterations);
  else if (type_ == L4)
    iteration = iterate_l4(x, y, max_iterations);
  else if (type_ == H4)
    iteration = iterate_h4(x, y, max_iterations);

  int color = 0;

  if (iteration < max_iterations) {
    color = 254*iteration/(max_iterations - 1) + 1;

    if (show_vector_) {
      double angle = CMathGen::atan2(zr_, zi_);

      if (angle >= M_PI)
        color = 256 - color;
    }
  }

  return color;
}

int
COrthogonal::
iterate_t5(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zr2 + zi2 < 10000.0 && iteration < max_iterations) {
    std::complex<double> z(zr_, zi_);

    std::complex<double> z3 = z*z*z;
    std::complex<double> z5 = z*z*z3;

    z = c*(16.0*z5 - 20.0*z3 + 5.0*z);

    zr_ = z.real();
    zi_ = z.imag();

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
COrthogonal::
iterate_c6(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zr2 + zi2 < 10000.0 && iteration < max_iterations) {
    std::complex<double> z(zr_, zi_);

    std::complex<double> z2 = z*z;
    std::complex<double> z4 = z2*z2;
    std::complex<double> z6 = z2*z4;

    z = c*(z6 - 6.0*z4 + 9.0*z2 - 2.0);

    zr_ = z.real();
    zi_ = z.imag();

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
COrthogonal::
iterate_p4(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zr2 + zi2 < 10000.0 && iteration < max_iterations) {
    std::complex<double> z(zr_, zi_);

    std::complex<double> z2 = z*z;
    std::complex<double> z4 = z2*z2;

    z = 0.125*(35.0*z4 - 30.0*z2 + 3.0) + c;

    zr_ = z.real();
    zi_ = z.imag();

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
COrthogonal::
iterate_p6(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zr2 + zi2 < 10000.0 && iteration < max_iterations) {
    std::complex<double> z(zr_, zi_);

    std::complex<double> z2 = z*z;
    std::complex<double> z4 = z2*z2;
    std::complex<double> z6 = z4*z2;

    z = 0.0625*(231.0*z6 - 315.0*z4 + 105.0*z2 - 5.0) + c;

    zr_ = z.real();
    zi_ = z.imag();

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
COrthogonal::
iterate_l4(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zr2 + zi2 < 10000.0 && iteration < max_iterations) {
    std::complex<double> z(zr_, zi_);

    std::complex<double> z2 = z*z;
    std::complex<double> z3 = z*z2;
    std::complex<double> z4 = z2*z2;
  //std::complex<double> z6 = z4*z2;

    z = (z4 - 16.0*z3 + 72.0*z2 - 96.0*z + 24.0)/24.0 + c;

    zr_ = z.real();
    zi_ = z.imag();

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
COrthogonal::
iterate_h4(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zr2 + zi2 < 10000.0 && iteration < max_iterations) {
    std::complex<double> z(zr_, zi_);

    std::complex<double> z2 = z*z;
    std::complex<double> z4 = z2*z2;

    z = (16.0*z4 - 48.0*z2 + 12.0)/12.0 + c;

    zr_ = z.real();
    zi_ = z.imag();

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}
