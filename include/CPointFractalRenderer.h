#ifndef CPOINT_FRACTAL_RENDERER_H
#define CPOINT_FRACTAL_RENDERER_H

#include <CPointFractal.h>

class CPointFractalCalc;

class CPointFractalRenderer : public CPointFractal {
 public:
  CPointFractalRenderer(CPointFractalCalc *calc);

  virtual ~CPointFractalRenderer();

  void resetRange();

  void getRange(double *xmin, double *ymin, double *xmax, double *ymax) const {
    *xmin = xmin_; *ymin = ymin_;
    *xmax = xmax_; *ymax = ymax_;
  }

  void setRange(double xmin, double ymin, double xmax, double ymax) {
    xmin_ = xmin; ymin_ = ymin;
    xmax_ = xmax; ymax_ = ymax;
  }

  int getMaxIterations() const { return max_iterations_; }
  void setMaxIterations(int iterations) { max_iterations_ = iterations; }

  void draw(int w, int h);

  void threadDraw(int w, int h);

 private:
  CPointFractalCalc *calc_           { nullptr };
  int                max_iterations_ { 128 };
  double             xmin_           { 0.0 };
  double             ymin_           { 0.0 };
  double             xmax_           { 1.0 };
  double             ymax_           { 1.0 };
};

#endif
