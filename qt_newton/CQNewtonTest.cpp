#include <CQNewtonTest.h>
#include <CQNewton.h>
#include <CNewton.h>
#include <CQApp.h>
#include <CQMenu.h>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQNewtonTest qmandelbrot;

  qmandelbrot.setGeometry(10, 10, 400, 400);

  qmandelbrot.show();

  return app.exec();
}

CQNewtonTest::
CQNewtonTest()
{
  newton_ = new CQNewton;

  setCentralWidget(newton_);

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

  //----

  new CQMenu(this, "|");

  //----

  CQMenu *help_menu = new CQMenu(this, "&Help");

  CQMenuItem *help_item = new CQMenuItem(help_menu, "&Help");

  QObject::connect(help_item->getAction(), SIGNAL(triggered()), this, SLOT(help()));
}

CQNewtonTest::
~CQNewtonTest()
{
}

void
CQNewtonTest::
resetRange()
{
  newton_->resetRange();
}

void
CQNewtonTest::
quit()
{
  exit(0);
}

void
CQNewtonTest::
setIterations8()
{
  newton_->setIterations(8);
}

void
CQNewtonTest::
setIterations16()
{
  newton_->setIterations(16);
}

void
CQNewtonTest::
setIterations32()
{
  newton_->setIterations(32);
}

void
CQNewtonTest::
setIterations64()
{
  newton_->setIterations(64);
}

void
CQNewtonTest::
setIterations128()
{
  newton_->setIterations(128);
}

void
CQNewtonTest::
setIterations256()
{
  newton_->setIterations(256);
}

void
CQNewtonTest::
setIterations512()
{
  newton_->setIterations(512);
}

void
CQNewtonTest::
setIterations1024()
{
  newton_->setIterations(1024);
}

void
CQNewtonTest::
toggleShowVector()
{
  newton_->toggleShowVector();
}

void
CQNewtonTest::
help()
{
}
