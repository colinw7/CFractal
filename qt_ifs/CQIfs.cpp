#include <CQIfs.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <CIfs.h>
#include <CQTurtle.h>
#include <CQUtil.h>
#include <COSFile.h>

#include <QPainter>
#include <QFileDialog>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQIfsTest ifs;

  ifs.setGeometry(10, 10, 400, 400);

  ifs.show();

  return app.exec();
}

CQIfsTest::
CQIfsTest()
{
  ifs_ = new CQIfs;

  setCentralWidget(ifs_);

  //----

  CQMenu *fileMenu = new CQMenu(this, "&File");

  CQMenuItem *loadItem = new CQMenuItem(fileMenu, "&Load File");

  connect(loadItem->getAction(), SIGNAL(triggered()), this, SLOT(loadSlot()));

  CQMenuItem *quitItem = new CQMenuItem(fileMenu, "&Quit");

  QObject::connect(quitItem->getAction(), SIGNAL(triggered()), this, SLOT(quitSlot()));

  //----

  CQMenu *viewMenu = new CQMenu(this, "&View");

  CQMenuItem *incItem = new CQMenuItem(viewMenu, "&Increase Depth");
  CQMenuItem *decItem = new CQMenuItem(viewMenu, "&Decrease Depth");

  incItem->setShortcut(QKeySequence(Qt::Key_Plus));
  decItem->setShortcut(QKeySequence(Qt::Key_Minus));

  QObject::connect(incItem->getAction(), SIGNAL(triggered()), this, SLOT(incSlot()));
  QObject::connect(decItem->getAction(), SIGNAL(triggered()), this, SLOT(decSlot()));

  //----

  CQMenu *help_menu = new CQMenu(this, "&Help");

  CQMenuItem *help_item = new CQMenuItem(help_menu, "&Help");

  QObject::connect(help_item->getAction(), SIGNAL(triggered()), this, SLOT(help()));
}

void
CQIfsTest::
loadSlot()
{
  QString title  = "Load File";
  QString cwd    = QString(COSFile::getCurrentDir().c_str());
  QString filter = "IFS (*.ifs)";

  QStringList filenames = QFileDialog::getOpenFileNames(this, title, cwd, filter);

  if (filenames.size() == 0)
    return;

  QStringListIterator fi(filenames);

  while (fi.hasNext()) {
    QString filename = fi.next();

    ifs_->read(filename.toLatin1().constData());
  }
}

void
CQIfsTest::
incSlot()
{
  ifs_->increaseDepth();
}

void
CQIfsTest::
decSlot()
{
  ifs_->decreaseDepth();
}

void
CQIfsTest::
quitSlot()
{
  exit(0);
}

void
CQIfsTest::
help()
{
}

//------

CQIfs::
CQIfs(QWidget *parent) :
 QWidget(parent)
{
  turtle_ = new CQTurtle;

  ifs_ = new CIfs(turtle_);
}

void
CQIfs::
read(const char *filename)
{
  ifs_->readFile(filename);
}

void
CQIfs::
increaseDepth()
{
  ifs_->increaseDepth();

  update();
}

void
CQIfs::
decreaseDepth()
{
  ifs_->decreaseDepth();

  update();
}

void
CQIfs::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.setRenderHints(QPainter::Antialiasing);

  turtle_->setPainter(&painter);

  range_.setEqualScale(true);

  range_.setPixelRange(0, 0, width() - 1, height() - 1);

  range_.setWindowRange(0, 0, 100.0, 100.0);

  QTransform t = CQUtil::toQTransform(range_.getMatrix());

  painter.setWorldTransform(t);

  ifs_->redraw();

  turtle_->setPainter(NULL);
}
