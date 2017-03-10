#include <CQTexture.h>
#include <CPerlinNoise.h>
#include <CThread.h>

#include <QApplication>
#include <QPainter>
#include <QKeyEvent>
#include <cmath>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQTexture *texture = new CQTexture;

  texture->show();

  app.exec();
}

CQTexture::
CQTexture() :
 n_(10)
{
  image_ = QImage(500, 500, QImage::Format_ARGB32);

  setFixedSize(image_.width(), image_.height());
}

void
CQTexture::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  switch (n_) {
    case 0 : texture1 (state_); break;
    case 1 : texture2 (state_); break;
    case 2 : texture3 (state_); break;
    case 3 : texture4 (state_); break;
    case 4 : texture5 (state_); break;
    case 5 : texture6 (state_); break;
    case 6 : texture7 (state_); break;
    case 7 : texture8 (state_); break;
    case 8 : texture9 (state_); break;
    case 9 : texture10(state_); break;
    case 10: texture11(state_); break;
  }

  p.drawImage(0, 0, image_);
}

void
CQTexture::
mousePressEvent(QMouseEvent *)
{
  ++n_;

  if (n_ > 9) n_ = 0;

  update();
}

void
CQTexture::
keyPressEvent(QKeyEvent *e)
{
  if      (e->key() == Qt::Key_Up   ) state_.dy++;
  else if (e->key() == Qt::Key_Down ) state_.dy--;
  else if (e->key() == Qt::Key_Left ) state_.dx++;
  else if (e->key() == Qt::Key_Right) state_.dx--;

  update();
}

//---------

class Calc {
 public:
  Calc() { }

  void render(QImage &image);

  virtual uint exec(const IPoint &ip, const Point &p) = 0;

  virtual double mapX(int x) { return -1.0 + (2.0*x)/(w_ - 1); }
  virtual double mapY(int y) { return 1.0 - (2.0*y)/(h_ - 1); }

 protected:
  int w_, h_;
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

class Texture1 : public Calc {
 public:
  Texture1(const State &s) :
   Calc() {
    noise_ = CPerlinNoiseInst;

    cos_scale_ =  85.0 + s.dy;
    x_scale_   =  45.0;
    y_scale_   = 120.0;
    factor_    = (89.0 + s.dx)/100; //  0.89;
  }

  uint exec(const IPoint &ip, const Point &) {
    double n = noise_->scaledNoise(ip.x/x_scale_, ip.y/y_scale_, factor_);

    n = cos(n*cos_scale_);

    RGB c(n, n - 1.0, 1.0 - n);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
  double        cos_scale_;
  double        x_scale_;
  double        y_scale_;
  double        factor_;
};

void
CQTexture::
texture1(const State &s)
{
  Texture1 f(s);

  f.render(image_);
}

//---------

class Texture2 : public Calc {
 public:
  Texture2() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &ip, const Point &) {
    double centerx = w_/2.0;
    double centery = h_/2.0;

    double dx = ip.x - centerx;
    double dy = ip.y - centery;

    double dist = (dx*dx + dy*dy)/6000;

    double n = noise_->scaledNoise(ip.x/5.0, ip.y/5.0, 0.18);

    double r = 1.0 - dist*n;

    RGB c(r, r - 1.0, 0.0);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture2(const State &)
{
  Texture2 f;

  f.render(image_);
}

//---------

class Texture3 : public Calc {
 public:
  Texture3() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &, const Point &p) {
    static double sizex = 1.5;
    static double sizey = 10;

    double n = noise_->scaledNoise(sizex*p.x, sizey*p.y, 0.4);

    double x = sqrt(1 + cos(n + 2*M_PI*p.x - 0.5));
    double y = p.y*p.y;

    RGB c(1.0 - x, 1.0 - n*x, y);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture3(const State &)
{
  Texture3 f;

  f.render(image_);
}

//---------

class Texture4 : public Calc {
 public:
  Texture4() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &, const Point &p) {
    static double two_pi = 2*M_PI;

    static double size = 20;

    double n = noise_->scaledNoise(size*p.x, size*p.y, 0.9);

    double b = 1.0 - (1.0 + sin(n + two_pi*p.x))/2;
    double g = 1.0 - (1.0 + cos(n + two_pi*p.x))/2;
    double r = 1.0 - (1.0 - sin(n + two_pi*p.x))/2;

    RGB c(r, g, b);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture4(const State &)
{
  Texture4 f;

  f.render(image_);
}

//---------

class Texture5 : public Calc {
 public:
  Texture5() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &, const Point &p) {
    static double size = 10;

    double n = noise_->scaledNoise(size*p.x, size*p.y, 0.8);

    RGB c(n, n, n);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture5(const State &)
{
  Texture5 f;

  f.render(image_);
}

//---------

class Texture6 : public Calc {
 public:
  Texture6() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &ip, const Point &) {
    double x = ip.x/30.0;
    double y = ip.y/(3*(ip.y + x)/w_);

    double n = noise_->scaledNoise(x, y, 0.18);

    RGB c(0.0, n - 1.0, n);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture6(const State &)
{
  Texture6 f;

  f.render(image_);
}

//---------

class Texture7 : public Calc {
 public:
  Texture7() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &ip, const Point &) {
    double centerx = w_/2.0;
    double centery = h_/2.0;

    double dx = ip.x - centerx;
    double dy = ip.y - centery;

    double dist = 1.2*sqrt(dx*dx + dy*dy);

    double n = noise_->scaledNoise(ip.x/30.0, ip.y/110.0, 0.28);

    double dterm = (dist/88)*n;

    double r = dist < 151 ? dterm     : 1.0;
    double b = dist < 151 ? 1.0 - r   : 1.0;
    double g = dist < 151 ? dterm/1.5 : 1.0;

    RGB c(r, g, b);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture7(const State &)
{
  Texture7 f;

  f.render(image_);
}

//---------

class Texture8 : public Calc {
 public:
  Texture8() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &, const Point &p) {
    double sizex = 3.0;
    double sizey = 66.0;

    double n = noise_->scaledNoise(sizex*p.x, sizey*p.y, 0.1);

    double x = (1 + sin(M_PI*p.x))/2;
    double y = (1 + sin(n*8*p.y))/2;

    double b = n*y*x;
    double r = y*b;
    double g = y;

    RGB c(r, g, b);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture8(const State &)
{
  Texture8 f;

  f.render(image_);
}

//---------

class Texture9 : public Calc {
 public:
  Texture9() :
   Calc() {
  }

  uint exec(const IPoint &, const Point &p) {
    static double two_pi = 2*M_PI;

    double b = 1.0 - p.y*(1.0 + sin(two_pi*p.x))/2;
    double g = 1.0 - p.y*(1.0 + cos(two_pi*p.x))/2;
    double r = 1.0 - p.y*(1.0 - sin(two_pi*p.x))/2;

    RGB c(r, g, b);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }
};

void
CQTexture::
texture9(const State &)
{
  Texture9 f;

  f.render(image_);
}

//---------

class Texture10 : public Calc {
 public:
  Texture10() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &, const Point &p) {
    static double size = 19;

    double n = noise_->scaledNoise(size*p.x, size*p.y, 0.9);

    double x = (1 + cos(n + 2*M_PI*p.x - 0.5));
    double y = (1 + cos(    2*M_PI*p.y)      );
    //x = Math.sqrt(x); y = Math.sqrt(y);

    double r = 1.0 - y*x*n;
    double g = r;
    double b = 1.0 - r;

    RGB c(r, g, b);

    return c.toInt();
  }

  double mapX(int x) { return (1.0*x)/w_; }
  double mapY(int y) { return (1.0*y)/h_; }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture10(const State &)
{
  Texture10 f;

  f.render(image_);
}

//---------

class Texture11 : public Calc {
 public:
  Texture11() :
   Calc() {
    noise_ = CPerlinNoiseInst;
  }

  uint exec(const IPoint &, const Point &p) {
    Point q = Point(noise(p + Point(0.0, 0.0)),
                    noise(p + Point(5.2, 1.3)));

    Point r = Point(noise(p + 4.0*q + Point(1.7, 9.2)),
                    noise(p + 4.0*q + Point(8.3, 2.8)));

    double g = noise(p + 4.0*r);

    double red   = sqrt(q.x*q.x + q.y*q.y)/4;
    double green = r.x/2;
    double blue  = r.y/2;

    RGB c(g + red, g + green, g + blue);

    return c.toInt();
  }

  double noise(const Point &p) {
    return noise_->noise(p.x, p.y, 0.0);
  }

  //double mapX(int x) { return (1.0*x)/w_; }
  //double mapY(int y) { return (1.0*y)/h_; }
  double mapX(int x) { return -3.0 + (6.0*x)/(w_ - 1); }
  double mapY(int y) { return  3.0 - (6.0*y)/(h_ - 1); }

 private:
  CPerlinNoise *noise_;
};

void
CQTexture::
texture11(const State &)
{
  Texture11 f;

  f.render(image_);
}

//-----

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
