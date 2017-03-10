#include <CQBifurication.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <QPainter>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQBifuricationTest bifurication;

  bifurication.setGeometry(10, 10, 400, 400);

  bifurication.show();

  return app.exec();
}

CQBifuricationTest::
CQBifuricationTest()
{
  bifurication_ = new CQBifurication;

  setCentralWidget(bifurication_);

  //----

  CQMenu *file_menu = new CQMenu(this, "&File");

  CQMenuItem *quit_item = new CQMenuItem(file_menu, "&Quit");

  QObject::connect(quit_item->getAction(), SIGNAL(triggered()), this, SLOT(quit()));

  //----

  CQMenu *display_menu = new CQMenu(this, "&Display");

  CQMenuItem *feigenbaum_item = new CQMenuItem(display_menu, "&Feigenbaum", CQMenuItem::CHECKABLE);

  QObject::connect(feigenbaum_item->getAction(), SIGNAL(toggled(bool)),
                   this, SLOT(setFeigenbaum(bool)));

  //----

  CQMenu *help_menu = new CQMenu(this, "&Help");

  CQMenuItem *help_item = new CQMenuItem(help_menu, "&Help");

  QObject::connect(help_item->getAction(), SIGNAL(triggered()), this, SLOT(help()));
}

void
CQBifuricationTest::
quit()
{
  exit(0);
}

void
CQBifuricationTest::
setFeigenbaum(bool set)
{
  bifurication_->setFeigenbaum(set);

  bifurication_->update();
}

void
CQBifuricationTest::
help()
{
}

//------

CQBifurication::
CQBifurication(QWidget *parent) :
 QWidget(parent)
{
}

void
CQBifurication::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter_ = &painter;

  CBifurication::draw(width(), height());
}

void
CQBifurication::
drawPoint(int x, int y)
{
  painter_->drawPoint(QPoint(x, y));
}
