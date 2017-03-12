#include <QMainWindow>

class CQNewton;

class CQNewtonTest : public QMainWindow {
  Q_OBJECT

 public:
  CQNewtonTest();

  virtual ~CQNewtonTest();

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

  void help();

 private:
  CQNewton *newton_ { nullptr };
  bool      animating_ { false };
  double    t_ { 0 };
};
