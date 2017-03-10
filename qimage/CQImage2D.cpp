#include <CQImage2D.h>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>
#include <CCosTable.h>
#include <CSinTable.h>
#include <CTanTable.h>
#include <CATanTable.h>
#include <CSqrtTable.h>
#include <CExpTable.h>
#include <CThread.h>
#include <limits>

static CCosTable  cos_table(1000);
static CSinTable  sin_table(1000);
static CTanTable  tan_table(1000);
static CATanTable atan_table(1000);
static CSqrtTable sqrt_table(0, 4, 1000);
static CExpTable  exp_table(-7, 1, 1000);

#define MAX(x,y) ((x)>(y)?x:y)

#define POW2(x) ((x)*(x))
#define POW3(x) ((x)*(x)*(x))
#define POW4(x) (POW2(x)*POW2(x))
#define POW8(x) (POW4(x)*POW4(x))

#define MOD(r, f) ((r) - int((r)/(f))*(f))

#define PDOT_SELF(p) (p.x*p.x + p.y*p.y)

#define PDOT(p1,p2) (p1.x*p2.x + p1.y*p2.y)

#define SQR(x) ((x)*(x))

#define LENGTH(p) SQRT(PDOT_SELF(p))

#define ABS(x) (((x) < 0.0) ? -(x) : (x))

#define POS_UNIT(x) (((x) > 0.0) ? 1.0 : 0.0)
//double u(double x) { return 0.5+0.5*sign(x); }
//double u(double x) { return POS_UNIT(x); }
//double u(double x) { return ABS(x)/x; }

#define STEP(r, d) (((d) < (r)) ? 0.0 : 1.0)
//double step(double r, double d) { return (d < r ? 0.0 : 1.0); }

#define TABLE 1

#if TABLE
#  define COS(a) cos_table.cos(a)
#  define SIN(a) sin_table.sin(a)
#  define TAN(a) (sin_table.sin(a)/cos_table.cos(a))

#  define ATAN(y,x) atan_table.atan(y, x)

#  define SQRT(x) sqrt_table.sqrt(x)

#  define EXP(x) exp_table.exp(x)
#else
#  define COS(a) cos(a)
#  define SIN(a) sin(a)
#  define TAN(a) tan(a)

#  define ATAN(y,x) atan2(y, x)

#  define SQRT(x) sqrt(x)

#  define EXP(x) exp(x)
#endif

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQImage2D *image2D = new CQImage2D;

  image2D->show();

  app.exec();
}

CQImage2D::
CQImage2D() :
 scale_(1), ind_(12), maxInd_(14)
{
  setWindowTitle(QString("CQImage2D Ind: %1, Scale %2").arg(ind_).arg(scale_));

  image_ = QImage(600, 400, QImage::Format_ARGB32);

  t_  = 0.0;
  dt_ = 0.1;

  setFixedSize(image_.width(), image_.height());

  QTimer *timer = new QTimer;

  connect(timer, SIGNAL(timeout()), this, SLOT(tickSlot()));

  timer->start(30);
}

void
CQImage2D::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  image2D();

  p.drawImage(0, 0, image_);
}

void
CQImage2D::
keyPressEvent(QKeyEvent *e)
{
  if      (e->key() == Qt::Key_Up) {
    if (scale_ < 64) ++scale_;
  }
  else if (e->key() == Qt::Key_Down) {
    if (scale_ > 1) --scale_;
  }
  else if (e->key() == Qt::Key_Left) {
    if (ind_ > 0) --ind_;
  }
  else if (e->key() == Qt::Key_Right) {
    if (ind_ < maxInd_) ++ind_;
  }

  setWindowTitle(QString("CQImage2D Ind: %1, Scale %2").arg(ind_).arg(scale_));
}

void
CQImage2D::
tickSlot()
{
  //if (dt_ > 0.0 && t_ >= 1.0) { dt_ = -0.01; }
  //if (dt_ < 0.0 && t_ <= 0.0) { dt_ =  0.01; }

  t_ += dt_;

  update();
}

//---------

class Calc {
 public:
  Calc(double t, int scale=1) :
   t_(t), scale_(scale) {
  }

  void render(QImage &image, int num_threads=5);

  virtual uint exec(const IPoint &ip, const Point &p) = 0;

  virtual double mapX(int x) { return -1.0 + (2.0*x)/(w_ - 1); }
  virtual double mapY(int y) { return 1.0 - (2.0*y)/(h_ - 1); }

  int round(double x);

  int sign(double x);

  double random();

 protected:
  double t_;
  int    w_, h_;
  double aspect_;
  int    scale_;
};

struct ThreadData {
  Calc*             calc;
  int               w, h;
  int               scale;
  int               xmin, ymin, xmax, ymax;
  double            rx, ry;
  std::vector<uint> color;
};

static void
ThreadDraw(void *d)
{
  ThreadData *data = (ThreadData *) d;

  Calc *calc = data->calc;

  IPoint ip;
  Point  p;

  int pos = 0;

  for (ip.y = data->ymin; ip.y <= data->ymax; ip.y += data->scale) {
    p.y = calc->mapY(ip.y);

    for (ip.x = data->xmin; ip.x <= data->xmax; ip.x += data->scale, ++pos) {
      p.x = calc->mapX(ip.x);

      data->color[pos] = calc->exec(ip, p);
    }
  }
}

//---------

class Image2D : public Calc {
 public:
  Image2D(double t, int ind=0, int scale=1) :
   Calc(t, scale), ind_(ind) {
  }

  uint exec(const IPoint &, const Point &p) {
    RGB c;

    // diagonals
    if      (ind_ == 0) {
      double col = 0.5*ABS(SIN(p.x*2*M_PI + t_) + COS(p.y*2*M_PI + t_));

      c = RGB(col, col, col);
    }
      // shore
    else if (ind_ == 1) {
      double col = 0.9*SIN(p.x*SIN(p.y)*M_PI*2) +
                   0.1*SIN(100*p.x*COS(p.y) + 5*t_)*COS(t_ + p.x*SIN(p.y)*10 +
                   random());

      c = RGB(col, col, col);
    }
    // rgb
    else if (ind_ == 2) {
      double r = ABS(SIN(p.x + t_));
      double g = ABS(COS(p.y + t_*1.01));
      double b = SIN(p.x*p.y + t_);

      c = RGB(r, g, b);
    }
    // cells
    else if (ind_ == 3) {
      double v = SIN(ABS(COS(ABS(SIN(p.x - 100)*(p.y - 100)))*(t_+100000)));

      c = RGB(v, 0.5-v, v*0.5);
    }
    // tv
    else if (ind_ == 4) {
      c = RGB(random(), random(),random());
    }
    // acid
    else if (ind_ == 5) {
      double v = sqrt(SQR(p.x - 0.5) + SQR(p.y - 0.5));

      v = ABS(SIN(t_ + 1000*sin(v + t_*0.1)));

      c = RGB(1 - v, 0.5 - v, v*v);
    }
    // welcome
    else if (ind_ == 6) {
      double v = sqrt(SQR(2*(p.x - 0.5)) + SQR(aspect_*2*(p.y - 0.5)));

      v = SIN(v*4 - t_);

      c = RGB(1 - v, 0.5 - v, v*v);
    }
    // sunshine
    else if (ind_ == 7) {
      double x = p.x - 0.5;
    //double y = p.y - 0.5;
      double r = sqrt(p.x*p.x + p.y*p.y)*(SIN(t_)*0.2 + 1);
      double v = SIN(x)/r + random()*0.1;

      c = RGB(1 - v, 0.5 - v, v*v);
    }
    // tunnelvision
    else if (ind_ == 8) {
      double x = p.x - 0.5;
      double y = p.y - 0.5;

      double r   = SQRT(x*x + y*y);
      double ang = ATAN(x/r, y/r)/M_PI;
      double col = SIN(ang/r*5 + t_);

      c = RGB(col, col, col);
    }
    // spirals
    else if (ind_ == 9) {
      double x   = p.x - 0.5;
      double y   = aspect_*(p.y - 0.5);
      double r   = SQRT(x*x + y*y);
      double ang = ATAN(x/r, y/r)/(2*M_PI) + 0.5;

      double col = (fmod(ang + r*10 - t_*0.5, 2) > -1 ? 1 : 0);

      c = RGB(col, col, col);
    }
    // meLoveU
    else if (ind_ == 10) {
      double x   = p.x - 0.5;
      double y   = aspect_*(p.y - 0.3);
      double r   = sqrt(x*x + y*y);
      double ang = acos(y/r);
      double v   = SIN(ang + r*10 - t_*0.5)*0.5 + 0.5;

      v = (v < 0.5 ? 0 : v);

      c = RGB(v, 0.1*v, 0.1 + 0.2*v);
    }
    // knight rider
    else if (ind_ == 11) {
      double x = p.x + cos(t_)*0.5;
      int    q = (p.y > 0.4 && p.y < 0.6);
      double v = (((x > 0.4 && x < 0.5) & q) ? 1 : 0);

      v = ((x < 0.4 || x > 0.5) & q) ? random()*0.5 : v;

      c = RGB(v, 0, 0);
    }
    // the architect
    else if (ind_ == 12) {
      double v = ABS(SIN(p.x*3*M_PI + t_)*cos(p.y*aspect_*4*M_PI + M_PI/2));

      v = (v > 0.1 ? v + (0.02*SIN(t_*10000)) : 0);

      c = RGB(v*0.5, v, v*0.4);
    }
    // debiatan
    else if (ind_ == 13) {
      double t = 2*M_PI*fmod(t_/10, 1);
      double x = ((COS(t) + 1)/2)*0.8 + 0.1;
      double y = ((SIN(t) + 1)/2)*0.6 + 0.2;
      double p1 = (sqrt(SQR(p.x - x)/(aspect_*aspect_)+SQR(p.y - y)) < (SIN(t)+1.5)*0.1);
      double p_color = 0.5+(SIN(t + M_PI) + 1)/2;
      double s = ((sqrt(SQR(p.x - 0.5)/(aspect_*aspect_) +
                  SQR(p.y - 0.5)) < 0.1*(1.5 + random()*0.15)) & !p1);
      double sun = s*(0.8+random()*0.2);
      double s2 = (fmod(p.x*93563*p.y*27644437, 5393) < 20) & !p1 & !s;
      double stars = s2*(0.7 + random());

      c = RGB(stars + sun + p1*0.2*p_color, stars + sun + p1*0.3*p_color, stars);
    }
    // mandelbrot
    else if (ind_ == 14) {
      static double limit = std::numeric_limits<double>::max();

      double r = (p.x - 0.5)*4;
      double i = (p.y - 0.5)*4*aspect_;

      double x  = 0;
      double y  = SIN(t_*0.1);
      double xx = x*x - y*y + r;
      double yy = 2*x*y + i;

      for (int ii = 0; ii < 5; ++ii) {
        x  = xx*xx - yy*yy + r;
        y  = 2*xx*yy + i;

        xx = x*x - y*y + r;
        yy = 2*x*y + i;

        if (fabs(xx) > limit || fabs(yy) > limit) break;
      }

      if (fabs(xx) < limit && fabs(yy) < limit) {
        double b  = sqrt(xx*xx + yy*yy);
        double rr = SIN(ATAN(xx, yy));
        double gg = b;
        int    ib = (b < 4);

        c = RGB(rr*ib, gg*ib, 1 - (1 - ib)*p.x);
      }
      else
        c = RGB(0, 0, 0);
    }

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/(w_ - 1); }
  double mapY(int y) { return (1.0*y)/(h_ - 1); }

 private:
  int ind_;
};

void
CQImage2D::
image2D()
{
  Image2D f(t_, ind_, scale_);

  if      (scale_ == 1)
    f.render(image_, 5);
  else if (scale_ < 4)
    f.render(image_, 4);
  else if (scale_ < 8)
    f.render(image_, 3);
  else if (scale_ < 16)
    f.render(image_, 2);
  else
    f.render(image_, 1);
}

//-----

void
Calc::
render(QImage &image, int dim_threads)
{
  int num_threads = dim_threads*dim_threads;

  //-----

  w_ = image.width ();
  h_ = image.height();

  aspect_ = (1.0*h_)/w_;

  //------

  //double dx = (1.0*scale_*((w_ - scale_ + 1)/scale_))/dim_threads;
  //double dy = (1.0*scale_*((h_ - scale_ + 1)/scale_))/dim_threads;
  int dx = (w_ + dim_threads - 1)/dim_threads;
  int dy = (h_ + dim_threads - 1)/dim_threads;

  if (dx == 0 || dy == 0) {
    if (dim_threads > 1)
      render(image, dim_threads - 1);

    return;
  }

  //----

  image.fill(0);

  CThread threads[num_threads];

  ThreadData threadData[num_threads];

  for (int iy = 0, i = 0; iy < dim_threads; ++iy) {
    for (int ix = 0; ix < dim_threads; ++ix, ++i) {
      ThreadData &t = threadData[i];

      t.calc  = this;
      t.w     = w_;
      t.h     = h_;
      t.scale = scale_;
      t.xmin  = int((ix    )*dx);
      t.xmax  = int((ix + 1)*dx) - 1;
      t.ymin  = int((iy    )*dy);
      t.ymax  = int((iy + 1)*dy) - 1;

      t.color.resize((t.xmax - t.xmin + 1)*(t.ymax - t.ymin + 1));
    }
  }

  for (int i = 0; i < num_threads; ++i)
    threads[i].start((CThreadProc) ThreadDraw, (void *) &threadData[i]);

  for (int i = 0; i < num_threads; ++i)
    threads[i].join();

  for (int i = 0; i < num_threads; ++i) {
    ThreadData &t = threadData[i];

    for (int y = t.ymin, pos = 0; y <= t.ymax; y += scale_) {
      for (int x = t.xmin; x <= t.xmax; x += scale_, ++pos) {
        for (int ix = 0; ix < scale_; ++ix) {
          int xx = x + ix;

          for (int iy = 0; iy < scale_; ++iy) {
            int yy = y + iy;

            if (xx < w_ && yy < h_) image.setPixel(xx, yy, t.color[pos]);
          }
        }
      }
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
