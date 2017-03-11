#ifndef CSCENERY_H
#define CSCENERY_H

#include <CRGBA.h>

class CScenery {
 private:
  enum { SIZE  = 8 };
  enum { COUNT = (1 << SIZE) };

  struct Color {
    double r;
    double g;
    double b;
  };

  static int   range_[SIZE];
  static Color colors_[];

  int   *cell_;
  CRGBA  rgba_[32];

 public:
  CScenery();

  virtual ~CScenery() { }

  void draw();
  void grow();
  void set(int, int, int);

  virtual void setForeground(const CRGBA &rgba) = 0;
  virtual void drawPoint(uint x, uint y) = 0;

 private:
  void setColors();
};

#endif
