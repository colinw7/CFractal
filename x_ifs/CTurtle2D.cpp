#include <CTurtle2D.h>
#include <CRenderer2D.h>

CTurtle2D::
CTurtle2D(CRenderer2D *renderer) :
 renderer_(renderer)
{
}

CTurtle2D::
CTurtle2D(const CTurtle2D &turtle) :
 CTurtle  (turtle),
 renderer_(turtle.renderer_)
{
}

CTurtle2D::
~CTurtle2D()
{
}

CTurtle2D &
CTurtle2D::
operator=(const CTurtle2D &turtle)
{
  CTurtle::operator=(turtle);

  renderer_ = turtle.renderer_;

  return *this;
}

CTurtle2D *
CTurtle2D::
dup() const
{
  return new CTurtle2D(*this);
}

void
CTurtle2D::
drawLine(double x1, double y1, double x2, double y2)
{
  renderer_->setForeground(color_);

  renderer_->drawLine(CPoint2D(x1, y1), CPoint2D(x2, y2));
}
