#include <CSedona.h>
#include <CMathRand.h>

static CRGBA
colors[16] = {
  CRGBA(0.0,0.0,0.0),
  CRGBA(0.0,0.0,0.5),
  CRGBA(0.0,0.5,0.0),
  CRGBA(0.0,0.5,0.5),
  CRGBA(0.5,0.0,0.0),
  CRGBA(0.5,0.0,0.5),
  CRGBA(0.5,0.5,0.0),
  CRGBA(0.8,0.8,0.8),
  CRGBA(0.4,0.4,0.4),
  CRGBA(0.4,0.4,1.0),
  CRGBA(0.4,1.0,0.4),
  CRGBA(0.4,1.0,1.0),
  CRGBA(1.0,0.4,0.4),
  CRGBA(1.0,0.4,1.0),
  CRGBA(1.0,1.0,0.4),
  CRGBA(1.0,1.0,1.0),
};

CSedona::
CSedona()
{
  y_max = 280;
}

void
CSedona::
draw(int w, int h)
{
  w_ = w;
  h_ = h;

  clear(CRGBA(0,0.4,0.8));

  int x1[26] = {-330,-90,-90,120,120,120,-160,-120,-120,-80,
                -80,-50,-50,-50, 80,104,104,128,128,152,152,200,
                -470,-350,-220,-200};
  int y1[26] = {-110,-110,-110,-110,-110,-110, -10,-10,-10,-10,
                   -10,-10,-10,-10, 50,50,50,50,50,50,50,50,
                   -300,-280,-280,-280};
  int x2[26] = {-160,-160,0,0,80,200, -160,-160,-120,-120,-80,
                -80,-50,0, 100,100,104,104,128,128,152,152,
                -250,-60,80,230};
  int y2[26] = {0,0,0,0,50,50, 220,220,190,190,230,230,100,180,
                180,180,200,205,215,215,160,160, -110,-140,-130,-120};
  int x3[26] = {-90,0,120,80,200,340, -120,-120,-80,-80,-50,
                -50,0,0,104,104,128,128,152,152,200,200,
                300,300,340,580};
  int y3[26] = {-110,0,-110,50,50,-110, -10,220,-10,200,-10,
                235,180,-10, 50,200,50,210,50,220,50,140,
                -300,-300,-300,-300};
  int level[26] = {3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};

  for (int i = 0; i < 22; ++i)
    generate(x1[i], y1[i], x2[i], y2[i], x3[i], y3[i], level[i], 4, 12);

  y_max = -100;

  gen_quad(-330, -260, -330, -100, 330, -100, 330, -260, 4, 6, 14);

  y_max = 0;

  cactus(-110, -130, 3, 4, 2, 10);
  cactus(-200, -120, 2, 4, 2, 10);
  cactus(   0, -160, 4, 4, 2, 10);
  cactus( 210, -200, 6, 4, 2, 10);
}

void
CSedona::
node(int x1, int y1, int x2, int y2, int x3, int y3,
     int x4,int y4, int x5, int y5, int x6, int y6, int level,
     int color1, int color2)
{
  if (level == 0)
    return;

  generate(x1, y1, x4, y4, x6, y6, level - 1, color1, color2);
  generate(x6, y6, x5, y5, x3, y3, level - 1, color1, color2);
  generate(x4, y4, x2, y2, x5, y5, level - 1, color1, color2);
  generate(x4, y4, x5, y5, x6, y6, level - 1, color1, color2);
}

void
CSedona::
generate(int x1, int y1, int x2, int y2, int x3, int y3,
         int level, int color1, int color2)
{
  int x4,x5,x6,y4,y5,y6,ax,bx,cx,ay,by,cy;

  x = x2 - x1;
  y = y2 - y1;

  midpoint();

  x4 = x1 + xz - xp;
  y4 = y1 + yz - yp;
  ax = -xp;
  ay = -yp;
  x  = x3 - x1;
  y  = y3 - y1;

  midpoint();

  x6 = x1 + xz;
  y6 = y1 + yz;
  cx = xp;
  cy = yp;
  x  = x3 - x2;
  y  = y3 - y2;

  midpoint();

  x5 = x2 + xz;
  y5 = y2 + yz;

  bx = -xp;
  by = -yp;

  if (level == 0) {
    plot_triangle(x1, y1,x4,y4,x6,y6,color1,color2);
    plot_triangle(x6, y6,x5,y5,x3,y3,color1,color2);
    plot_triangle(x4, y4,x5,y5,x6,y6,color1,color2);
    plot_triangle(x4, y4,x2,y2,x5,y5,color1,color2);
  }
  else {
    plot_triangle(x1   , y1   , x4+ax, y4+ay, x6+cx ,y6+cy, color1, color2);
    plot_triangle(x6+cx, y6+cy, x5+bx, y5+by, x3    ,y3   , color1, color2);
    plot_triangle(x4+ax, y4+ay, x5+bx, y5+by, x6+cx ,y6+cy, color1, color2);
    plot_triangle(x4+ax, y4+ay, x2   , y2   , x5+bx, y5+by, color1, color2);

    node(x1, y1, x2, y2, x3, y3, x4, y4, x5, y5, x6, y6, level, color1, color2);
  }
}

void
CSedona::
plot_triangle(int x1, int y1, int x2, int y2, int x3,
              int y3, int color1, int color2)
{
  int ytt = std::max(std::max(y1, y2), y3);

  double ym1 = y_max + 240.0;
  double yt1 = ytt   + 240.0;

  int color;

  if      (yt1 < 0.35*ym1)
    color = color1;
  else if (yt1 > 0.92*ym1)
    color = color2;
  else {
    double zt = ym1*(1.0 - (yt1*yt1)/(ym1*ym1));

    if (CMathRand::randInRange(0.0, ym1) <= zt)
      color = color1;
    else
      color = color2;
  }

  CRGBA rgba = colors[color];

  setForeground(rgba);

  fillTriangle(CIPoint2D(x1 + w_/2, h_/2 - 1 - y1),
               CIPoint2D(x2 + w_/2, h_/2 - 1 - y2),
               CIPoint2D(x3 + w_/2, h_/2 - 1 - y3));
}

void
CSedona::
midpoint()
{
  double r = 0.5 + random_no(0.0, 0.16666);
  double w = random_no(0.03, 0.07);

  xz = r*x - w*y;
  yz = r*y + w*x;

  xp =  0.05*y;
  yp = -0.05*x;
}

double
CSedona::
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
CSedona::
gen_quad(int x1, int y1, int x2, int y2, int x3, int y3,
         int x4, int y4, int level, int color1, int color2)
{
  generate(x1, y1, x2, y2, x3, y3, level, color1, color2);
  generate(x1, y1, x4, y4, x3, y3, level, color1, color2);
}

void
CSedona::
cactus(int x1, int y1, int scale, int level, int color1, int color2)
{
  gen_quad(x1, y1, x1, y1 + 21*scale, x1 + 1.6*scale, y1 + 22*scale,
           x1 + 1.6*scale, y1, level, color1, color2);
  gen_quad(x1 + 1.4*scale, y1, x1 + 1.4*scale, y1 + 22*scale,
           x1 + 3*scale, y1 + 21*scale, x1 + 3*scale, y1, level, color1,
           color2);
  gen_quad(x1, y1 + 9*scale, x1 + 7*scale, y1 + 9*scale, x1 + 7*scale,
           y1 + 12*scale, x1, y1 + 12*scale, 0, color1, color2);
  gen_quad(x1, y1 + 9*scale, x1 + 6*scale, y1 + 9*scale, x1 + 7*scale,
           y1 + 12*scale, x1, y1 + 12*scale, level, color1, color2);
  gen_quad(x1 + 7*scale, y1 + 9*scale, x1 + 7*scale, y1 + 16*scale,
           x1 + 8.5*scale, y1 + 17*scale, x1 + 8.5*scale, y1 + 9*scale,
           level, color1, color2);
  gen_quad(x1 + 8.4*scale, y1 + 9*scale, x1 + 8.4*scale, y1 + 16*scale,
           x1 + 10*scale, y1 + 17*scale, x1 + 10*scale, y1 + 10*scale,
           level, color1, color2);
  gen_quad(x1, y1 + 7*scale, x1-6*scale, y1 + 7*scale, x1-6*scale,
           y1 + 10*scale, x1, y1 + 10*scale, 0, color1, color2);
  gen_quad(x1, y1 + 7*scale, x1-6*scale, y1 + 7*scale, x1-6*scale,
           y1 + 10*scale, x1, y1 + 10*scale, level, color1, color2);
  gen_quad(x1-7*scale, y1 + 8*scale, x1-7*scale, y1 + 12*scale,
           x1-5.4*scale, y1 + 13*scale, x1-5.4*scale, y1 + 7*scale,
           level, color1, color2);
  gen_quad(x1-5.6*scale, y1 + 7*scale, x1-5.6*scale, y1 + 13*scale,
           x1-4*scale, y1 + 12*scale, x1-4*scale, y1 + 7*scale, level,
           color1, color2);
}
