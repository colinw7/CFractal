#include <QMainWindow>

class QTimer;

class CQJulia;

class CQJuliaTest : public QMainWindow {
  Q_OBJECT

 public:
  CQJuliaTest();

  virtual ~CQJuliaTest();

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

  void toggleShowVector();

  void toggleAnimate();
  void animateSlot();

  void help();

 private:
  CQJulia *julia_ { nullptr };
  QTimer  *timer_ { nullptr };
  bool     animating_ { false };
  double   t_ { 0 };
};
