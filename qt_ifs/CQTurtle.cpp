#include <CQTurtle.h>
#include <QPainter>

CQTurtle::
CQTurtle(QPainter *painter) :
 painter_(painter)
{
}

CQTurtle::
~CQTurtle()
{
}

void
CQTurtle::
setPainter(QPainter *painter)
{
  painter_ = painter;
}

void
CQTurtle::
drawLine(double x1, double y1, double x2, double y2)
{
  painter_->drawLine(QPointF(x1, y1), QPointF(x2, y2));
}
