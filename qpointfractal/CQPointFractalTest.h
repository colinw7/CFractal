#include <CQMainWindow.h>
#include <CQMdiArea.h>

class CQPointFractal;
class CQMenu;
class CQMenuItem;
class CQToolBar;
class QLabel;

class CQPointFractalTest : public CQMainWindow {
  Q_OBJECT

 private:
  CQMdiArea<CQPointFractal> *workspace_;

  // File Menu
  CQMenu *fileMenu;

  CQMenuItem *mandelbrotItem;
  CQMenuItem *juliaItem;
  CQMenuItem *dragonItem;
  CQMenuItem *phoenixItem;
  CQMenuItem *quitItem;

  // Iterations Menu
  CQMenu *iterMenu;

  // Display Menu
  CQMenu *displayMenu;

  // Help Menu
  CQMenu *helpMenu;

  QLabel *statusLabel;

 public:
  CQPointFractalTest();

 private:
  QSize sizeHint() const { return QSize(700,500); }

  void createWorkspace();

  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createDockWindows();

  void setIterations(int num);

 private slots:
  void newMandelbrot();
  void newJulia();
  void newDragon();
  void newPhoenix();

  void quit();

  void resetRange();

  void setIterations8();
  void setIterations16();
  void setIterations32();
  void setIterations64();
  void setIterations128();
  void setIterations256();
  void setIterations512();
  void setIterations1024();

  void toggleShowVector();

  void help();
};
