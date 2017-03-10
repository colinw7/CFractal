#ifndef CPOINT_FRACTAL_RENDERER_H
#define CPOINT_FRACTAL_RENDERER_H

#include <CPointFractal.h>

class CPointFractalCalc;

class CPointFractalRenderer : public CPointFractal {
 public:
  CPointFractalRenderer(CPointFractalCalc *calc);

  virtual ~CPointFractalRenderer();

  bool getShowVector() const;

  void setShowVector(bool show_vector);

  void resetRange();

  void getRange(double *xmin, double *ymin, double *xmax, double *ymax) const {
    *xmin = xmin_;
    *ymin = ymin_;
    *xmax = xmax_;
    *ymax = ymax_;
  }

  void setRange(double xmin, double ymin, double xmax, double ymax) {
    xmin_ = xmin;
    ymin_ = ymin;
    xmax_ = xmax;
    ymax_ = ymax;
  }

  int getMaxIterations() const { return max_iterations_; }

  void setMaxIterations(int iterations) { max_iterations_ = iterations; }

  void conv (double px, double py, double *wx, double *wy);
  void iconv(double wx, double wy, double *px, double *py);

  void draw(int w, int h);

  void threadDraw(int w, int h);

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void drawPoint(int x, int y) = 0;

 private:
  CPointFractalCalc *calc_;
  int                max_iterations_;
  double             xmin_, ymin_, xmax_, ymax_;
};

#endif
