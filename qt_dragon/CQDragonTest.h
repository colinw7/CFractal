#include <QMainWindow>
#include <CQDragon.h>

class QTimer;

class CQDragonTest : public QMainWindow {
  Q_OBJECT

 public:
  CQDragonTest(CQDragon::Type type);

  virtual ~CQDragonTest();

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
  CQDragon *dragon_ { nullptr };
  QTimer   *timer_ { nullptr };
  double    t_ { 0 };
};
