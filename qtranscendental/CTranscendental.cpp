#include <CTranscendental.h>
#include <CMathGen.h>

CTranscendental::
CTranscendental() :
 type_(SIN)
{
  setType(type_);
}

CTranscendental *
CTranscendental::
dup() const
{
  return new CTranscendental;
}

void
CTranscendental::
setType(Type type)
{
  type_ = type;

  switch (type_) {
    case SIN:
      xmin_ = -2*M_PI; ymin_ = -M_PI; xmax_ = 0; ymax_ = M_PI;
      break;
    case COS:
      xmin_ = -M_PI; ymin_ = -M_PI; xmax_ = M_PI; ymax_ = M_PI;
      break;
    case SINH:
      xmin_ = -M_PI; ymin_ = -2*M_PI; xmax_ = M_PI; ymax_ = 0;
      break;
    case COSH:
      xmin_ = -M_PI; ymin_ = -M_PI; xmax_ = M_PI; ymax_ = M_PI;
      break;
    case EXP:
      xmin_ = -10*M_PI; ymin_ = -10*M_PI; xmax_ = 10*M_PI; ymax_ = 10*M_PI;
      break;
  }
}

int
CTranscendental::
calc(double x, double y, int max_iterations) const
{
  int iteration = 0;

  if      (type_ == SIN)
    iteration = iterate_sin(x, y, max_iterations);
  else if (type_ == COS)
    iteration = iterate_cos(x, y, max_iterations);
  else if (type_ == SINH)
    iteration = iterate_sinh(x, y, max_iterations);
  else if (type_ == COSH)
    iteration = iterate_cosh(x, y, max_iterations);
  else if (type_ == EXP)
    iteration = iterate_exp(x, y, max_iterations);

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
CTranscendental::
iterate_cos(double x, double y, int max_iterations) const
{
  int iteration = -1;

  zr_ = 0.0;
  zi_ = 0.0;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zi2 + zr2 < 10000.0 && iteration < max_iterations) {
    double zr1 =  cos(zr_)*cosh(zi_) + x;
    double zi1 = -sin(zr_)*sinh(zi_) + y;

    zr_ = zr1;
    zi_ = zi1;

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
CTranscendental::
iterate_sin(double x, double y, int max_iterations) const
{
  int iteration = -1;

  zr_ = 0.0;
  zi_ = 0.0;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zi2 + zr2 < 1000.0 && iteration < max_iterations) {
    double zr1 = sin(zr_)*cosh(zi_) + x;
    double zi1 = cos(zr_)*sinh(zi_) + y;

    zr_ = zr1;
    zi_ = zi1;

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
CTranscendental::
iterate_exp(double x, double y, int max_iterations) const
{
  int iteration = -1;

  zr_ = 0.0;
  zi_ = 0.0;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zi2 + zr2 < 1000.0 && iteration < max_iterations) {
    double zr1 = x*exp(zr_)*cos(zi_) - y*exp(zr_)*sin(zi_);
    double zi1 = y*exp(zr_)*cos(zi_) + x*exp(zr_)*sin(zi_);

    zr_ = zr1;
    zi_ = zi1;

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
CTranscendental::
iterate_cosh(double x, double y, int max_iterations) const
{
  int iteration = -1;

  zr_ = 0.0;
  zi_ = 0.0;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zi2 + zr2 < 1000.0 && iteration < max_iterations) {
    double zr1 = cosh(zr_)*cos(zi_) + x;
    double zi1 = sinh(zr_)*sin(zi_) + y;

    zr_ = zr1;
    zi_ = zi1;

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
CTranscendental::
iterate_sinh(double x, double y, int max_iterations) const
{
  int iteration = -1;

  zr_ = 0.0;
  zi_ = 0.0;

  double zr2 = 0.0;
  double zi2 = 0.0;

  while (zi2 + zr2 < 1000.0 && iteration < max_iterations) {
    double zr1 = sinh(zr_)*cos(zi_) + x;
    double zi1 = cosh(zr_)*sin(zi_) + y;

    zr_ = zr1;
    zi_ = zi1;

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}
