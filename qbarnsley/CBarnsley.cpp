#include <CBarnsley.h>
#include <CMathGen.h>

#include <complex>

CBarnsley::
CBarnsley() :
 type_(B1)
{
  setType(type_);
}

CBarnsley::
CBarnsley(const CBarnsley &barnsley) :
 type_(barnsley.type_)
{
  setType(type_);
}

CBarnsley *
CBarnsley::
dup() const
{
  return new CBarnsley(*this);
}

void
CBarnsley::
setType(Type type)
{
  type_ = type;

  switch (type_) {
    case B1:
      xmin_ = 0.077; ymin_ = -0.21; xmax_ = 1.08; ymax_ = 0.79;

      p_ = 0.6; q_ = 1.1;

      break;
    case B2:
      xmin_ = 0.077; ymin_ = -0.21; xmax_ = 1.08; ymax_ = 0.79;

      p_ = 0.6; q_ = 1.1;

      break;
    case B3:
      xmin_ = -2.1; ymin_ = -1.03; xmax_ = 1.7; ymax_ = 1.03;

      p_ = 1.0; q_ = 1.0;

      break;
    case B4:
      xmin_ = -0.5; ymin_ = -0.22; xmax_ = 1.3; ymax_ = 1.22;

      p_ = 0.0; q_ = 0.0;

      break;
  }
}

int
CBarnsley::
calc(double x, double y, int max_iterations) const
{
  int iteration = 0;

  if      (type_ == B1)
    iteration = iterate_b1(x, y, max_iterations);
  else if (type_ == B2)
    iteration = iterate_b2(x, y, max_iterations);
  else if (type_ == B3)
    iteration = iterate_b3(x, y, max_iterations);
  else if (type_ == B4)
    iteration = iterate_b4(x, y, max_iterations);

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
CBarnsley::
iterate_b1(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = zr_*zr_;
  double zi2 = zi_*zi_;

  while (zr2 + zi2 < 4 && iteration < max_iterations) {
    double px = p_*zr_;
    double py = p_*zi_;
    double qx = q_*zr_;
    double qy = q_*zi_;

    if (zr_ >= 0) {
      zr_ = px - p_ - qy;
      zi_ = py - q_ + qx;
    }
    else {
      zr_ = px + p_ - qy;
      zi_ = py + q_ + qx;
    }

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
CBarnsley::
iterate_b2(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = zr_*zr_;
  double zi2 = zi_*zi_;

  while (zr2 + zi2 < 4 && iteration < max_iterations) {
    double px = p_*zr_;
    double py = p_*zi_;
    double qx = q_*zr_;
    double qy = q_*zi_;

    if (qx + py >= 0) {
      zr_ = px - p_ - qy;
      zi_ = py - q_ + qx;
    }
    else {
      zr_ = px + p_ - qy;
      zi_ = py + q_ + qx;
    }

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}

int
CBarnsley::
iterate_b3(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = zr_*zr_;
  double zi2 = zi_*zi_;
  double zri = zr_*zi_;

  while (zr2 + zi2 < 4 && iteration < max_iterations) {
    if (zr_ >= 0) {
      zr_ = zr2 - zi2 - 1.0;
      zi_ = 2.0*zri;
    }
    else {
      zr_ = zr2 - zi2 - 1.0 + p_*zr_;
      zi_ = 2.0*zri;
    }

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;
    zri = zr_*zi_;

    ++iteration;
  }

  return iteration;
}

int
CBarnsley::
iterate_b4(double x, double y, int max_iterations) const
{
  int iteration = -1;

  std::complex<double> c(x, y);

  zr_ = x;
  zi_ = y;

  double zr2 = zr_*zr_;
  double zi2 = zi_*zi_;

  while (zr2 + zi2 < 4 && iteration < max_iterations) {
    zr_ = 2.0*zr_;
    zi_ = 2.0*zi_;

    if      (zi_ > 1.0)
      --zi_;
    else if (zr_ > 1.0)
      --zr_;

    zr2 = zr_*zr_;
    zi2 = zi_*zi_;

    ++iteration;
  }

  return iteration;
}
