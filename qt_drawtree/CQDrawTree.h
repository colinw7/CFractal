#ifndef CQDrawTree_H
#define CQDrawTree_H

#include <CDrawTree.h>
#include <QWidget>

class CQRenderer2D;

class CQDrawTree : public QWidget, public CDrawTree {
 public:
  CQDrawTree(int width, int height);

  void paintEvent(QPaintEvent *);

  void resizeEvent(QResizeEvent *);

  void setDataRange(double xmin, double ymin, double xmax, double ymax);

  void setForeground(const CRGBA &rgba);

  void drawLine(double x1, double y1, double x2, double y2);

  void setLineWidth(double w);

 private:
  CQRenderer2D *renderer_ { nullptr };
};

#endif
