#ifndef CQCircles_H
#define CQCircles_H

#include <CCircles.h>
#include <QWidget>

class CQRenderer2D;

class CQCircles : public QWidget, public CCircles {
 public:
  CQCircles(int width, int height);

  void paintEvent(QPaintEvent *);

  void resizeEvent(QResizeEvent *);

  void setDataRange(double xmin, double ymin, double xmax, double ymax);

  void setForeground(const CRGBA &rgba);

  void drawCircle(double x, double y, double r);
  void fillCircle(double x, double y, double r);

 private:
  CQRenderer2D *renderer_;
};

#endif
