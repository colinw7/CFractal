#include <QWidget>
#include <QImage>
#include <QPointF>

#include "RGB.h"
#include "IPoint.h"
#include "Point.h"

class CQImage2D : public QWidget {
  Q_OBJECT

 public:
  CQImage2D();

 private:
  void paintEvent(QPaintEvent *);

  void keyPressEvent(QKeyEvent *e);

  void image2D();

 private slots:
  void tickSlot();

 private:
  QImage image_;
  double t_;
  double dt_;
  int    scale_;
  int    ind_;
  int    maxInd_;
};
