#include <CQMandelbrotTest.h>
#include <CQMandelbrot.h>
#include <CMandelbrot.h>

#include <QApplication>
#include <CQMenu.h>
#include <QTimer>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  app.setFont(QFont("helvetica", 10));

  CQMandelbrotTest qmandelbrot;

  qmandelbrot.setGeometry(10, 10, 400, 400);

  qmandelbrot.show();

  return app.exec();
}

CQMandelbrotTest::
CQMandelbrotTest() :
 timer_(0), animating_(false), t_(0)
{
  mandelbrot_ = new CQMandelbrot;

  setCentralWidget(mandelbrot_);

  //----

  CQMenu *file_menu = new CQMenu(this, "&File");

  CQMenuItem *quit_item = new CQMenuItem(file_menu, "&Quit");

  QObject::connect(quit_item->getAction(), SIGNAL(triggered()), this, SLOT(quit()));

  //----

  CQMenu *iter_menu = new CQMenu(this, "&Iterations");

  iter_menu->startGroup();

  CQMenuItem *iter1_item = new CQMenuItem(iter_menu,    "8", CQMenuItem::CHECKABLE);
  CQMenuItem *iter2_item = new CQMenuItem(iter_menu,   "16", CQMenuItem::CHECKABLE);
  CQMenuItem *iter3_item = new CQMenuItem(iter_menu,   "32", CQMenuItem::CHECKABLE);
  CQMenuItem *iter4_item = new CQMenuItem(iter_menu,   "64", CQMenuItem::CHECKABLE);
  CQMenuItem *iter5_item = new CQMenuItem(iter_menu,  "128", CQMenuItem::CHECKABLE);
  CQMenuItem *iter6_item = new CQMenuItem(iter_menu,  "256", CQMenuItem::CHECKED  );
  CQMenuItem *iter7_item = new CQMenuItem(iter_menu,  "512", CQMenuItem::CHECKABLE);
  CQMenuItem *iter8_item = new CQMenuItem(iter_menu, "1024", CQMenuItem::CHECKABLE);
  CQMenuItem *iter9_item = new CQMenuItem(iter_menu, "2048", CQMenuItem::CHECKABLE);

  iter_menu->endGroup();

  QObject::connect(iter1_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations8()));
  QObject::connect(iter2_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations16()));
  QObject::connect(iter3_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations32()));
  QObject::connect(iter4_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations64()));
  QObject::connect(iter5_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations128()));
  QObject::connect(iter6_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations256()));
  QObject::connect(iter7_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations512()));
  QObject::connect(iter8_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations1024()));
  QObject::connect(iter9_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations2048()));

  //----

  CQMenu *display_menu = new CQMenu(this, "&Display");

  CQMenuItem *reset_item = new CQMenuItem(display_menu, "&Reset");

  QObject::connect(reset_item->getAction(), SIGNAL(triggered()), this, SLOT(resetRange()));

  CQMenuItem *show_vector_item =
    new CQMenuItem(display_menu, "Show &Vector", CQMenuItem::CHECKABLE);

  QObject::connect(show_vector_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(toggleShowVector()));

  CQMenuItem *thread_item =
    new CQMenuItem(display_menu, "Threaded", CQMenuItem::CHECKED);

  QObject::connect(thread_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(toggleThreaded()));

  CQMenuItem *animate_item =
    new CQMenuItem(display_menu, "Animate", CQMenuItem::CHECKABLE);

  QObject::connect(animate_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(toggleAnimate()));

  //----

  new CQMenu(this, "|");

  //----

  CQMenu *help_menu = new CQMenu(this, "&Help");

  CQMenuItem *help_item = new CQMenuItem(help_menu, "&Help");

  QObject::connect(help_item->getAction(), SIGNAL(triggered()), this, SLOT(help()));
}

CQMandelbrotTest::
~CQMandelbrotTest()
{
}

void
CQMandelbrotTest::
resetRange()
{
  mandelbrot_->resetRange();
}

void
CQMandelbrotTest::
quit()
{
  exit(0);
}

void
CQMandelbrotTest::
setIterations8()
{
  mandelbrot_->setIterations(8);
}

void
CQMandelbrotTest::
setIterations16()
{
  mandelbrot_->setIterations(16);
}

void
CQMandelbrotTest::
setIterations32()
{
  mandelbrot_->setIterations(32);
}

void
CQMandelbrotTest::
setIterations64()
{
  mandelbrot_->setIterations(64);
}

void
CQMandelbrotTest::
setIterations128()
{
  mandelbrot_->setIterations(128);
}

void
CQMandelbrotTest::
setIterations256()
{
  mandelbrot_->setIterations(256);
}

void
CQMandelbrotTest::
setIterations512()
{
  mandelbrot_->setIterations(512);
}

void
CQMandelbrotTest::
setIterations1024()
{
  mandelbrot_->setIterations(1024);
}

void
CQMandelbrotTest::
setIterations2048()
{
  mandelbrot_->setIterations(2048);
}

void
CQMandelbrotTest::
toggleShowVector()
{
  mandelbrot_->toggleShowVector();
}

void
CQMandelbrotTest::
toggleAnimate()
{
  if (animating_) {
    timer_->stop();
  }
  else {
    if (! timer_) {
      timer_ = new QTimer;

      connect(timer_, SIGNAL(timeout()), this, SLOT(animateSlot()));
    }

    timer_->start(100);
  }

  animating_ = ! animating_;
}

void
CQMandelbrotTest::
toggleThreaded()
{
  mandelbrot_->setThreaded(! mandelbrot_->isThreaded());
}

void
CQMandelbrotTest::
animateSlot()
{
  static double xc = -0.745;
  static double yc =  0.186;

  double t = sin(2*M_PI*(t_/500.0));

  double z = 0.62 + 0.38*t;

  double a = (1.0 - z)*t;

  z = pow(z, 8.0);

  CMandelbrot *mandelbrot = mandelbrot_->getMandelbrot();

  double s = 1.6*z;

  mandelbrot->setAngle(2*M_PI*a);

  mandelbrot_->setRange(QRect(xc - s, yc - s, 2*s, 2*s));

  ++t_;

  if (t_ >= 500)
    t_ = 0;

  mandelbrot_->redraw();
}

void
CQMandelbrotTest::
help()
{
}
