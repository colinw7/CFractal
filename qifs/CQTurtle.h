#ifndef CQTURTLE_H
#define CQTURTLE_H

#include <CTurtle.h>

class QPainter;

class CQTurtle : public CTurtle {
 private:
  QPainter *painter_;

 public:
  CQTurtle(QPainter *painter=nullptr);
 ~CQTurtle();

  void setPainter(QPainter *painter);

  void drawLine(double x1, double y1, double x2, double y2);

 private:
  CQTurtle(const CQTurtle &turtle);
  CQTurtle &operator=(const CQTurtle &turtle);
};

#endif
