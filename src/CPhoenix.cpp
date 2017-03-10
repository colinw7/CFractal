#include <CPhoenix.h>
#include <CMathGen.h>

CPhoenix::
CPhoenix()
{
  p_ =  0.56667;
  q_ = -0.5;
}

CPhoenix *
CPhoenix::
dup() const
{
  return new CPhoenix;
}

int
CPhoenix::
calc(double x, double y, int max_iterations) const
{
  double zi   = 0.0;
  double zii  = 0.0;
  double zr   = y;
  double zri  = x;

  double zr2  = 0.0;
  double zri2 = 0.0;

  int iteration = -1;

  double angle;
  double zrt, zrit;

  while (zr2 + zri2 < 4.0 && iteration < max_iterations) {
    zr2  = zr*zr;
    zri2 = zri*zri;

    zrt  = zr2 - zri2 + p_ + q_*zi;
    zrit = 2.0*zr*zri + q_*zii;

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
