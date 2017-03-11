#include <CXLib.h>
#include <CColorRange.h>
#include <CXLibPixelRenderer.h>

class CXPlasma : public CXWindow {
 public:
  CXPlasma(int width, int height);

  bool exposeEvent();

  bool resizeEvent();

  void draw();

  void subdivide(int x1, int y1, int x2, int y2);

  void set_color(int x, int y, int &color, int d);

  int get_color(int x, int y);

  void draw_point(int x, int y, int color);

 private:
  CXLibPixelRenderer *renderer_;
  CColorRange         colors_;
  std::vector<int>    data_;
  int                 s_;
};
