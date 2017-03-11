#include <CPikePeak.h>
#include <CMathRand.h>
#include <CRGBName.h>

CPikePeak::
CPikePeak()
{
  y_max = 180;
}

void
CPikePeak::
draw(int w, int h)
{
  w_ = w;
  h_ = h;

  clear(CRGBA(0,0.4,0.8));

  int x1[12] = {-220,-780,-480,-100,-770,-550,-220,-200};
  int y1[12] = {-240,-200,0,-260,-300,-280,-280,-280};
  int x2[12] = {120,40,-240,240,-250,-60,80,230};
  int y2[12] = {100,130,60,40,-110,-140,-130,-120};
  int x3[12] = {500,420,0,500,600,400,340,580};
  int y3[12] = {-40,-120,-60,-180,-300,-300,-300,-300};

  int level[12] = {6,6,5,5,5,5,4,4,4,4};

  for (int i = 0; i < 4; ++i) {
    if (i == 1)
      y_max = 160;
    else
      y_max = 180;

    generate(x1[i], y1[i], x2[i], y2[i], x3[i], y3[i], level[i], i + 3, i + 7);
  }

  set_color(1);

  fill_triangle(-320,-200,-320,-110, 319,-110);

  set_color(1);

  fill_triangle( 319,-110, 319,-200,-320,-200);

  y_max = -100;

  for (int i = 4; i < 8; ++i)
    generate(x1[i], y1[i], x2[i], y2[i], x3[i], y3[i], level[i], 11, 12);
}

void
CPikePeak::
midpoint()
{
  //ulong seed_gen = 350*(y + 240) + x + 320;
  //uint  seed     = seed_gen % 32760 + 2;

  //CMathGen::seedRand(seed);

  double r = 0.5 + random_no(0, 0.16666);
  double w = random_no(0.015, 0.035);

  xz = r*x - (w + 0.05)*y;
  yz = r*y + (w + 0.05)*x;
}

void
CPikePeak::
generate(int x1, int y1, int x2, int y2, int x3, int y3,
         int level, int color1, int color2)
{
  int x4,x5,x6,y4,y5,y6;

  x = x2 - x1;
  y = y2 - y1;

  midpoint(/*x,y*/);

  x4 = x1 + xz;
  y4 = y1 + yz;

  x = x1 - x3;
  y = y1 - y3;

  midpoint(/*x,y*/);

  x6 = x3 + xz;
  y6 = y3 + yz;

  x = x3 - x2;
  y = y3 - y2;

  midpoint(/*x,y*/);

  x5 = x2 + xz;
  y5 = y2 + yz;

  if (level == 0) {
    plot_triangle(x1, y1, x6, y6, x4, y4, color1, color2);
    plot_triangle(x2, y2, x4, y4, x5, y5, color1, color2);
    plot_triangle(x3, y3, x5, y5, x6, y6, color1, color2);
    plot_triangle(x4, y4, x5, y5, x6, y6, color1, color2);
  }
  else
    node(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, level, color1, color2);
}

double
CPikePeak::
random_no(double limit_start, double limit_end)
{
  limit_end -= limit_start;

  double result = CMathRand::randInRange(-limit_end, limit_end);

  if (result >= 0)
    result += limit_start;
  else
    result -= limit_start;

  return result;
}

void
CPikePeak::
node(int x1, int y1, int x2, int y2, int x3, int y3,
     int x4, int y4, int x5, int y5, int x6, int y6, int level,
     int color1, int color2)
{
  if (level == 0)
    return;

  generate(x1, y1, x6, y6, x4, y4, level - 1, color1, color2);
  generate(x2, y2, x4, y4, x5, y5, level - 1, color1, color2);
  generate(x3, y3, x5, y5, x6, y6, level - 1, color1, color2);
  generate(x4, y4, x5, y5, x6, y6, level - 1, color1, color2);
}

void
CPikePeak::
plot_triangle(int x1, int y1, int x2, int y2, int x3, int y3,
              int color1, int color2)
{
  int ytt = std::max(std::max(y1, y2), y3);

  double ym1 = y_max + 240.0;
  double yt1 = ytt   + 240.0;

  int color;

  if      (yt1 < 0.25*ym1)
    color = color1;
  else if (yt1 > 0.98*ym1)
    color = color2;
  else {
    double zt = ym1*(1.0 - (yt1*yt1)/(ym1*ym1));

    if (CMathRand::randInRange(0.0, ym1) <= zt)
      color = color1;
    else
      color = color2;
  }

  set_color(color);

  fill_triangle(x1, y1, x2, y2, x3, y3);
}

void
CPikePeak::
fill_triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
  fillTriangle(CIPoint2D(x1 + w_/2, h_/2 - 1 - y1),
               CIPoint2D(x2 + w_/2, h_/2 - 1 - y2),
               CIPoint2D(x3 + w_/2, h_/2 - 1 - y3));
}

void
CPikePeak::
set_color(int color)
{
  static CRGBA
  colors[65] = {
    CRGBName::toRGBA("#000000"), // 0
    CRGBName::toRGBA("#0000AA"), // 1
    CRGBName::toRGBA("#00AA00"), // 2
    CRGBName::toRGBA("#00AAAA"), // 3
    CRGBName::toRGBA("#AA0000"), // 4
    CRGBName::toRGBA("#AA00AA"), // 5
    CRGBName::toRGBA("#AAAA00"),
    CRGBName::toRGBA("#AAAAAA"), // 7

    CRGBName::toRGBA("#000055"),
    CRGBName::toRGBA("#0000FF"),
    CRGBName::toRGBA("#00AA55"),
    CRGBName::toRGBA("#00AAFF"),
    CRGBName::toRGBA("#AA0055"),
    CRGBName::toRGBA("#AA00FF"),
    CRGBName::toRGBA("#AAAA55"),
    CRGBName::toRGBA("#AAAAFF"),

    CRGBName::toRGBA("#005500"),
    CRGBName::toRGBA("#0055AA"),
    CRGBName::toRGBA("#00FF00"),
    CRGBName::toRGBA("#00FFAA"),
    CRGBName::toRGBA("#AA5500"), // 6
    CRGBName::toRGBA("#AA55AA"),
    CRGBName::toRGBA("#AAFF00"),
    CRGBName::toRGBA("#AAFFAA"),

    CRGBName::toRGBA("#005555"),
    CRGBName::toRGBA("#0055FF"),
    CRGBName::toRGBA("#00FF55"),
    CRGBName::toRGBA("#00FFFF"),
    CRGBName::toRGBA("#AA5555"),
    CRGBName::toRGBA("#AA55FF"),
    CRGBName::toRGBA("#AAFF55"),
    CRGBName::toRGBA("#AAFFFF"),

    CRGBName::toRGBA("#550000"),
    CRGBName::toRGBA("#5500AA"),
    CRGBName::toRGBA("#55AA00"),
    CRGBName::toRGBA("#55AAAA"),
    CRGBName::toRGBA("#FF0000"),
    CRGBName::toRGBA("#FF00AA"),
    CRGBName::toRGBA("#FFAA00"),
    CRGBName::toRGBA("#FFAAAA"),

    CRGBName::toRGBA("#550055"),
    CRGBName::toRGBA("#5500FF"),
    CRGBName::toRGBA("#55AA55"),
    CRGBName::toRGBA("#55AAFF"),
    CRGBName::toRGBA("#FF0055"),
    CRGBName::toRGBA("#FF00FF"),
    CRGBName::toRGBA("#FFAA55"),
    CRGBName::toRGBA("#FFAAFF"),

    CRGBName::toRGBA("#555500"),
    CRGBName::toRGBA("#5555AA"),
    CRGBName::toRGBA("#55FF00"),
    CRGBName::toRGBA("#55FFAA"),
    CRGBName::toRGBA("#FF5500"),
    CRGBName::toRGBA("#FF55AA"),
    CRGBName::toRGBA("#FFFF00"),
    CRGBName::toRGBA("#FFFFAA"),

    CRGBName::toRGBA("#555555"), // 8
    CRGBName::toRGBA("#5555FF"), // 9
    CRGBName::toRGBA("#55FF55"), // 10
    CRGBName::toRGBA("#55FFFF"), // 11
    CRGBName::toRGBA("#FF5555"), // 12
    CRGBName::toRGBA("#FF55FF"), // 13
    CRGBName::toRGBA("#FFFF55"), // 14
    CRGBName::toRGBA("#FFFFFF"), // 15
  };

  int color_map[16] = {0,1,2,11,10,10,34,31,47,58,18,2,6,27,62,63};

  setForeground(colors[color_map[color]]);
}
