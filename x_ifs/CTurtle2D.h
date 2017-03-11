#ifndef CTURTLE_2D_H
#define CTURTLE_2D_H

#include <CTurtle.h>

class CRenderer2D;

class CTurtle2D : public CTurtle {
 private:
  CRenderer2D *renderer_;

 public:
  CTurtle2D(CRenderer2D *renderer=NULL);
  CTurtle2D(const CTurtle2D &turtle);

 ~CTurtle2D();

  CTurtle2D &operator=(const CTurtle2D &turtle);

  CTurtle2D *dup() const;

  void drawLine(double x1, double y1, double x2, double y2);
};

#endif
