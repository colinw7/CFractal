#include <CQJuliaTest.h>
#include <CQJulia.h>
#include <CJulia.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <QTimer>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQJuliaTest qmandelbrot;

  qmandelbrot.setGeometry(10, 10, 400, 400);

  qmandelbrot.show();

  return app.exec();
}

CQJuliaTest::
CQJuliaTest()
{
  julia_ = new CQJulia;

  setCentralWidget(julia_);

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

  iter_menu->endGroup();

  QObject::connect(iter1_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations8()));
  QObject::connect(iter2_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations16()));
  QObject::connect(iter3_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations32()));
  QObject::connect(iter4_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations64()));
  QObject::connect(iter5_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations128()));
  QObject::connect(iter6_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations256()));
  QObject::connect(iter7_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations512()));
  QObject::connect(iter8_item->getAction(), SIGNAL(triggered()), this, SLOT(setIterations1024()));

  //----

  CQMenu *display_menu = new CQMenu(this, "&Display");

  CQMenuItem *reset_item = new CQMenuItem(display_menu, "&Reset");

  QObject::connect(reset_item->getAction(), SIGNAL(triggered()), this, SLOT(resetRange()));

  CQMenuItem *show_vector_item =
    new CQMenuItem(display_menu, "Show &Vector", CQMenuItem::CHECKABLE);

  QObject::connect(show_vector_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(toggleShowVector()));

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

CQJuliaTest::
~CQJuliaTest()
{
}

void
CQJuliaTest::
resetRange()
{
  julia_->resetRange();
}

void
CQJuliaTest::
quit()
{
  exit(0);
}

void
CQJuliaTest::
setIterations8()
{
  julia_->setIterations(8);
}

void
CQJuliaTest::
setIterations16()
{
  julia_->setIterations(16);
}

void
CQJuliaTest::
setIterations32()
{
  julia_->setIterations(32);
}

void
CQJuliaTest::
setIterations64()
{
  julia_->setIterations(64);
}

void
CQJuliaTest::
setIterations128()
{
  julia_->setIterations(128);
}

void
CQJuliaTest::
setIterations256()
{
  julia_->setIterations(256);
}

void
CQJuliaTest::
setIterations512()
{
  julia_->setIterations(512);
}

void
CQJuliaTest::
setIterations1024()
{
  julia_->setIterations(1024);
}

void
CQJuliaTest::
toggleShowVector()
{
  julia_->toggleShowVector();
}

void
CQJuliaTest::
toggleAnimate()
{
  if (animating_) {
    timer_->stop();

    animating_ = false;
  }
  else {
    if (! timer_) {
      timer_ = new QTimer;

      connect(timer_, SIGNAL(timeout()), this, SLOT(animateSlot()));
    }

    timer_->start(100);

    animating_ = true;
  }
}

void
CQJuliaTest::
animateSlot()
{
  julia_->getJulia()->setTime(t_/100.0);

  ++t_;

  if (t_ >= 100)
    t_ = 0;

  julia_->redraw();
}

void
CQJuliaTest::
help()
{
}
