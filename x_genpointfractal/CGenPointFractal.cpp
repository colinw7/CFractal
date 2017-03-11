#include <CGenPointFractal.h>
#include <CMathGen.h>

CGenPointFractal::
CGenPointFractal()
{
  xmin_ = -2.0;
  ymin_ = -1.2;
  xmax_ =  1.2;
  ymax_ =  1.2;

  xi_type_ = POS; xi_ = 0.0;
  yi_type_ = POS; yi_ = 0.0;
  a_type_  = POS; a_  = 0.0;
  b_type_  = POS; b_  = 0.0;
  c_type_  = POS; c_  = 0.0;
  d_type_  = POS; d_  = 0.0;
  e_type_  = POS; e_  = 0.0;
  f_type_  = POS; f_  = 0.0;
}

CGenPointFractal *
CGenPointFractal::
dup() const
{
  // TODO: copy parameters
  return new CGenPointFractal;
}

void
CGenPointFractal::
mandelbrot()
{
  xmin_ = -2.0;
  ymin_ = -1.2;
  xmax_ =  1.2;
  ymax_ =  1.2;

  xi_type_ = VALUE; xi_ = 0.0;
  yi_type_ = VALUE; yi_ = 0.0;
  a_type_  = VALUE; a_  = 1.0;
  b_type_  = VALUE; b_  = 0.0;
  c_type_  = VALUE; c_  = 0.0;
  d_type_  = VALUE; d_  = 0.0;
  e_type_  = POS;   e_  = 0.0;
  f_type_  = POS;   f_  = 0.0;
}

void
CGenPointFractal::
julia()
{
  xmin_ = -1.6;
  ymin_ = -1.2;
  xmax_ =  1.6;
  ymax_ =  1.2;

  p_ = 0.238498;
  q_ = 0.519198;

  xi_type_ = POS  ; xi_ = 0.0;
  yi_type_ = POS  ; yi_ = 0.0;
  a_type_  = VALUE; a_  = 1.0;
  b_type_  = VALUE; b_  = 0.0;
  c_type_  = VALUE; c_  = 0.0;
  d_type_  = VALUE; d_  = 0.0;
  e_type_  = VALUE; e_  = p_;
  f_type_  = VALUE; f_  = q_;
}

void
CGenPointFractal::
dragon()
{
  xmin_ = -0.2;
  ymin_ = -0.7;
  xmax_ =  1.2;
  ymax_ =  0.7;

  p_ = 1.646009;
  q_ = 0.967049;

  xi_type_ = POS  ; xi_ = 0;
  yi_type_ = POS  ; yi_ = 0;
  a_type_  = VALUE; a_  = -p_;
  b_type_  = VALUE; b_  = -q_;
  c_type_  = VALUE; c_  = p_;
  d_type_  = VALUE; d_  = q_;
  e_type_  = VALUE; e_  = 0;
  f_type_  = VALUE; f_  = 0;
}

void
CGenPointFractal::
dragonSet()
{
  xmin_ = -2.2;
  ymin_ = -1.5;
  xmax_ =  4.2;
  ymax_ =  1.5;

  xi_type_ = VALUE; xi_ = 0.5;
  yi_type_ = VALUE; yi_ = 0;
  a_type_  = NEG  ; a_  = 0;
  b_type_  = NEG  ; b_  = 0;
  c_type_  = POS  ; c_  = 0;
  d_type_  = POS  ; d_  = 0;
  e_type_  = VALUE; e_  = 0;
  f_type_  = VALUE; f_  = 0;
}

int
CGenPointFractal::
calc(double x, double y, int max_iterations) const
{
  int iteration = iterate(x, y, max_iterations);

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
CGenPointFractal::
iterate(double x, double y, int max_iterations) const
{
  int iteration = -1;

  zr_ = (xi_type_ != VALUE ? (xi_type_ == NEG ? -x : x) : xi_);
  zi_ = (yi_type_ != VALUE ? (yi_type_ == NEG ? -y : y) : yi_);

  double a, b, c, d, e, f;

  if (a_type_ == VALUE) a = a_; else if (a_type_ == NEG) a = -x; else a = x;
  if (c_type_ == VALUE) c = c_; else if (c_type_ == NEG) c = -x; else c = x;
  if (e_type_ == VALUE) e = e_; else if (e_type_ == NEG) e = -x; else e = x;
  if (b_type_ == VALUE) b = b_; else if (b_type_ == NEG) b = -y; else b = y;
  if (d_type_ == VALUE) d = d_; else if (d_type_ == NEG) d = -y; else d = y;
  if (f_type_ == VALUE) f = f_; else if (f_type_ == NEG) f = -y; else f = y;

  double zr2 = 0.0;
  double zi2 = 0.0;
  double zri = 0.0;

  while (zr2 + zi2 < 4.0 && iteration < max_iterations) {
    zr2 = zr_*zr_;
    zi2 = zi_*zi_;
    zri = zr_*zi_;

    double zr =   a*zr2 - a*zi2 - 2*b*zri + c*zr_ - d*zi_ + e;
    double zi = 2*a*zri + b*zr2 -   b*zi2 + c*zi_ + d*zr_ + f;

    zr_ = zr;
    zi_ = zi;

    ++iteration;
  }

  return iteration;
}
