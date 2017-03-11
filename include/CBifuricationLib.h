#ifndef CBIFURICATION_LIB_H
#define CBIFURICATION_LIB_H

class CBifurication {
 private:
  int min_iterations_;
  int max_iterations_;

  bool feigenbaum_;

  double rmin_, rmax_;
  double ymin_, ymax_;
  bool   yset_;

 public:
  CBifurication();

  virtual ~CBifurication();

  void setFeigenbaum(bool feigenbaum);

  void setRRange(double rmin, double rmax);

  void draw(int width, int height);

  virtual void drawPoint(int x, int y) = 0;
};

#endif
