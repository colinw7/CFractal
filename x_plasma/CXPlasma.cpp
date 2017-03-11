#include <CXPlasma.h>
#include <CMathRand.h>

int
main(int, char **)
{
  CMathRand::seedRand(time(NULL));

  CXPlasma *plasma = new CXPlasma(600, 600);

  plasma->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXPlasma::
CXPlasma(int width, int height) :
 CXWindow(width, height)
{
  renderer_ = new CXLibPixelRenderer(this);
}

bool
CXPlasma::
exposeEvent()
{
  clear();

  draw();

  return true;
}

bool
CXPlasma::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

void
CXPlasma::
draw()
{
  s_ = std::min(getWidth(), getHeight());

  int s2 = s_*s_;

  data_.reserve(s2);

  for (int i = 0; i < s2; ++i)
    data_[i] = 0;

  int color1 = CMathRand::randInRange(1, 255);
  int color2 = CMathRand::randInRange(1, 255);
  int color3 = CMathRand::randInRange(1, 255);
  int color4 = CMathRand::randInRange(1, 255);

  int x1 = 0;
  int y1 = 0;
  int x2 = s_ - 1;
  int y2 = s_ - 1;

  draw_point(x1, y1, color1);
  draw_point(x2, y1, color2);
  draw_point(x2, y2, color3);
  draw_point(x1, y2, color4);

  subdivide(x1, y1, x2, y2);
}

void
CXPlasma::
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
CXPlasma::
set_color(int x, int y, int &color, int d)
{
  d = std::min(85, d);

  color += CMathRand::randInRange(-d, d);

  color = std::min(std::max(color, 1), 255);

  draw_point(x, y, color);
}

int
CXPlasma::
get_color(int x, int y)
{
  return data_[s_*y + x];
}

void
CXPlasma::
draw_point(int x, int y, int color)
{
  int ind = s_*y + x;

  if (data_[ind] == 0) {
    data_[ind] = color;

    renderer_->setForeground(colors_.getColor(color));

    renderer_->drawPoint(CIPoint2D(x, y));
  }
}
