#ifndef CLORENZ_CALC_H
#define CLORENZ_CALC_H

class CLorenzCalc {
 private:
  static double xmin_, ymin_, zmin_;
  static double xmax_, ymax_, zmax_;

  int iteration_start_;
  int iteration_end_;

 public:
  static double getXMin() { return xmin_; }
  static double getYMin() { return ymin_; }
  static double getZMin() { return zmin_; }
  static double getXMax() { return xmax_; }
  static double getYMax() { return ymax_; }
  static double getZMax() { return zmax_; }

  CLorenzCalc();

  virtual ~CLorenzCalc() { }

  void setIterationStart(int iteration_start) {
    iteration_start_ = iteration_start;
  }

  int getIterationStart() {
    return iteration_start_;
  }

  void setIterationEnd(int iteration_end) {
    iteration_end_ = iteration_end;
  }

  int getIterationEnd() {
    return iteration_end_;
  }

  void draw();

  virtual void drawPoint(double x, double y, double z) = 0;
};

#endif
