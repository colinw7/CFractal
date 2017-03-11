#include <CRGBA.h>

class CPikePeak {
 public:
  CPikePeak();

  void draw(int w, int h);

  virtual void clear(const CRGBA &rgba) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3) = 0;

 private:
  void generate(int x1, int y1, int x2, int y2, int x3, int y3,
                int level, int color1, int color2);

  void midpoint();

  void node(int x1, int y1, int x2, int y2, int x3, int y3,
            int x4, int y4, int x5, int y5, int x6, int y6, int level,
            int color1, int color2);

  void plot_triangle(int x1, int y1, int x2, int y2, int x3,
                     int y3, int color1, int color2);

  double random_no(double limit_start, double limit_end);

  void fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3);

  void set_color(int color);

 private:
  int    w_, h_;
  int    y_max;
  double xz, yz, xp, yp;
  double x,y;
};
