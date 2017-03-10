#include <CQPointFractalTest.h>
#include <CQPointFractal.h>

#include <CMandelbrot.h>
#include <CJulia.h>
#include <CDragon.h>
#include <CPhoenix.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <CQToolBar.h>

#include <QTabWidget>
#include <QLabel>
#include <QStatusBar>
#include <QFileDialog>

CQPointFractalTest::
CQPointFractalTest() :
 CQMainWindow("CQPointFractalTest")
{
  init();
}

void
CQPointFractalTest::
createWorkspace()
{
  workspace_ = new CQMdiArea<CQPointFractal>(this, "workspace");
}

void
CQPointFractalTest::
createMenus()
{
  fileMenu = new CQMenu(this, "&File");

  mandelbrotItem = new CQMenuItem(fileMenu, "&New Mandelbrot");

  mandelbrotItem->setShortcut("Ctrl+M");
  mandelbrotItem->setStatusTip("Add a new Mandelbrot");

  connect(mandelbrotItem->getAction(), SIGNAL(triggered()),
          this, SLOT(newMandelbrot()));

  juliaItem = new CQMenuItem(fileMenu, "&New Julia");

  juliaItem->setShortcut("Ctrl+M");
  juliaItem->setStatusTip("Add a new Julia");

  connect(juliaItem->getAction(), SIGNAL(triggered()),
          this, SLOT(newJulia()));

  dragonItem = new CQMenuItem(fileMenu, "&New Dragon");

  dragonItem->setShortcut("Ctrl+M");
  dragonItem->setStatusTip("Add a new Dragon");

  connect(dragonItem->getAction(), SIGNAL(triggered()),
          this, SLOT(newDragon()));

  phoenixItem = new CQMenuItem(fileMenu, "&New Phoenix");

  phoenixItem->setShortcut("Ctrl+M");
  phoenixItem->setStatusTip("Add a new Phoenix");

  connect(phoenixItem->getAction(), SIGNAL(triggered()),
          this, SLOT(newPhoenix()));

  fileMenu->addSeparator();

  quitItem = new CQMenuItem(fileMenu, "&Quit");

  quitItem->setShortcut("Ctrl+Q");
  quitItem->setStatusTip("Quit the application");

  connect(quitItem->getAction(), SIGNAL(triggered()),
          this, SLOT(close()));

  //--------

  iterMenu = new CQMenu(this, "&Iterations");

  iterMenu->startGroup();

  CQMenuItem *iter1_item =
    new CQMenuItem(iterMenu,    "8", CQMenuItem::CHECKABLE);
  CQMenuItem *iter2_item =
    new CQMenuItem(iterMenu,   "16", CQMenuItem::CHECKABLE);
  CQMenuItem *iter3_item =
    new CQMenuItem(iterMenu,   "32", CQMenuItem::CHECKABLE);
  CQMenuItem *iter4_item =
    new CQMenuItem(iterMenu,   "64", CQMenuItem::CHECKABLE);
  CQMenuItem *iter5_item =
    new CQMenuItem(iterMenu,  "128", CQMenuItem::CHECKABLE);
  CQMenuItem *iter6_item =
    new CQMenuItem(iterMenu,  "256", CQMenuItem::CHECKED  );
  CQMenuItem *iter7_item =
    new CQMenuItem(iterMenu,  "512", CQMenuItem::CHECKABLE);
  CQMenuItem *iter8_item =
    new CQMenuItem(iterMenu, "1024", CQMenuItem::CHECKABLE);

  iterMenu->endGroup();

  QObject::connect(iter1_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations8()));
  QObject::connect(iter2_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations16()));
  QObject::connect(iter3_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations32()));
  QObject::connect(iter4_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations64()));
  QObject::connect(iter5_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations128()));
  QObject::connect(iter6_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations256()));
  QObject::connect(iter7_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations512()));
  QObject::connect(iter8_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(setIterations1024()));

  //--------

  displayMenu = new CQMenu(this, "&Display");

  CQMenuItem *reset_item = new CQMenuItem(displayMenu, "&Reset");

  QObject::connect(reset_item->getAction(),
                   SIGNAL(triggered()), this, SLOT(resetRange()));

  CQMenuItem *show_vector_item =
    new CQMenuItem(displayMenu, "Show &Vector", CQMenuItem::CHECKABLE);

  QObject::connect(show_vector_item->getAction(), SIGNAL(triggered()),
                   this, SLOT(toggleShowVector()));

  //--------

  new CQMenu(this, "|");

  //--------

  helpMenu = new CQMenu(this, "&Help");

  CQMenuItem *helpItem = new CQMenuItem(helpMenu, "&Help");

  QObject::connect(helpItem->getAction(), SIGNAL(triggered()),
                   this, SLOT(help()));
}

void
CQPointFractalTest::
createToolBars()
{
}

void
CQPointFractalTest::
createStatusBar()
{
  statusLabel = new QLabel(" ");

  statusLabel->setAlignment(Qt::AlignHCenter);
  statusLabel->setMinimumSize(statusLabel->sizeHint());

  statusBar()->addWidget(statusLabel);
}

void
CQPointFractalTest::
createDockWindows()
{
}

void
CQPointFractalTest::
newMandelbrot()
{
  CQPointFractal *fractal = workspace_->addWindow("Mandelbrot");

  ((QWidget *) fractal)->parentWidget()->resize(200, 200);

  fractal->setFractal(new CMandelbrot);
}

void
CQPointFractalTest::
newJulia()
{
  CQPointFractal *fractal = workspace_->addWindow("Julia");

  ((QWidget *) fractal)->parentWidget()->resize(200, 200);

  fractal->setFractal(new CJulia);
}

void
CQPointFractalTest::
newDragon()
{
  CQPointFractal *fractal = workspace_->addWindow("Dragon");

  ((QWidget *) fractal)->parentWidget()->resize(200, 200);

  fractal->setFractal(new CDragon);
}

void
CQPointFractalTest::
newPhoenix()
{
  CQPointFractal *fractal = workspace_->addWindow("Phoenix");

  ((QWidget *) fractal)->parentWidget()->resize(200, 200);

  fractal->setFractal(new CPhoenix);
}

void
CQPointFractalTest::
resetRange()
{
  CQPointFractal *fractal = workspace_->activeWindow();

  if (fractal != NULL)
    fractal->resetRange();
}

void
CQPointFractalTest::
quit()
{
  exit(0);
}

void
CQPointFractalTest::
setIterations8()
{
  setIterations(8);
}

void
CQPointFractalTest::
setIterations16()
{
  setIterations(16);
}

void
CQPointFractalTest::
setIterations32()
{
  setIterations(32);
}

void
CQPointFractalTest::
setIterations64()
{
  setIterations(64);
}

void
CQPointFractalTest::
setIterations128()
{
  setIterations(128);
}

void
CQPointFractalTest::
setIterations256()
{
  setIterations(256);
}

void
CQPointFractalTest::
setIterations512()
{
  setIterations(512);
}

void
CQPointFractalTest::
setIterations1024()
{
  setIterations(1024);
}

void
CQPointFractalTest::
setIterations(int num)
{
  CQPointFractal *fractal = workspace_->activeWindow();

  if (fractal != NULL)
    fractal->setIterations(num);
}

void
CQPointFractalTest::
toggleShowVector()
{
  CQPointFractal *fractal = workspace_->activeWindow();

  if (fractal != NULL)
    fractal->toggleShowVector();
}

void
CQPointFractalTest::
help()
{
}
