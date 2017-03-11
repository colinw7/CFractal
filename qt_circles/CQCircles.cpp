#include <CQCircles.h>
#include <CQWidgetRenderer2D.h>
#include <QWidget>
#include <QPainter>
#include <CQApp.h>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQCircles *circles = new CQCircles(600, 600);

  circles->show();

  app.exec();

  return 0;
}

CQCircles::
CQCircles(int width, int height) :
 QWidget()
{
  resize(width, height);

  renderer_ = new CQWidgetRenderer2D(this);
}

void
CQCircles::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  p.fillRect(rect(), QBrush(QColor(0,0,0)));

  renderer_->beginDraw();

  draw();

  renderer_->endDraw();
}

void
CQCircles::
resizeEvent(QResizeEvent *)
{
  renderer_->updateSize(width(), height());
}

void
CQCircles::
setDataRange(double xmin, double ymin, double xmax, double ymax)
{
  renderer_->setDataRange(xmin, ymin, xmax, ymax);
}

void
CQCircles::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CQCircles::
drawCircle(double x, double y, double r)
{
  renderer_->drawCircle(CPoint2D(x, y), r);
}

void
CQCircles::
fillCircle(double x, double y, double r)
{
  renderer_->fillCircle(CPoint2D(x, y), r);
}
