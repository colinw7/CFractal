#include <QMainWindow>
#include <CDisplayRange2D.h>

class CQIfs;

class CQIfsTest : public QMainWindow {
  Q_OBJECT

 private:
  CQIfs *ifs_;

 public:
  CQIfsTest();

 private slots:
  void loadSlot();
  void incSlot();
  void decSlot();
  void quitSlot();
  void help();
};

class CIfs;
class CQTurtle;

class CQIfs : public QWidget {
 public:
  CQIfs(QWidget *parent=NULL);

  void read(const char *filename);

  void increaseDepth();
  void decreaseDepth();

  void paintEvent(QPaintEvent *);

 private:
  CIfs            *ifs_;
  CQTurtle        *turtle_;
  CDisplayRange2D  range_;
};
