#include <QWidget>
#include <QImage>
#include <QPointF>

#include <RGB.h>
#include <IPoint.h>
#include <Point.h>

struct State {
  int dx, dy;

  State() {
    dx = 0;
    dy = 0;
  }
};

class CQTexture : public QWidget {
  Q_OBJECT

 public:
  CQTexture();

 private:
  void paintEvent(QPaintEvent *);

  void mousePressEvent(QMouseEvent *);

  void keyPressEvent(QKeyEvent *);

  void texture1 (const State &s);
  void texture2 (const State &s);
  void texture3 (const State &s);
  void texture4 (const State &s);
  void texture5 (const State &s);
  void texture6 (const State &s);
  void texture7 (const State &s);
  void texture8 (const State &s);
  void texture9 (const State &s);
  void texture10(const State &s);
  void texture11(const State &s);

 private:
  int    n_;
  QImage image_;
  State  state_;
};
