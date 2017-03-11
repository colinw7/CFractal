#include <CQBarnsleyTest.h>
#include <CQBarnsley.h>
#include <CBarnsley.h>
#include <CQApp.h>
#include <CQMenu.h>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQBarnsleyTest qbarnsley;

  qbarnsley.setGeometry(10, 10, 400, 400);

  qbarnsley.show();

  return app.exec();
}

CQBarnsleyTest::
CQBarnsleyTest()
{
  barnsley_ = new CQBarnsley;

  setCentralWidget(barnsley_);

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

  CQMenu *type_menu = new CQMenu(this, "&Type");

  CQMenuItem *type1_item = new CQMenuItem(type_menu, "Type &1");
  CQMenuItem *type2_item = new CQMenuItem(type_menu, "Type &2");
  CQMenuItem *type3_item = new CQMenuItem(type_menu, "Type &3");
  CQMenuItem *type4_item = new CQMenuItem(type_menu, "Type &4");

  QObject::connect(type1_item->getAction(), SIGNAL(triggered()), this, SLOT(type1Slot()));
  QObject::connect(type2_item->getAction(), SIGNAL(triggered()), this, SLOT(type2Slot()));
  QObject::connect(type3_item->getAction(), SIGNAL(triggered()), this, SLOT(type3Slot()));
  QObject::connect(type4_item->getAction(), SIGNAL(triggered()), this, SLOT(type4Slot()));

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

CQBarnsleyTest::
~CQBarnsleyTest()
{
}

void
CQBarnsleyTest::
resetRange()
{
  barnsley_->resetRange();
}

void
CQBarnsleyTest::
quit()
{
  exit(0);
}

void
CQBarnsleyTest::
setIterations8()
{
  barnsley_->setIterations(8);
}

void
CQBarnsleyTest::
setIterations16()
{
  barnsley_->setIterations(16);
}

void
CQBarnsleyTest::
setIterations32()
{
  barnsley_->setIterations(32);
}

void
CQBarnsleyTest::
setIterations64()
{
  barnsley_->setIterations(64);
}

void
CQBarnsleyTest::
setIterations128()
{
  barnsley_->setIterations(128);
}

void
CQBarnsleyTest::
setIterations256()
{
  barnsley_->setIterations(256);
}

void
CQBarnsleyTest::
setIterations512()
{
  barnsley_->setIterations(512);
}

void
CQBarnsleyTest::
setIterations1024()
{
  barnsley_->setIterations(1024);
}

void
CQBarnsleyTest::
toggleShowVector()
{
  barnsley_->toggleShowVector();
}

void
CQBarnsleyTest::
type1Slot()
{
  barnsley_->getBarnsley()->setType(CBarnsley::B1);

  barnsley_->redraw();
}

void
CQBarnsleyTest::
type2Slot()
{
  barnsley_->getBarnsley()->setType(CBarnsley::B2);

  barnsley_->redraw();
}

void
CQBarnsleyTest::
type3Slot()
{
  barnsley_->getBarnsley()->setType(CBarnsley::B3);

  barnsley_->redraw();
}

void
CQBarnsleyTest::
type4Slot()
{
  barnsley_->getBarnsley()->setType(CBarnsley::B4);

  barnsley_->redraw();
}

void
CQBarnsleyTest::
help()
{
}
