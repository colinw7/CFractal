#include <CRGBA.h>

class CLunar {
 public:
  CLunar();

  virtual ~CLunar() { }

  void draw(int w, int h);

  virtual void clear(const CRGBA &rgba) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void fillTriangle(const CIPoint2D &p1, const CIPoint2D &p2, const CIPoint2D &p3) = 0;

  virtual void fillEllipse(const CIPoint2D &c, int xr, int yr) = 0;

  virtual void drawPoint(const CIPoint2D &p) = 0;

 private:
  void ranFillOval(int x, int y, int b, int color, float aspect);

  void fillOval(int x, int y, int b, int color, float aspect);

  void generate(int xl, int y1, int x2, int y2, int x3, int y3,
                int level, int color1, int color2);

  void gen_quad(int xl, int y1, int x2, int y2, int x3,int y3,
                int x4, int v4, int level, int color1, int color2);

  void midpoint();

  void node(int xl, int y1, int x2, int y2, int x3, int y3,
            int x4, int y4, int x5, int y5, int x6, int y6, int level,
            int color1, int color2);

  void plot_triangle(int xl, int y1, int x2, int y2, int x3,
                     int y3, int color1, int color2, int type);

  void plot(int x, int y, int color);

  void sort(int index, int x_coord[], int y_coord[]);

  float gauss();

  void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color);

  void set_color(int color);

 private:
  int    w_, h_;
  int    y_max;
  int    xz, yz, xp, yp, type;
  int    x_center, y_center, radius;
  double x,y;
};
