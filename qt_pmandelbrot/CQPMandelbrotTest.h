#include <QMainWindow>

class QTimer;

class CQPMandelbrot;

class CQPMandelbrotTest : public QMainWindow {
  Q_OBJECT

 public:
  CQPMandelbrotTest();

  virtual ~CQPMandelbrotTest();

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
  void animateSlot();

  void help();

 private:
  CQPMandelbrot *mandelbrot_;
  QTimer        *timer_;
  bool           animating_;
  double         t_;
};
