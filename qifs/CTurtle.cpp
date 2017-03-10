#include <CTurtle.h>

CTurtle::
CTurtle() :
 color_()
{
  reset();
}

CTurtle::
CTurtle(const CTurtle &turtle) :
 prev_x_    (turtle.prev_x_),
 prev_y_    (turtle.prev_y_),
 prev_angle_(turtle.prev_angle_),
 x_         (turtle.x_),
 y_         (turtle.y_),
 angle_     (turtle.angle_),
 color_     (turtle.color_),
 m_         (turtle.m_)
{
}

CTurtle::
~CTurtle()
{
}

CTurtle &
CTurtle::
operator=(const CTurtle &turtle)
{
  prev_x_     = turtle.prev_x_;
  prev_y_     = turtle.prev_y_;
  prev_angle_ = turtle.prev_angle_;

  x_     = turtle.x_;
  y_     = turtle.y_;
  angle_ = turtle.angle_;

  color_ = turtle.color_;

  m_ = turtle.m_;

  return *this;
}

CTurtle *
CTurtle::
dup() const
{
  return new CTurtle(*this);
}

void
CTurtle::
reset()
{
  prev_x_     = 0.0;
  prev_y_     = 0.0;
  prev_angle_ = 0.0;

  x_     = 0.0;
  y_     = 0.0;
  angle_ = 0.0;

  color_ = CRGBA(0, 0, 0);

  m_.setIdentity();
}

void
CTurtle::
setColor(const CRGBA &color)
{
  color_ = color;
}

void
CTurtle::
move(double x, double y)
{
  prev_x_ = x_;
  prev_y_ = y_;

  x_ = x;
  y_ = y;
}

void
CTurtle::
step(double length)
{
  prev_x_ = x_;
  prev_y_ = y_;

  x_ += length*cos(deg2rad(angle_));
  y_ += length*sin(deg2rad(angle_));

  CPoint2D p1(prev_x_, prev_y_);
  CPoint2D p2(x_     , y_     );

  p1 = m_*p1;
  p2 = m_*p2;

  drawLine(p1.x, p1.y, p2.x, p2.y);
}

void
CTurtle::
skip(double length)
{
  prev_x_ = x_;
  prev_y_ = y_;

  x_ += length*cos(deg2rad(angle_));
  y_ += length*sin(deg2rad(angle_));
}

void
CTurtle::
turn(double angle)
{
  prev_angle_ = angle_;

  angle_ += angle;

  while (angle_ < 0.0)
    angle_ += 360.0;

  while (angle_ >= 360.0)
    angle_ -= 360.0;
}

void
CTurtle::
drawLine(double, double, double, double)
{
}
