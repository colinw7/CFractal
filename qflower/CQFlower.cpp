#include <CQFlower.h>

#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QMenu>
#include <QContextMenuEvent>

#include <CCosTable.h>
#include <CSinTable.h>
#include <CTanTable.h>
#include <CATanTable.h>
#include <CSqrtTable.h>
#include <CExpTable.h>
#include <CPerlinNoise.h>
#include <CThread.h>

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

#define LENGTH(p) SQRT(PDOT_SELF(p))

#define ABS(x) (((x) < 0.0) ? -(x) : (x))

#define POS_UNIT(x) (((x) > 0.0) ? 1.0 : 0.0)
//double u(double x) { return 0.5+0.5*sign(x); }
//double u(double x) { return POS_UNIT(x); }
//double u(double x) { return ABS(x)/x; }

#define STEP(r, d) (((d) < (r)) ? 0.0 : 1.0)
//double step(double r, double d) { return (d < r ? 0.0 : 1.0); }

#define TABLE 0

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

  CQFlower *flower = new CQFlower;

  flower->show();

  app.exec();
}

CQFlower::
CQFlower()
{
  mode_ = NOISE_MODE;

  image_ = QImage(512, 512, QImage::Format_ARGB32);

  t_  = 0.0;
  dt_ = 0.01;

  setFixedSize(image_.width(), image_.height());

  QTimer *timer = new QTimer;

  connect(timer, SIGNAL(timeout()), this, SLOT(tickSlot()));

  timer->start(30);
}

void
CQFlower::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  dt_ = 0.01;

  if      (mode_ == FLOWER_MODE)
    flower();
  else if (mode_ == HEART_MODE) {
    heart(); dt_ = 0.05;
  }
  else if (mode_ == PLASMA_MODE)
    plasma();
  else if (mode_ == MONJORI_MODE)
    monjori();
  else if (mode_ == METABLOB_MODE)
    metablob();
  else if (mode_ == CRYSTALS_MODE) {
    quasi_crystals(); dt_ = 0.5;
  }
  else if (mode_ == NOISE_MODE) {
    noise();
  }

  p.drawImage(0, 0, image_);
}

void
CQFlower::
contextMenuEvent(QContextMenuEvent *e)
{
  QMenu *menu = new QMenu(this);

  menu->addAction("Flower");
  menu->addAction("Heart");
  menu->addAction("Plasma");
  menu->addAction("Monjori");
  menu->addAction("Metablob");
  menu->addAction("Crystals");
  menu->addAction("Noise");

  connect(menu, SIGNAL(triggered(QAction *)), this, SLOT(menuActionSlot(QAction *)));

  menu->popup(mapToGlobal(e->pos()));
}

void
CQFlower::
menuActionSlot(QAction *a)
{
  if      (a->text() == "Flower")
    mode_ = FLOWER_MODE;
  else if (a->text() == "Heart")
    mode_ = HEART_MODE;
  else if (a->text() == "Plasma")
    mode_ = PLASMA_MODE;
  else if (a->text() == "Monjori")
    mode_ = MONJORI_MODE;
  else if (a->text() == "Metablob")
    mode_ = METABLOB_MODE;
  else if (a->text() == "Crystals")
    mode_ = CRYSTALS_MODE;
  else if (a->text() == "Noise")
    mode_ = NOISE_MODE;
}

void
CQFlower::
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
  Calc(double t) :
   t_(t) {
  }

  void render(QImage &image);

  virtual uint exec(const IPoint &ip, const Point &p) = 0;

  virtual double mapX(int x) { return -1.0 + (2.0*x)/(w_ - 1); }
  virtual double mapY(int y) { return 1.0 - (2.0*y)/(h_ - 1); }

 protected:
  double t_;
  int    w_, h_;
};

struct ThreadData {
  Calc*             calc;
  int               w, h;
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

  for (ip.y = data->ymin; ip.y <= data->ymax; ++ip.y) {
    p.y = calc->mapY(ip.y);

    for (ip.x = data->xmin; ip.x <= data->xmax; ++ip.x, ++pos) {
      p.x = calc->mapX(ip.x);

      data->color[pos] = calc->exec(ip, p);
    }
  }
}

//---------

class Flower : public Calc {
 public:
  Flower(double t) :
   Calc(t) {
  }

  uint exec(const IPoint &, const Point &p) {
    double a = ATAN(p.x, p.y);
    double r = LENGTH(p)*0.75;

    double w = COS(M_PI*t_ - r*2.0);

    double h = 0.50 + 0.50*COS(12.0*a - w*7.0 + r*8.0);

    double d = 0.25 + 0.75*pow(h, 1.0*r)*(0.7 + 0.3*w);

    double col = POS_UNIT(d - r)*SQRT(1.0-r/d)*r*2.5;

    col *= 1.25 + 0.25*COS((12.0*a -w*7.0 + r*8.0)/2.0);

    col *= 1.00 - 0.35*(0.5 + 0.5*SIN(r*30.0))*(0.5 + 0.5*COS(12.0*a - w*7.0 + r*8.0));

    RGB c(col, col - h*0.5 + r*0.2 + 0.35*h*(1.0 - r), col - h*r + 0.1*h*(1.0 - r));

    return c.toInt();
  }
};

void
CQFlower::
flower()
{
  Flower f(t_);

  f.render(image_);
}

//-----

class Heart : public Calc {
 public:
  Heart(double t) :
   Calc(t) {
  }

  uint exec(const IPoint &, const Point &p) {
    // animate
    double tt = MOD(t_, 2.0)/2.0;
    double ss = pow(tt, 0.2)*0.5 + 0.5;

    ss -= ss*0.2*SIN(tt*M_PI*10.0)*EXP(-tt*6.0);

    Point p1(p.x*(0.5 + 0.5*ss), p.y*(1.5 - 0.5*ss));

    double a = ATAN(p1.x, p1.y)/M_PI;
    double r = LENGTH(p1);

    // shape
    double h = ABS(a);
    double d = (13.0*h - 22.0*h*h + 10.0*h*h*h)/(6.0 - 5.0*h);

    // color
    double f = STEP(r, d)*pow(1.0- r/d, 0.25);

    RGB c(f, 0.0, 0.0);

    return c.toInt();
  }

  double mapX(int x) { return (2.0*x)/(w_ - 1) - 1.0; }
  double mapY(int y) { return 1.0 - (2.0*y)/(h_ - 1); }
//double mapY(int y) { return 0.4 - (1.5*y)/(h_ - 1); }
};

void
CQFlower::
heart()
{
  Heart h(t_);

  h.render(image_);
}

//-----------

class Plasma : public Calc {
 public:
  Plasma(double t) :
   Calc(t) {
  }

  uint exec(const IPoint &ip, const Point &p) {
    double mov0 = ip.x + ip.y + COS(SIN(t_)*2.0)*100.0 + SIN(ip.x/100.0)*1000.0;
    double mov1 = p.y/0.2 + t_;
    double mov2 = p.x/0.2;

    double c1 = ABS(SIN(mov1 + t_)/2.0 + mov2/2.0 - mov1 - mov2 + t_);
    double c2 = ABS(SIN(c1 + SIN(mov0/1000.0 + t_) +
                    SIN(ip.y/40.0 + t_) + SIN((ip.x + ip.y)/100.0)*3.0));
    double c3 = ABS(SIN(c2 + COS(mov1 + mov2 + c2) + COS(mov2) + SIN(ip.x/1000.0)));

    RGB c(c1,c2,c3);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/(w_ - 1); }
  double mapY(int y) { return 1.0 - (1.0*y)/(h_ - 1); }
};

void
CQFlower::
plasma()
{
  Plasma p(t_);

  p.render(image_);
}

//-----------

class Monjori : public Calc {
 public:
  Monjori(double t) :
   Calc(t) {
  }

  uint exec(const IPoint &, const Point &p) {
    static double g = 1.0/40.0;

    double a = t_*40.0;

    double e = 400.0*(p.x*0.5 + 0.5);
    double f = 400.0*(p.y*0.5 + 0.5);
    double i = 200.0 + SIN(e*g + a/150.0)*20.0;
    double d = 200.0 + COS(f*g/2.0)*18.0 + COS(e*g)*7.0;

    double r = sqrt(POW2(i - e) + POW2(d - f));

    double q = f/r;

    e = (r*COS(q)) - a/2.0;
    f = (r*SIN(q)) - a/2.0;

    d = SIN(e*g)*176.0 + SIN(e*g)*164.0 + r;

    double h = ((f + d) + a/2.0)*g;

    i = COS(h + r*p.x/1.3)*(e + e + a) + COS(q*g*6.0)*(r + h/3.0);
    h = SIN(f*g)*144.0 - SIN(e*g)*212.0*p.x;
    h = (h + (f - e)*q + SIN(r - (a + h)/7.0)*10.0 + i/4.0)*g;

    i += COS(h*2.3*SIN(a/350.0 - q))*184.0*SIN(q - (r*4.3 + a/12.0)*g) +
         TAN(r*g + h)*184.0*COS(r*g + h);

    i = MOD(i/5.6, 256.0)/64.0;

    if (i <  0.0) i += 4.0;
    if (i >= 2.0) i  = 4.0 - i;

    d = r/350.0;

    d += SIN(d*d*8.0)*0.52;

    f = (SIN(a*g) + 1.0)/2.0;

    RGB c1(f*i/1.6        , i/2.0 + d/13.0, i);
    RGB c2(  i/1.3 + d/8.0, i/2.0 + d/18.0, i);

    RGB c = c1*d*p.x + c2*d*(1.0 - p.x);

    return c.toInt();
  }
};

void
CQFlower::
monjori()
{
  Monjori m(t_);

  m.render(image_);
}

//-----------

class Metablob : public Calc {
 public:
  Metablob(double t) :
   Calc(t) {
    //the centre point for each blob
    m1_ = Point(COS(t_    )*0.4, SIN(t_*1.5)*0.4);
    m2_ = Point(COS(t_*2.0)*0.4, SIN(t_*3.0)*0.4);
  }

  uint exec(const IPoint &, const Point &p) {
    //radius for each blob
    Point p1 = p - m1_;
    Point p2 = p + m2_;

    double r1 = PDOT_SELF(p1)* 8.0;
    double r2 = PDOT_SELF(p2)*16.0;

    //sum the meatballs
    double metaball = (1.0/r1 + 1.0/r2);

    //alter the cut-off power
    double col = POW8(metaball);

    //set the output color
    //if (col < 0.0) col = 0.0;
    if (col > 1.0) col = 1.0;

    return RGB(col).toInt();
  }

 private:
  Point m1_, m2_;
};

void
CQFlower::
metablob()
{
  Metablob m(t_);

  m.render(image_);
}

//-----------

class QuasiCrystals : public Calc {
 public:
  QuasiCrystals(double t) :
   Calc(t) {
  }

  uint exec(const IPoint &, const Point &p) {
    static double c = 0.90096886790241, s = 0.43388373911755; // sin and cos of pi / 7

    static Point rx(c, s), ry(-s, c);

    Point up(64 /*256*/, 0); // change this for finer/coarser stripes

    double sum = 0.0;

    for (int i = 0; i < 7; ++i) {
      sum += COS(PDOT(p, up) + t_);

      up = Point(PDOT(up, rx), PDOT(up, ry));
    }

    // the important wrap around term. play with this for different effects
    double a1 = (COS(sum + 2.0) + 1.0)*0.5;

    return RGB(a1,a1,a1).toInt();
  }
};

void
CQFlower::
quasi_crystals()
{
  QuasiCrystals q(t_);

  q.render(image_);
}

//-----------

class Noise : public Calc {
 public:
  Noise(double t) :
   Calc(t) {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &, const Point &p) {
    double dx = SIN(t_);
    double dy = COS(t_);

    Point q = Point(noise(p + Point(dx , dy )),
                    noise(p + Point(5.2, 1.3)));

    Point r = Point(noise(p + 4.0*q + Point(1.7, 9.2)),
                    noise(p + 4.0*q + Point(8.3, 2.8)));

    double g = noise(p + 4.0*r);

    double red   = sqrt(q.x*q.x + q.y*q.y)/1.5;
    double green = r.x;
    double blue  = r.y;

    RGB c((g + red)/2, (g + green)/2, (g + blue)/2);

    return c.toInt();
  }

  double noise(const Point &p) {
    return noise_->noise(p.x, p.y, 0.9);
    //return noise_->scaledNoise(p.x, p.y, 0.9);
  }

  //double mapX(int x) { return (1.0*x)/w_; }
  //double mapY(int y) { return (1.0*y)/h_; }
  double mapX(int x) { return -3.0 + (6.0*x)/(w_ - 1); }
  double mapY(int y) { return  3.0 - (6.0*y)/(h_ - 1); }

 private:
  CPerlinNoise *noise_;
};

void
CQFlower::
noise()
{
  Noise q(t_);

  q.render(image_);
}

//-----------

double
CQFlower::
dotSelf(const Point &p)
{
  return (p.x*p.x + p.y*p.y);
}

double
CQFlower::
dot(const Point &p1, const Point &p2)
{
  return (p1.x*p2.x + p1.y*p2.y);
}

//-----------

void
Calc::
render(QImage &image)
{
  static uint dim_threads = 4;
  static uint num_threads = dim_threads*dim_threads;

  //-----

  w_ = image.width ();
  h_ = image.height();

  //------

  ThreadData threadData[num_threads];

  CThread threads[num_threads];

  double dx = (1.0*w_)/dim_threads;
  double dy = (1.0*h_)/dim_threads;

  for (uint iy = 0, i = 0; iy < dim_threads; ++iy) {
    for (uint ix = 0; ix < dim_threads; ++ix, ++i) {
      ThreadData &t = threadData[i];

      t.calc = this;
      t.w    = w_;
      t.h    = h_;
      t.xmin = int((ix    )*dx);
      t.xmax = int((ix + 1)*dx) - 1;
      t.ymin = int((iy    )*dy);
      t.ymax = int((iy + 1)*dy) - 1;

      t.color.resize((t.xmax - t.xmin + 1)*(t.ymax - t.ymin + 1));
    }
  }

  for (uint i = 0; i < num_threads; ++i)
    threads[i].start((CThreadProc) ThreadDraw, (void *) &threadData[i]);

  for (uint i = 0; i < num_threads; ++i)
    threads[i].join();

  for (uint i = 0; i < num_threads; ++i) {
    ThreadData &t = threadData[i];

    for (int y = t.ymin, pos = 0; y <= t.ymax; ++y) {
      for (int x = t.xmin; x <= t.xmax; ++x, ++pos) {
        image.setPixel(x, y, t.color[pos]);
      }
    }
  }
}
