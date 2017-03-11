#include <CGLApp.h>
#include <CGLWindow.h>
#include <CGLRenderer3D.h>
#include <CMathRand.h>

class CGLPlasmaCalc;

class CGLPlasmaWindow : public CGLWindow {
 private:
  CGLRenderer3D    *renderer_;
  std::vector<int>  data_;
  int               s_;

 public:
  CGLPlasmaWindow(int x, int y, uint w, uint h);

  void setup();

  bool resizeEvent();
  bool exposeEvent();

  bool buttonPressEvent  (const CMouseEvent &event);
  bool buttonMotionEvent (const CMouseEvent &event);
  bool buttonReleaseEvent(const CMouseEvent &event);

  bool keyPressEvent(const CKeyEvent &event);

  void createList();

  void draw();

  void render();

  void subdivide(int x1, int y1, int x2, int y2);

  void set_color(int x, int y, int &color, int d);

  int get_color(int x, int y);

  void draw_point(int x, int y, int color);
};

//---------

int
main(int argc, char **argv)
{
  CMathRand::seedRand(time(NULL));

  CGLAppInst->init(argc, argv);

  CGLPlasmaWindow *window = new CGLPlasmaWindow(0, 0, 400, 400);

  window->setup();

  CGLAppInst->mainLoop();

  return 0;
}

//---------

CGLPlasmaWindow::
CGLPlasmaWindow(int x, int y, uint w, uint h)
{
  init(x, y, w, h);
}

void
CGLPlasmaWindow::
setup()
{
  renderer_ = new CGLRenderer3D(this);

  addControl();

  enableDispAttr();
}

bool
CGLPlasmaWindow::
resizeEvent()
{
  return true;
}

bool
CGLPlasmaWindow::
exposeEvent()
{
  static bool has_list;

  renderer_->clear(CRGBA(0,0,0));

  renderer_->setForeground(CRGBA(1,1,1));

  if (! has_list) {
    createList();

    has_list = true;
  }

  glCallList(1);

  return true;
}

bool
CGLPlasmaWindow::
buttonPressEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLPlasmaWindow::
buttonMotionEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLPlasmaWindow::
buttonReleaseEvent(const CMouseEvent &)
{
  return true;
}

bool
CGLPlasmaWindow::
keyPressEvent(const CKeyEvent &)
{
  return true;
}

void
CGLPlasmaWindow::
createList()
{
  glNewList(1, GL_COMPILE);

  draw();

  glEndList();
}

void
CGLPlasmaWindow::
draw()
{
  s_ = 400;

  int s2 = s_*s_;

  data_.reserve(s2);

  for (int i = 0; i < s2; ++i)
    data_[i] = 0;

  int color1 = CMathRand::randInRange(0, 100);
  int color2 = CMathRand::randInRange(0, 100);
  int color3 = CMathRand::randInRange(0, 100);
  int color4 = CMathRand::randInRange(0, 100);

  int x1 = 0;
  int y1 = 0;
  int x2 = s_ - 1;
  int y2 = s_ - 1;

  draw_point(x1, y1, color1);
  draw_point(x2, y1, color2);
  draw_point(x2, y2, color3);
  draw_point(x1, y2, color4);

  subdivide(x1, y1, x2, y2);

  render();
}

void
CGLPlasmaWindow::
subdivide(int x1, int y1, int x2, int y2)
{
  int dx = x2 - x1;
  int dy = y2 - y1;

  if (dx < 2 && dy < 2) return;

  int x = (x1 + x2)/2;
  int y = (y1 + y2)/2;

  int color1 = get_color(x1, y1);
  int color2 = get_color(x2, y1);
  int color3 = get_color(x2, y2);
  int color4 = get_color(x1, y2);

  int color12 = (color1 + color2)/2;
  int color23 = (color2 + color3)/2;
  int color34 = (color3 + color4)/2;
  int color41 = (color4 + color1)/2;

  set_color(x , y1, color12, dx);
  set_color(x2, y , color23, dy);
  set_color(x , y2, color34, dx);
  set_color(x1, y , color41, dy);

  int color = (color1 + color2 + color3 + color4)/4;

  draw_point(x, y, color);

  subdivide(x1, y1, x , y );
  subdivide(x , y1, x2, y );
  subdivide(x , y , x2, y2);
  subdivide(x1, y , x , y2);
}

void
CGLPlasmaWindow::
set_color(int x, int y, int &color, int d)
{
  d = std::min(20, d);

  color += CMathRand::randInRange(-d, d);

  color = std::min(std::max(color, 0), 100);

  draw_point(x, y, color);
}

int
CGLPlasmaWindow::
get_color(int x, int y)
{
  return data_[s_*y + x];
}

void
CGLPlasmaWindow::
draw_point(int x, int y, int color)
{
  int ind = s_*y + x;

  if (data_[ind] == 0)
    data_[ind] = color;
}

void
CGLPlasmaWindow::
render()
{
  std::vector<CPoint3D> points;

  points.resize(3);

  for (int y = 0; y < s_ - 1; ++y) {
    for (int x = 0; x < s_ - 1; ++x) {
      //renderer_->setForeground(colors_.getColor(color));
      //renderer_->setForeground(CRGBA(1,color/100.0,1));
      int ind1 = s_*y + x;
      int ind2 = ind1 + 1;
      int ind3 = ind1 + s_ + 1;
      int ind4 = ind1 + s_;

      int color1 = data_[ind1];
      int color2 = data_[ind2];
      int color3 = data_[ind3];
      int color4 = data_[ind4];

      CRGBA rgba;

      if (color1 < 10 || color2 < 10 || color3 < 10 || color4 < 10) {
        color1 = 10;
        color2 = 10;
        color3 = 10;
        color4 = 10;

        rgba = CRGBA(0,0,1);
      }
      else if (color1 > 200 || color2 > 200 || color3 > 200 || color4 > 200) {
        double g = std::max(std::max(std::max(color1, color2), color3), color4)/100.0;

        rgba = CRGBA(g, g, g);
      }
      else {
        rgba = CRGBA(0,color1/100.0,0);
      }

      int color = (color1 + color2 + color3 + color4)/4;

      double x1 = x - 200;
      double y1 = y - 200;
      double x2 = x1 + 1;
      double y2 = y1 + 1;
      double xm = x1 + 0.5;
      double ym = y1 + 0.5;

      renderer_->setForeground(rgba);

      points[0] = CPoint3D(x1, y1, color1);
      points[1] = CPoint3D(x2, y1, color2);
      points[2] = CPoint3D(xm, ym, color );

      renderer_->fillPolygon(points);

      points[0] = CPoint3D(x2, y1, color2);
      points[1] = CPoint3D(x2, y2, color3);
      points[2] = CPoint3D(xm, ym, color );

      renderer_->fillPolygon(points);

      points[0] = CPoint3D(x2, y2, color3);
      points[1] = CPoint3D(x1, y2, color4);
      points[2] = CPoint3D(xm, ym, color );

      renderer_->fillPolygon(points);

      points[0] = CPoint3D(x1, y2, color4);
      points[1] = CPoint3D(x1, y1, color1);
      points[2] = CPoint3D(xm, ym, color );

      renderer_->fillPolygon(points);
    }
  }
}
