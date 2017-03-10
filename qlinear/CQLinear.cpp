#include <CQLinear.h>
#include <CThread.h>
#include <CBresenham.h>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <cmath>

class ImageLine : public CBresenham {
 public:
  ImageLine(QImage *i, QColor c, int h) :
   i_(i), c_(c), h_(h) {
  }

  void drawPoint(int x, int y) {
    if (y >= 0 && y < h_)
      i_->setPixel(x, h_ - 1 - y, c_.rgb());
  }

 private:
  QImage *i_;
  QColor  c_;
  int     h_;
};

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQLinear *linear = new CQLinear;

  linear->show();

  app.exec();
}

CQLinear::
CQLinear()
{
  image_ = QImage(600, 400, QImage::Format_ARGB32);

  t_  = 0.0;
  dt_ = 0.05;

  setFixedSize(image_.width(), image_.height());

  QTimer *timer = new QTimer;

  connect(timer, SIGNAL(timeout()), this, SLOT(tickSlot()));

  timer->start(30);
}

void
CQLinear::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  linear();

  p.drawImage(0, 0, image_);
}

void
CQLinear::
tickSlot()
{
  t_ += dt_;

  update();
}

//---------

class Calc {
 public:
  Calc(double t) :
   t_(t) {
  }

  void render(QImage &image);

  virtual double exec(int ix, double x) = 0;

  virtual double mapX(int x) { return -1.0 + (2.0*x)/(w_ - 1); }

  int round(double x);

  int sign(double x);

  double random();

 protected:
  double t_;
  int    w_, h_;
};

struct ThreadData {
  Calc*               calc;
  int                 w, h;
  int                 xmin, xmax;
  std::vector<double> y;
};

static void
ThreadDraw(void *d)
{
  ThreadData *data = (ThreadData *) d;

  Calc *calc = data->calc;

  int pos = 0;

  for (int ix = data->xmin; ix <= data->xmax; ++ix, ++pos) {
    double x = calc->mapX(ix);

    data->y[pos] = calc->exec(ix, x);
  }
}

//---------

class Linear : public Calc {
 public:
  Linear(double t) :
   Calc(t) {
  }

  double exec(int ix, double x) {
    //return 0.9*sin(x*M_PI*2) + 0.1*sin(10*x+t_);

    //return 0.9*sin(x*M_PI*2) + 0.1*sin(200*x + 5*t_)*cos(2*t_ + x*10+random());

    //return 0.9*sin(x*M_PI*2) + 0.1*sin(20*x + t_) + 0.2*sin(13.3*x + t_*0.91) - 0.02*random();

    //return (3*(x + t_*0.2) - round(3*(x + t_*0.2)));

    //return 0.7*(sin(x*10 + t_*10.1) > 0.0 ? 1.0 : -1.0);

    return sign(x)*(((ix % 10) != 0) ? 0 : sin(x*10*t_)*sin(t_));
  }
};

void
CQLinear::
linear()
{
  Linear f(t_);

  f.render(image_);
}

//-----

void
Calc::
render(QImage &image)
{
  static uint num_threads = 0;

  //-----

  w_ = image.width ();
  h_ = image.height();

  image.fill(0xFF000000);

  //------

  QColor c(255, 255, 255);

  ImageLine line(&image, c, h_);

  if (num_threads > 0) {
    ThreadData threadData[num_threads];

    CThread threads[num_threads];

    double dx = (1.0*w_)/num_threads;

    for (uint ix = 0; ix < num_threads; ++ix) {
      ThreadData &t = threadData[ix];

      t.calc = this;
      t.w    = w_;
      t.h    = h_;
      t.xmin = int((ix    )*dx);
      t.xmax = int((ix + 1)*dx) - 1;

      t.y.resize((t.xmax - t.xmin + 1));
    }

    for (uint i = 0; i < num_threads; ++i)
      threads[i].start((CThreadProc) ThreadDraw, (void *) &threadData[i]);

    for (uint i = 0; i < num_threads; ++i)
      threads[i].join();

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    for (uint i = 0; i < num_threads; ++i) {
      ThreadData &t = threadData[i];

      int pos = 0;

      for (int x = t.xmin; x <= t.xmax; ++x, ++pos) {
        x1 = x2;
        y1 = y2;
        x2 = x;
        y2 = h_*(t.y[pos] + 1.0)/2.0;

        if (i > 0 || pos > 0)
          line.drawLine(x1, y1, x2, y2);

        //if (y2 >= 0 && y2 < h_) image.setPixel(x2, h_ - 1 - y2, c.rgb());
      }
    }
  }
  else {
    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    for (int ix = 0; ix < w_; ++ix) {
      double x = mapX(ix);
      double y = exec(ix, x);

      x1 = x2;
      y1 = y2;
      x2 = ix;
      y2 = h_*(y + 1.0)/2.0;

      if (ix > 0)
        line.drawLine(x1, y1, x2, y2);
    }
  }
}

int
Calc::
round(double x)
{
  if (x >= 0.0)
    return int(x + 0.5);
  else
    return int(x - 0.5);
}

int
Calc::
sign(double x)
{
  return (x >= 0 ? 1 : -1);
}

double
Calc::
random()
{
  return (2.0*rand())/RAND_MAX - 1.0;
}
