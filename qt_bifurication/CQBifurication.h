#include <QMainWindow>

class CQBifurication;

class CQBifuricationTest : public QMainWindow {
  Q_OBJECT

 private:
  CQBifurication *bifurication_;

 public:
  CQBifuricationTest();

 private slots:
  void quit();
  void setFeigenbaum(bool set);
  void help();
};

#include <CBifuricationLib.h>

class CQBifurication : public QWidget, public CBifurication {
 private:
  QPainter *painter_;

 public:
  CQBifurication(QWidget *parent=NULL);

  void paintEvent(QPaintEvent *);

  void drawPoint(int x, int y);
};
