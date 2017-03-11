#include <CMandelPhoenix.h>
#include <CMathGen.h>

CMandelPhoenix *
CMandelPhoenix::
dup() const
{
  return new CMandelPhoenix;
}

int
CMandelPhoenix::
calc(double x, double y, int max_iterations) const
{
  double zi   = 0.0;
  double zii  = 0.0;
  double zr   = 0.0;
  double zri  = 0.0;

  double zr2  = 0.0;
  double zri2 = 0.0;

  int iteration = -1;

  double angle;
  double zrt, zrit;

  while (zr2 + zri2 < 4.0 && iteration < max_iterations) {
    zr2  = zr*zr;
    zri2 = zri*zri;

    zrt  = zr2 - zri2 + x + y*zi;
    zrit = 2.0*zr*zri + y*zii;

    zi  = zr;
    zii = zri;
    zr  = zrt;
    zri = zrit;

    ++iteration;
  }

  int color = 0;

  if (iteration < max_iterations) {
    color = 254*iteration/(max_iterations - 1) + 1;

    if (show_vector_) {
      angle = CMathGen::atan2(zr, zi);

      if (angle >= M_PI)
        color = 256 - color;
    }
  }

  return color;
}
