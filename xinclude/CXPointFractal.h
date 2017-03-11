#ifndef CX_POINT_FRACTAL_H
#define CX_POINT_FRACTAL_H

#include <CPointFractal.h>
#include <CXLib.h>
#include <CXLibPixelRenderer.h>

class CXPointFractalRenderer;

class CXPointFractal : public CXWindow {
 protected:
  CPointFractalCalc      *calc_;
  CXLibPixelRenderer     *renderer_;
  CXPointFractalRenderer *frenderer_;

  int canvas_width_;
  int canvas_height_;

  int    max_iterations_;
  double canvas_xmin_, canvas_ymin_;
  double canvas_xmax_, canvas_ymax_;

  bool zooming_;
  int  zoom_x1_, zoom_y1_;
  int  zoom_x2_, zoom_y2_;

  bool draw_;

 public:
  CXPointFractal(CPointFractalCalc *calc);
 ~CXPointFractal();

  void setRange(double xmin, double ymin, double xmax, double ymax) {
    canvas_xmin_ = xmin;
    canvas_ymin_ = ymin;
    canvas_xmax_ = xmax;
    canvas_ymax_ = ymax;
  }

  void resetRange();

  bool exposeEvent();

  bool resizeEvent();

  bool buttonPressEvent  (const CMouseEvent &event);
  bool buttonMotionEvent (const CMouseEvent &event);
  bool buttonReleaseEvent(const CMouseEvent &event);

  bool keyReleaseEvent(const CKeyEvent &event);

  void setForeground(const CRGBA &rgba);

  void drawPoint(int x, int y);
};

#endif
