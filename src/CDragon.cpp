#include <CDragon.h>
#include <CMathGen.h>

CDragon *
CDragon::
dup() const
{
  return new CDragon;
}

int
CDragon::
calc(double x, double y, int max_iterations) const
{
  double zr = 0.5;
  double zi = 0.0;

  int iteration = -1;

  double angle;
  double zrt, zit;

  while (zr*zr + zi*zi < 4.0 && iteration < max_iterations) {
    zrt = (zi - zr)*(zi + zr) + zr;
    zit = zr*zi;
    zit = zit + zit - zi;

    zr = x*zrt + y*zit;
    zi = y*zrt - x*zit;

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
