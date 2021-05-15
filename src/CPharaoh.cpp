#include <CPharaoh.h>
#include <CRGBName.h>
#include <cmath>

const char *
CPharaoh::colors[] = {
  "red",
  "green",
  "blue",
  "cyan",
  "magenta",
  "yellow",
  "orange",
  "brown",
  "grey50",
  "pink",
  "purple",
  "darkgreen",
  "lightblue",
  "seagreen",
  "lightsteelblue",
  "tan",
};

CPharaoh::
CPharaoh()
{
  canvas_xmin = -250.0;
  canvas_ymin = -250.0;
  canvas_xmax =  250.0;
  canvas_ymax =  250.0;

  invert_x  = 0.0;
  invert_y  = 0.0;
  invert_r  = 1.0;
  invert_rs = 1.0;
}

void
CPharaoh::
draw()
{
  setDataRange(canvas_xmin, canvas_ymin, canvas_xmax, canvas_ymax);

  double xa =   0.0;
  double ya =   0.0;
  double ra = 220.0;

  double xb =   0.0;
  double yb =  80.0;
  double rb = 140.0;

  invert_x  = 0.0;
  invert_y  = ra;
  invert_r  = 200*std::sqrt(10.0);
  invert_rs = invert_r*invert_r;

  setForeground(CRGBName::toRGBA("black"));

  fillCircle(xa, ya, ra);

  setForeground(CRGBName::toRGBA("red"));

  fillCircle(xb, yb, rb);

  double xo = 0.0;
  double yo = ra;

  double a_line = invert_rs/(2.0*ra);
  double b_line = invert_rs/(2.0*rb);

  double height = (b_line - a_line);
  double radius = height/2.0;
  double width  = radius*std::sqrt(2.0);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width,
                   yo - a_line - radius,
                   radius,
                   2);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width,
                   yo - a_line - 0.5*radius,
                   0.5*radius,
                   3);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width,
                   yo - b_line + 0.5*radius,
                   0.5*radius,
                   4);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.5*width,
                   yo - a_line - 0.75*radius,
                   0.25*radius,
                   5);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.5*width,
                   yo - b_line + 0.75*radius,
                   0.25*radius,
                   6);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.5*width,
                   yo - a_line - 0.125*radius,
                   0.125*radius,
                   7);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.5*width,
                   yo - b_line + 0.125*radius,
                   0.125*radius,
                   8);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.5*width,
                   yo - a_line - 5.0*radius/12.0,
                   radius/12.0,
                   9);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.5*width,
                   yo - b_line + 5.0*radius/12.0,
                   radius/12.0,
                   10);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.6*width,
                   yo - a_line - 0.3*radius,
                   0.1*radius,
                   11);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.6*width,
                   yo - b_line + 0.3*radius,
                   0.1*radius,
                   12);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.4*width,
                   yo - a_line - 0.3*radius,
                   0.1*radius,
                   13);

  for (uint i = 0; i < 20; i++)
    generateCircle(xo + i*width + 0.4*width,
                   yo - b_line + 0.3*radius,
                   0.1*radius,
                   14);
}

void
CPharaoh::
generateCircle(double x, double y, double r, int color)
{
  invertCircle( x, y, r, color);
  invertCircle(-x, y, r, color);
}

void
CPharaoh::
invertCircle(double x, double y, double r, int color)
{
  double d = std::sqrt((x - invert_x)*(x - invert_x) +
                       (y - invert_y)*(y - invert_y));

  double x1 = x + (invert_x - x)*r/d;
  double y1 = y + (invert_y - y)*r/d;
  double x2 = x - (invert_x - x)*r/d;
  double y2 = y - (invert_y - y)*r/d;

  invertPoint(&x1, &y1);
  invertPoint(&x2, &y2);

  double r1 = std::sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1))/2.0;

  setForeground(CRGBName::toRGBA(colors[color]));

  fillCircle((x1 + x2)/2.0, (y1 + y2)/2.0, r1);
}

void
CPharaoh::
invertPoint(double *x, double *y)
{
  double ds = (*x - invert_x)*(*x - invert_x) +
              (*y - invert_y)*(*y - invert_y);

  if (ds == 0.0)
    return;

  *x = invert_x + (*x - invert_x)*invert_rs/ds;
  *y = invert_y + (*y - invert_y)*invert_rs/ds;
}
