#ifndef CCIRCLES_H
#define CCIRCLES_H

#include <CRGBA.h>

class CCircles {
 private:
  struct NamedColor {
    const char *name;
    bool        set;
    CRGBA       rgba;

    NamedColor(const char *name1, bool set1=false,
               const CRGBA &rgba1=CRGBA(0,0,0)) :
     name(name1), set(set1), rgba(rgba1) {
    }
  };

  enum { MAX_COLORS = 16 };

  static NamedColor colors[];

  double canvas_xmin;
  double canvas_ymin;
  double canvas_xmax;
  double canvas_ymax;

  int canvas_color;
  int circles_depth;

 public:
  CCircles();

  virtual ~CCircles() { }

  void draw();

  virtual void setDataRange(double xmin, double ymin,
                            double xmax, double ymax) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void drawCircle(double x, double y, double r) = 0;
  virtual void fillCircle(double x, double y, double r) = 0;

 private:
  void generateCircle(double, double, double, double, double,
                      double, double, double, double, int);
};

#endif
