#include <QMainWindow>

class CQBarnsley;

class CQBarnsleyTest : public QMainWindow {
  Q_OBJECT

 private:
  CQBarnsley *barnsley_;

 public:
  CQBarnsleyTest();

  virtual ~CQBarnsleyTest();

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

  void type1Slot();
  void type2Slot();
  void type3Slot();
  void type4Slot();

  void help();
};
