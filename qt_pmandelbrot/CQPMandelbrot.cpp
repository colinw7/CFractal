#include <CQPMandelbrot.h>
#include <CMandelbrot.h>
#include <CPointFractal.h>
#include <CQUtil.h>
#include <CRGB.h>
#include <CTransform2D.h>

#include <QPainter>
#include <QMouseEvent>

CQPMandelbrot::
CQPMandelbrot(QWidget *parent) :
 QWidget(parent), redraw_(true), rubber_band_(NULL)
{
  setFocusPolicy(Qt::StrongFocus);

  mandelbrot_ = new CMandelbrot;

  max_iterations_ = 128;

  show_vector_ = false;

  xmin_ = mandelbrot_->getXMin();
  ymin_ = mandelbrot_->getYMin();
  xmax_ = mandelbrot_->getXMax();
  ymax_ = mandelbrot_->getYMax();

  for (uint i = 0; i < NUM_THREADS; ++i) {
    threads_[i] = new CQPMandelbrotThread;

    connect(threads_[i], SIGNAL(drawImageSignal(int,int,const QImage &)),
            this, SLOT(drawImageSlot(int, int, const QImage &)));
  }
}

CQPMandelbrot::
~CQPMandelbrot()
{
  for (uint i = 0; i < NUM_THREADS; ++i)
    delete threads_[i];

  delete rubber_band_;
}

void
CQPMandelbrot::
resetRange()
{
  xmin_ = mandelbrot_->getXMin();
  ymin_ = mandelbrot_->getYMin();
  xmax_ = mandelbrot_->getXMax();
  ymax_ = mandelbrot_->getYMax();

  redraw();
}

void
CQPMandelbrot::
setIterations(int iterations)
{
  if (iterations != getMaxIterations()) {
    setMaxIterations(iterations);

    redraw();
  }
}

void
CQPMandelbrot::
toggleShowVector()
{
  setShowVector(! getShowVector());

  redraw();
}

void
CQPMandelbrot::
selectionNotify(const QPoint &p1, const QPoint &p2)
{
  int x = std::min(p1.x(), p2.x());
  int y = std::min(p1.y(), p2.y());
  int w = abs(p2.x() - p1.x());
  int h = abs(p2.y() - p1.y());

  QRect rect(x, y, w, h);

  double wx1, wy1, wx2, wy2;

  conv(rect.left (), rect.top   (), &wx1, &wy1);
  conv(rect.right(), rect.bottom(), &wx2, &wy2);

  double canvas_xmin, canvas_ymin, canvas_xmax, canvas_ymax;

  getRange(&canvas_xmin, &canvas_ymin, &canvas_xmax, &canvas_ymax);

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

  setRange(canvas_xmin, canvas_ymin, canvas_xmax, canvas_ymax);

  redraw();
}

void
CQPMandelbrot::
paintEvent(QPaintEvent *)
{
  if (redraw_) {
    resizeEvent(NULL);

    redraw_ = false;
  }

  QPainter painter(this);

  painter.drawImage(QPoint(0, 0), qimage_);
}

void
CQPMandelbrot::
resizeEvent(QResizeEvent *)
{
  uint pwidth  = width ();
  uint pheight = height();

  qimage_ = QImage(pwidth, pheight, QImage::Format_ARGB32);

  uint pwidth1  = pwidth /NUM_SPLITS;
  uint pheight1 = pheight/NUM_SPLITS;

  double dwidth  = xmax_ - xmin_;
  double dheight = ymax_ - ymin_;

  double dwidth1  = dwidth /NUM_SPLITS;
  double dheight1 = dheight/NUM_SPLITS;

  px_[0         ] = 0;
  px_[NUM_SPLITS] = pwidth - 1;
  dx_[0         ] = xmin_;
  dx_[NUM_SPLITS] = xmax_;

  for (uint x = 1; x < NUM_SPLITS; ++x) {
    px_[x] = px_[x - 1] + pwidth1;
    dx_[x] = dx_[x - 1] + dwidth1;
  }

  py_[0         ] = 0;
  py_[NUM_SPLITS] = pheight - 1;
  dy_[0         ] = ymin_;
  dy_[NUM_SPLITS] = ymax_;

  for (uint y = 1; y < NUM_SPLITS; ++y) {
    py_[y] = py_[y - 1] + pheight1;
    dy_[y] = dy_[y - 1] + dheight1;
  }

  for (uint y = 0; y < NUM_SPLITS; ++y) {
    uint y1 = NUM_SPLITS*y;

    for (uint x = 0; x < NUM_SPLITS; ++x) {
      int i = y1 + x;

      threads_[i]->init(px_[x], py_[y], px_[x + 1], py_[y + 1],
                        dx_[x], dy_[y], dx_[x + 1], dy_[y + 1],
                        max_iterations_);
    }
  }

  transform_.setFrom(0, 0, pwidth - 1, pheight - 1);
  transform_.setTo  (xmin_, ymin_, xmax_, ymax_);
}

void
CQPMandelbrot::
mousePressEvent(QMouseEvent *event)
{
  press_pos_ = event->pos();

  if (event->button() == Qt::LeftButton)
    updateRubberband(press_pos_, press_pos_);
}

void
CQPMandelbrot::
mouseMoveEvent(QMouseEvent *event)
{
  updateRubberband(press_pos_, event->pos());
}

void
CQPMandelbrot::
mouseReleaseEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton) {
    updateRubberband(press_pos_, event->pos());

    selectionNotify(press_pos_, event->pos());

    rubber_band_->hide();
  }
}

void
CQPMandelbrot::
updateRubberband(const QPoint &p1, const QPoint &p2)
{
  if (rubber_band_ == NULL)
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
CQPMandelbrot::
drawImageSlot(int x, int y, const QImage &image)
{
  QPainter painter(&qimage_);

  painter.drawImage(x, y, image);

  update();
}

void
CQPMandelbrot::
conv(double px, double py, double *wx, double *wy)
{
  transform_.conv(px, py, wx, wy);
}

void
CQPMandelbrot::
iconv(double wx, double wy, double *px, double *py)
{
  transform_.iconv(wx, wy, px, py);
}

void
CQPMandelbrot::
redraw()
{
  //for (uint i = 0; i < NUM_THREADS; ++i) threads_[i]->abort();

  redraw_ = true;

  update();
}

//------

CQPMandelbrotThread::
CQPMandelbrotThread()
{
  restart_  = false;
  abort_    = false;
  finished_ = false;
}

CQPMandelbrotThread::
~CQPMandelbrotThread()
{
  mutex_.lock();

  abort_ = true;

  condition_.wakeOne();

  mutex_.unlock();

  wait();
}

void
CQPMandelbrotThread::
init(int pixel_xmin, int pixel_ymin, int pixel_xmax, int pixel_ymax,
     double xmin, double ymin, double xmax, double ymax,
     uint max_iterations)
{
  pixel_xmin_ = pixel_xmin;
  pixel_ymin_ = pixel_ymin;
  pixel_xmax_ = pixel_xmax;
  pixel_ymax_ = pixel_ymax;

  xmin_ = xmin;
  ymin_ = ymin;
  xmax_ = xmax;
  ymax_ = ymax;

  max_iterations_ = max_iterations;

  int pwidth  = pixel_xmax_ - pixel_xmin_ + 1;
  int pheight = pixel_ymax_ - pixel_ymin_ + 1;

  qimage_ = QImage(pwidth, pheight, QImage::Format_ARGB32);

  finished_ = false;

  if (! isRunning())
    start();
  else {
    restart_ = true;

    condition_.wakeOne();
  }
}

void
CQPMandelbrotThread::
run()
{
  forever {
    transform_.setFrom(pixel_xmin_, pixel_ymin_, pixel_xmax_, pixel_ymax_);
    transform_.setTo  (xmin_, ymin_, xmax_, ymax_);

    uint pixel_width  = pixel_xmax_ - pixel_xmin_ + 1;
    uint pixel_height = pixel_ymax_ - pixel_ymin_ + 1;

    if (pixel_width > x_store_.size())
      x_store_.resize(pixel_width);

    if (pixel_height > y_store_.size())
      y_store_.resize(pixel_height);

    double dummy;

    for (int x = pixel_xmin_, xx = 0; x <= pixel_xmax_; ++x, ++xx)
      transform_.conv(x, 0, &x_store_[xx], &dummy);

    for (int y = pixel_ymin_, yy = 0; y <= pixel_ymax_; ++y, ++yy)
      transform_.conv(0, y, &dummy, &y_store_[yy]);

    mandelbrot_.setRange(xmin_, ymin_, xmax_, ymax_);

    mandelbrot_.initCalc(pixel_xmin_, pixel_ymin_, pixel_xmax_, pixel_ymax_,
                         xmin_, ymin_, xmax_, ymax_, max_iterations_);

    for (int y = pixel_ymin_, yy = 0; y <= pixel_ymax_; ++y, ++yy) {
      if (restart_) break;
      if (abort_  ) return;

      double ry = y_store_[yy];

      for (int x = pixel_xmin_, xx = 0; x <= pixel_xmax_; ++x, ++xx) {
        if (restart_) break;
        if (abort_  ) return;

        double rx = x_store_[xx];

        int color = mandelbrot_.calc(rx, ry, max_iterations_);

        const CRGBA &rgba = colors_.getColor(color);

        qimage_.setPixel(QPoint(xx, yy), CQUtil::rgbaToInt(rgba));
      }
    }

    finished_ = true;

    if (! restart_)
      emit drawImageSignal(pixel_xmin_, pixel_ymin_, qimage_);

    //------

    // wait for next data to become available
    mutex_.lock();

    if (! restart_)
      condition_.wait(&mutex_);

    restart_ = false;

    mutex_.unlock();
  }
}
