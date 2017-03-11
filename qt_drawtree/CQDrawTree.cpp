#include <CQDrawTree.h>
#include <CQWidgetRenderer2D.h>
#include <QWidget>
#include <QPainter>
#include <CQApp.h>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQDrawTree *tree = new CQDrawTree(600, 600);

  std::string filename;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-')
      continue;
    else
      filename = argv[i];
  }

  if (filename != "")
    tree->read(filename);

  tree->show();

  app.exec();

  return 0;
}

CQDrawTree::
CQDrawTree(int width, int height) :
 QWidget()
{
  resize(width, height);

  renderer_ = new CQWidgetRenderer2D(this);
}

void
CQDrawTree::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  p.fillRect(rect(), QBrush(QColor(0,0,0)));

  renderer_->beginDraw();

  draw();

  renderer_->endDraw();
}

void
CQDrawTree::
resizeEvent(QResizeEvent *)
{
  renderer_->updateSize(width(), height());
}

void
CQDrawTree::
setDataRange(double xmin, double ymin, double xmax, double ymax)
{
  renderer_->setDataRange(xmin, ymin, xmax, ymax);
}

void
CQDrawTree::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CQDrawTree::
drawLine(double x1, double y1, double x2, double y2)
{
  renderer_->drawLine(CPoint2D(x1, y1), CPoint2D(x2, y2));
}

void
CQDrawTree::
setLineWidth(double width)
{
  renderer_->setLineWidth(width);
}
