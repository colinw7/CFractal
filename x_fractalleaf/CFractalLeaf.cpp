#include <CFractalLeaf.h>
#include <CMathRand.h>

CFractalLeaf::
CFractalLeaf()
{
}

void
CFractalLeaf::
draw(int w, int h)
{
  //double min_x =  1E50;
  //double min_y =  1E50;
  //double max_x = -1E50;
  //double max_y = -1E50;

  double xmin, ymin, xmax, ymax;
  uint   nd;
  double *a, *b, *c, *d, *e, *f;
  uint   *p;

  // sierpinski triangle
  if      (type_ == SIERPINSKI) {
    xmin = 0;
    ymin = 0;
    xmax = 2;
    ymax = 1;
    nd   = 3;

    static double a1[3] = { 0.50, 0.50, 0.50};
    static double b1[3] = { 0.00, 0.00, 0.00};
    static double c1[3] = { 0.00, 0.00, 0.00};
    static double d1[3] = { 0.50, 0.50, 0.50};
    static double e1[3] = { 0.00, 1.00, 0.50};
    static double f1[3] = { 0.00, 0.00, 0.50};
    static uint   p1[3] = {   33,   66,  100};

    a = a1; b = b1; c = c1; d = d1; e = e1; f = f1; p = p1;
  }
  // fern leaf
  else if (type_ == FERN) {
    xmin = -2.1816700;
    ymin =  0.0746271;
    xmax =  2.6556800;
    ymax =  9.9981800;
    nd   = 4;

    static double a1[4] = { 0.00,  0.20, -0.15,  0.85};
    static double b1[4] = { 0.00, -0.26,  0.28,  0.04};
    static double c1[4] = { 0.00,  0.23,  0.26, -0.04};
    static double d1[4] = { 0.16,  0.22,  0.24,  0.85};
    static double e1[4] = { 0.00,  0.00,  0.00,  0.00};
    static double f1[4] = { 0.00,  1.60,  0.44,  1.60};
    static uint   p1[4] = {    1,     8,    15,   100};

    a = a1; b = b1; c = c1; d = d1; e = e1; f = f1; p = p1;
  }
  // tree
  else if (type_ == TREE) {
    xmin = -0.25;
    ymin =  0.00;
    xmax =  0.25;
    ymax =  0.50;
    nd   = 4;

    static double a1[4] = { 0.00,  0.10,  0.42,  0.42};
    static double b1[4] = { 0.00,  0.00, -0.42,  0.42};
    static double c1[4] = { 0.00,  0.00,  0.42, -0.42};
    static double d1[4] = { 0.50,  0.10,  0.42,  0.42};
    static double e1[4] = { 0.00,  0.00,  0.00,  0.00};
    static double f1[4] = { 0.00,  0.20,  0.20,  0.20};
    static uint   p1[4] = {    5,    20,    60,   100};

    a = a1; b = b1; c = c1; d = d1; e = e1; f = f1; p = p1;
  }
  // cantor tree
  else if (type_ == CANTOR) {
    xmin = 0;
    ymin = 0;
    xmax = 2;
    ymax = 2;
    nd   = 3;

    static double a1[3] = { 0.333, 0.333, 0.667};
    static double b1[3] = { 0.000, 0.000, 0.000};
    static double c1[3] = { 0.000, 0.000, 0.000};
    static double d1[3] = { 0.333, 0.333, 0.667};
    static double e1[3] = { 0.000, 1.000, 0.500};
    static double f1[3] = { 0.000, 0.000, 0.500};
    static uint   p1[3] = {    33,    66,   100};

    a = a1; b = b1; c = c1; d = d1; e = e1; f = f1; p = p1;
  }
  // circle
  else if (type_ == CIRCLE) {
    xmin = 0;
    ymin = 0;
    xmax = 1;
    ymax = 1;
    nd   = 5;

    static double a1[5] = {  0.15596, 0.04428, 0.05566, 0.11540, 0.27142};
    static double b1[5] = {  0.98776, 0.00000, 0.00000, 0.00000, 0.00000};
    static double c1[5] = { -0.98776, 0.00000, 0.00000, 0.00000, 0.00000};
    static double d1[5] = {  0.15596, 0.04116, 0.04527, 0.05094, 0.04932};
    static double e1[5] = { -0.07790, 0.06410, 0.09980, 0.14280, 0.23800};
    static double f1[5] = {  0.91240, 0.48290, 0.47790, 0.47610, 0.47810};
    static uint   p1[5] = {       96,      97,      98,      99,     100};

    a = a1; b = b1; c = c1; d = d1; e = e1; f = f1; p = p1;
  }
  // maple leaf
  else if (type_ == MAPLE) {
    xmin = 0;
    ymin = 0;
    xmax = 1;
    ymax = 1;
    nd   = 5;

    static double a1[5] = {  0.35173,  0.35338, 0.50000,  0.50154, 0.00364};
    static double b1[5] = {  0.35537, -0.35370, 0.00000, -0.00180, 0.00000};
    static double c1[5] = { -0.35537,  0.35373, 0.00000,  0.00157, 0.00000};
    static double d1[5] = {  0.35173,  0.35338, 0.50000,  0.58795, 0.57832};
    static double e1[5] = {  0.35340,  0.28790, 0.25000,  0.25010, 0.50160};
    static double f1[5] = {  0.50000,  0.15280, 0.46200,  0.10540, 0.06060};
    static uint   p1[5] = {       18,       56,      74,       94,     100};

    a = a1; b = b1; c = c1; d = d1; e = e1; f = f1; p = p1;
  }
  else
    return;

  //------

  double x = 0;
  double y = 0;

  uint num_iterations = 400000;

  for (uint i = 0; i < num_iterations; ++i) {
    uint percent = CMathRand::randInRange(0, 99);

    double x1, y1;

    CRGBA rgba;

    rgba = CRGBA(0,0,0);

    for (uint j = 0; j < nd; ++j) {
      if (percent < p[j]) {
        x1 = a[j]*x + b[j]*y + e[j];
        y1 = c[j]*x + d[j]*y + f[j];
        break;
      }
    }

#if 0
    if      (percent < 1) {
      x1   = 0;
      y1   = 0.16*y;
      rgba = CRGBA(0,1,0);
    }
    else if (percent < 8) {
      x1   = 0.20*x - 0.26*y;
      y1   = 0.23*x + 0.22*y + 1.6;
      rgba = CRGBA(1,0,0);
    }
    else if (percent < 15) {
      x1   = -0.15*x + 0.28*y;
      y1   =  0.26*x + 0.24*y + 0.44;
      rgba = CRGBA(0,0,0.5);
    }
    else {
      x1   =  0.85*x + 0.04*y;
      y1   = -0.04*x + 0.85*y + 1.6;
      rgba = CRGBA(0,0,1);
    }
#endif

    x = x1;
    y = y1;

    setForeground(rgba);

    drawPoint(CIPoint2D((w - 1)*(x - xmin)/(xmax - xmin), (h - 1)*(y - ymax)/(ymin - ymax)));

    //min_x = min(x, min_x);
    //min_y = min(y, min_y);
    //max_x = max(x, max_x);
    //max_y = max(y, max_y);
  }

  //cerr << min_x << endl;
  //cerr << min_y << endl;
  //cerr << max_x << endl;
  //cerr << max_y << endl;
}
