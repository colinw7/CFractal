#include <CJulia.h>
#include <CMathGen.h>

CJulia::
CJulia(double cr, double ci) :
 cr_(cr), ci_(ci)
{
}

void
CJulia::
setTime(double t)
{
  double a = 2.0*t*M_PI;

  cr_ = 0.5*(1 + cos(a));
  ci_ = 0.5*(1 + sin(a));
}

int
CJulia::
calc(double x, double y, int max_iterations) const
{
  int num_iterations = iterate(x, y, max_iterations);

  if (num_iterations < 0 || num_iterations >= max_iterations)
    return 0;

  int color = 254*num_iterations/(max_iterations - 1) + 1;

  if (show_vector_) {
    double angle = CMathGen::atan2(zr_, zi_);

    if (angle >= M_PI)
      color = 256 - color;
  }

  return color;
}

int
CJulia::
iterate(double x, double y, int max_iterations) const
{
  int num_iterations = -1;

  zr_ = x;
  zi_ = y;

  double zr2 = zr_*zr_;
  double zi2 = zi_*zi_;

  double zri;

  while (zi2 + zr2 < 4.0 && num_iterations < max_iterations) {
    zri = zr_*zi_;

    zr_ = zr2 - zi2 + cr_;
    zi_ = zri + zri + ci_;

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++num_iterations;
  }

  return num_iterations;
}
