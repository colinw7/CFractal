#include <QMainWindow>

class QTimer;

class CQMandelbrot;

class CQMandelbrotTest : public QMainWindow {
  Q_OBJECT

 public:
  CQMandelbrotTest();

  virtual ~CQMandelbrotTest();

 private slots:
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
  void setIterations2048();

  void toggleShowVector();

  void toggleAnimate();
  void toggleThreaded();
  void animateSlot();

  void help();

 private:
  CQMandelbrot *mandelbrot_;
  QTimer       *timer_;
  bool          animating_;
  double        t_;
};
