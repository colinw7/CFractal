#include <CQPointFractal.h>
#include <CPointFractalRenderer.h>
#include <CQColors.h>
#include <CQColorsPalette.h>
#include <CQUtil.h>
#include <CQUtilRGBA.h>

#include <QPainter>
#include <QRubberBand>
#include <QMouseEvent>

class CQPointFractalRenderer : public CPointFractalRenderer {
 public:
  CQPointFractalRenderer(CQPointFractal *pf, CPointFractalCalc *fractal) :
   CPointFractalRenderer(fractal), pf_(pf) {
  }

  void setForeground(int color) override {
    pf_->setForeground(color);
  }

  void setForeground(const CRGBA &rgba) override {
    pf_->setForeground(rgba);
  }

  void drawPoint(int x, int y) override {
    pf_->drawPoint(x, y);
  }

 private:
  CQPointFractal *pf_ { nullptr };
};

//------

CQPointFractal::
CQPointFractal(QWidget *parent) :
 QWidget(parent)
{
  setPalette("plasma");

  setFocusPolicy(Qt::StrongFocus);
}

CQPointFractal::
~CQPointFractal()
{
  delete renderer_;
  delete rubber_band_;
}

void
CQPointFractal::
setFractal(CPointFractalCalc *fractal)
{
  delete renderer_;

  renderer_ = new CQPointFractalRenderer(this, fractal);
}

void
CQPointFractal::
setThreaded(bool threaded)
{
  threaded_ = threaded;

  redraw_ = true;

  update();
}

void
CQPointFractal::
resetRange()
{
  renderer_->resetRange();

  redraw();
}

QRectF
CQPointFractal::
range() const
{
  double xmin, ymin, xmax, ymax;

  renderer_->getRange(&xmin, &ymin, &xmax, &ymax);

  QRectF r;

  r.setCoords(xmin, ymin, xmax, ymax);

  return r;
}

void
CQPointFractal::
setRange(const QRectF &r)
{
  double xmin = std::min(r.left  (), r.right());
  double xmax = std::max(r.left  (), r.right());
  double ymin = std::min(r.bottom(), r.top  ());
  double ymax = std::max(r.bottom(), r.top  ());

  renderer_->setRange(xmin, ymin, xmax, ymax);

  redraw();
}

int
CQPointFractal::
iterations() const
{
  return renderer_->getMaxIterations();
}

void
CQPointFractal::
setIterations(int n)
{
  if (n != iterations()) {
    renderer_->setMaxIterations(n);

    redraw();
  }
}

bool
CQPointFractal::
showVector() const
{
  return renderer_->getShowVector();
}

void
CQPointFractal::
setShowVector(bool show)
{
  if (show != showVector()) {
    renderer_->setShowVector(show);

    redraw();
  }
}

void
CQPointFractal::
toggleShowVector()
{
  setShowVector(! showVector());
}

void
CQPointFractal::
selectionNotify(const QPoint &p1, const QPoint &p2)
{
  int x = std::min(p1.x(), p2.x());
  int y = std::min(p1.y(), p2.y());
  int w = abs(p2.x() - p1.x());
  int h = abs(p2.y() - p1.y());

  QRect rect(x, y, w, h);

  double wx1, wy1, wx2, wy2;

  renderer_->conv(rect.left (), rect.top   (), &wx1, &wy1);
  renderer_->conv(rect.right(), rect.bottom(), &wx2, &wy2);

  double canvas_xmin, canvas_ymin, canvas_xmax, canvas_ymax;

  renderer_->getRange(&canvas_xmin, &canvas_ymin, &canvas_xmax, &canvas_ymax);

  double w1 = fabs(wx2 - wx1);
  double h1 = fabs(wy2 - wy1);

  double w2 = fabs(canvas_xmax - canvas_xmin);
  double h2 = fabs(canvas_ymax - canvas_ymin);

  double s = std::min(w1/w2, h1/h2);

  double xc = 0.5*(wx2 + wx1);
  double yc = 0.5*(wy2 + wy1);

  w2 *= s;
  h2 *= s;

  canvas_xmin = xc - 0.5*w2;
  canvas_ymin = yc - 0.5*h2;
  canvas_xmax = xc + 0.5*w2;
  canvas_ymax = yc + 0.5*h2;

  QRectF canvas_range;

  canvas_range.setCoords(canvas_xmin, canvas_ymin, canvas_xmax, canvas_ymax);

  setRange(canvas_range);

  redraw();
}

void
CQPointFractal::
paintEvent(QPaintEvent *)
{
  if (qimage_.isNull())
    resizeEvent(nullptr);

  if (redraw_) {
    QPainter painter(&qimage_);

    painter_ = &painter;

    if (isThreaded())
      renderer_->threadDraw(width(), height());
    else
      renderer_->draw(width(), height());

    redraw_ = false;
  }

  QPainter painter(this);

  painter.drawImage(QPoint(0, 0), qimage_);
}

void
CQPointFractal::
resizeEvent(QResizeEvent *)
{
  qimage_ = QImage(QSize(width(), height()), QImage::Format_ARGB32);

  redraw_ = true;
}

void
CQPointFractal::
setForeground(int color)
{
  if (color == 0)
    painter_->setPen(QColor());
  else
    painter_->setPen(palette_->getColor(color - 1, 255));
}

void
CQPointFractal::
setForeground(const CRGBA &rgba)
{
  painter_->setPen(CQUtil::rgbaToColor(rgba));
}

void
CQPointFractal::
drawPoint(int x, int y)
{
  painter_->drawPoint(QPoint(x, y));
}

void
CQPointFractal::
mousePressEvent(QMouseEvent *event)
{
  press_pos_ = event->pos();

  if (event->button() == Qt::LeftButton)
    updateRubberband(press_pos_, press_pos_);
}

void
CQPointFractal::
mouseMoveEvent(QMouseEvent *event)
{
  updateRubberband(press_pos_, event->pos());
}

void
CQPointFractal::
mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    updateRubberband(press_pos_, event->pos());

    selectionNotify(press_pos_, event->pos());

    rubber_band_->hide();
  }
}

void
CQPointFractal::
updateRubberband(const QPoint &p1, const QPoint &p2)
{
  if (! rubber_band_)
    rubber_band_ = new QRubberBand(QRubberBand::Rectangle, this);

  int w = abs(p2.x() - p1.x());
  int h = abs(p2.y() - p1.y());

  if (w > 2 && h > 2) {
    int x = std::min(p1.x(), p2.x());
    int y = std::min(p1.y(), p2.y());

    rubber_band_->setGeometry(x, y, w + 1, h + 1);

    rubber_band_->show();
  }
  else
    rubber_band_->hide();
}

void
CQPointFractal::
redraw()
{
  redraw_ = true;

  update();
}

void
CQPointFractal::
setPalette(const QString &name)
{
  palette_ = CQColorsMgrInst->getNamedPalette(name);
}
