#include <CLunar.h>
#include <CMathGen.h>
#include <CMathRand.h>
#include <CRGBA.h>
#include <CRGBName.h>

//uchar PALETTE[16]={0,1,2,3,4,5,20,7,56,57,58,59,60, 61,62,62};

CLunar::
CLunar()
{
  y_max = 280;

  radius = 150;

  x_center = -100;
  y_center = 0;
}

void
CLunar::
draw(int w, int h)
{
  w_ = w;
  h_ = h;

  clear(CRGBA(0,0.4,0.8));

  int level[26] = {3,3,3,3,3,3,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};
  int x1[27] = {-100,-200,200,12,-280,20, -470,-350,-220,-200};
  int y1[27] = {-30,-110,-110,140,-210,-210, -300,-280,-280,-280};
  int x2[27] = {-210,-160,-160,0,0,80, -250,-60,80,230};
  int y2[27] = {210,0,0,0,0,50, -110,-140,-130,-120,0};
  int x3[27] = {0,-90,0,120,80,200, 300,300,340,580};
  int y3[27] = {-80,-110,0,-110,50,50, -300,-300,-300,-300};
  int xa[35] = {-82,-80,-90,-70,-50,-30,-25,25,40,42,20,35,40,50,
                60,60,-28, 70,100,70,108,8l,60,45,48,96,45,38,-8,0,-20, -28};
  int xb[35] = {-70,-70,-80,-50,-30,25,-25,40,65,65,40,38,40,
                60,60,70,-28,100,127,129,92,70,56,48,54,100,38,46,12,14,
                14,8};
  int xc[35] = {-70,-70,-80,-50,-50,20,30,40,40,58,40,37,50,50,
                 70,75,20,100,129,120,83,70,45,60,60,54,106,65,12,40,14,-8};
  int xd[35] = {-90,-80,-90,-70,-30,20,20,25,50,50,20,40,50,60,
                 70,75,20,70,100,108,81,108,45,56,96,45,100,106,8,44,0,-30};
  int ya[35] = {52,52,76,80,76,38,10,80,90,55,50,3,60,60,52,55,
               80,115,120,109,76,80,-130,-124,-90,-70,-60,-50,0,-10,10,
               90};
  int yb[35] = {52,52,76,80,80,30,30,80,70,70,40,5,8,52,38,38,20,
                 120,116,104,58,95,-124,-90,-65,-60,-50,-25,0,-10,10,80};
  int yc[35] = {60,80,80,55,56,38,10,90,80,70,3,-5,60,20,38,40,
                 20,106,104,76,60,110,-124,-100,-100,-65,-50,-25,-18,-30,
                 18,75};
  int yd[35] = {60,80,77,55,38,30,30,90,60,60,3,-4,20,27,38,40,
                74,109,106,76,80,76,-124,-124,-70,-60,-60,-50,-18,-30,-18,
                85};

//setEGApalette(0,8);
//setEGApalette(1,57);
//setEGApalette(3,20);
//setEGApalette(6,60);

  for (int i = 0; i < 2000; i++) {
    int col = CMathRand::randInRange(-320,320);
    int row = CMathRand::randInRange(-240,240);

    plot(col, row, 15);
  }

  fillOval(-100,0,152,1,1.0);

  type = 1;

  int level1 = 4;

  for (int i = 0; i < 32; i++)
    gen_quad(xa[i] + x_center, ya[i] + y_center, xb[i] + x_center,
             yb[i] + y_center, xc[i] + x_center, yc[i] + y_center,
             xd[i] + x_center, yd[i] + y_center, level1, 2, 3);

  ranFillOval(-100, 0, 152, 0, 1.0);

  type = 0;

  y_max = -60;

  for (int i = 6; i < 10; i++)
    generate(x1[i],y1[i],x2[i],y2[i],x3[i],y3[i],level[i], 14,6);

  fillOval(-180,-200,10,6,.35);
  fillOval(   0,-160,10,6,.35);
  fillOval(  40,-220,16,6,.30);
  fillOval( 100,-170, 6,6,.35);
  fillOval( 200,-190,12,6,.35);
  fillOval(-220,-130, 8,6,.35);
  fillOval( 280,-150, 8,6,.35);
}

void
CLunar::
fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
  set_color(color);

  fillTriangle(CIPoint2D(x1 + w_/2, h_/2 - 1 - y1),
               CIPoint2D(x2 + w_/2, h_/2 - 1 - y2),
               CIPoint2D(x3 + w_/2, h_/2 - 1 - y3));

#if 0
  #define sign(x) ((x) > 0 ? 1 : ((x) == 0 ? 0 : (-1)))

  int dx, dy, dxabs, dyabs, index=0, j, k, sdx,
      sdy, x, y, xpoint[4], ypoint[4], toggle, old_sdy,sy0;

  int *x_coord = (int *) malloc(4000 * sizeof(int));
  int *y_coord = (int *) malloc(4000 * sizeof(int));

  xpoint[0] = x1 + 319;
  ypoint[0] = 175 - ((y1*93L) >> 7);
  xpoint[1] = x2 + 319;
  ypoint[1] = 175 - ((y2*93L) >> 7);
  xpoint[2] = x3 + 319;
  ypoint[2] = 175 - ((y3*93L) >> 7);
  xpoint[3] = xpoint[0];
  ypoint[3] = ypoint[0];

  int i = 3;

  int px = xpoint[0];
  int py = ypoint[0];

  if (ypoint[1] == ypoint[0]) {
    x_coord[index  ] = px;
    y_coord[index++] = py;
  }

  for (j = 0; j < i; j++) {
    dx = xpoint[j+1] - xpoint[j];
    dy = ypoint[j+1] - ypoint[j];

    sdx = sign(dx);
    sdy = sign(dy);

    if (j==0) {
      old_sdy = sdy;
      sy0 = sdy;
    }

    dxabs = abs(dx);
    dyabs = abs(dy);

    x = 0;
    y = 0;

    if (dxabs >= dyabs) {
      for (k=0; k<dxabs; k++) {
        y += dyabs;

        if (y>=dxabs) {
          y -= dxabs;
          py += sdy;

          if (old_sdy != sdy) {
            old_sdy = sdy;
            index--;
          }

          x_coord[index] = px+sdx;
          y_coord[index++] = py;
        }

        px += sdx;
      }
    }
    else {
      for (k=0; k<dyabs; k++) {
        x += dxabs;

        if (x>=dyabs) {
          x -= dyabs;
          px += sdx;
        }

        py += sdy;

        if (old_sdy != sdy) {
          old_sdy = sdy;

          if (sdy != 0)
            index--;
        }

        x_coord[index] = px;
        y_coord[index++] = py;
      }
    }
  }

  index--;

  if (sy0 + sdy== 0)
    index--;

  sort(index,x_coord,y_coord);

  toggle = 0;

  if (x_coord[0] < 0)
    x_coord[0] = 0;

  if (x_coord[0] > 639)
    x_coord[0] = 639;

  for (int i=0; i<index; i++) {
    if (x_coord[i+1] < 0)
      x_coord[i+1] = 0;

    if (x_coord[i+1] > 639)
      x_coord[i+1] = 639;

    if ((y_coord[i] == y_coord[i+1]) && (toggle == 0) &&
        (y_coord[i] >= 0) && (y_coord[i] < 350)) {
      for (j=x_coord[i]; j<=x_coord[i+1]; j++) {
        int xa = j - 319;
        int ya = (175 - y_coord[i])*128L/93;

        if (((xa - x_center)*(xa - x_center) + (ya-y_center)*(ya-y_center)) <
            (radius*radius) || (type == 0))
          plot(j, y_coord[i], color);
      }

      toggle = 1;
    }
    else
      toggle = 0;
  }

  free(x_coord);
  free(y_coord);
#endif
}

void
CLunar::
sort(int index, int x_coord[], int y_coord[])
{
  int d = 4;

  while (d<=index)
    d *= 2;

  d -= 1;

  while (d > 1) {
    d /= 2;

    for (int j=0; j <= (index - d); j++) {
      for (int i = j; i >= 0; i -= d) {
        if ((y_coord[i + d] < y_coord[i]) ||
            ((y_coord[i + d] == y_coord[i]) && (x_coord[i + d] <= x_coord[i]))) {
          std::swap(y_coord[i], y_coord[i+d]);
          std::swap(x_coord[i], x_coord[i+d]);
        }
      }
    }
  }
}

void
CLunar::
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
CLunar::
gen_quad(int x1, int y1, int x2, int y2, int x3, int y3,
         int x4, int y4, int level, int color1, int color2)
{
  generate(x1, y1, x2, y2, x3, y3, level, color1, color2);
  generate(x1, y1, x4, y4, x3, y3, level, color1, color2);
}

void
CLunar::
generate(int x1, int y1, int x2, int y2, int x3, int y3,
         int level, int color1, int color2)
{
  int x4, x5, x6, y4, y5, y6, ax, bx, cx, ay, by, cy;

  x = x2 - x1;
  y = y2 - y1;

  midpoint(/*x,y*/);

  x4 = x1 + xz - xp;
  y4 = y1 + yz - yp;

  ax = -xp;
  ay = -yp;

  x = x3 - x1;
  y = y3 - y1;

  midpoint(/*x,y*/);

  x6 = x1 + xz;
  y6 = y1 + yz;

  cx = xp;
  cy = yp;

  x = x3 - x2;
  y = y3 - y2;

  midpoint(/*x,y*/);

  x5 = x2 + xz;
  y5 = y2 + yz;

  bx = -xp;
  by = -yp;

  if (level == 0) {
    plot_triangle(x1, y1, x4, y4, x6, y6, color1, color2, 0);
    plot_triangle(x6, y6, x5, y5, x3, y3, color1, color2, 0);
    plot_triangle(x4, y4, x5, y5, x6, y6, color1, color2, 0);
    plot_triangle(x4, y4, x2, y2, x5, y5, color1, color2, 0);
  }
  else {
    plot_triangle(x1   ,y1   ,x4+ax,y4+ay,x6+cx,y6+cy,color1,color2,0);
    plot_triangle(x6+cx,y6+cy,x5+bx,y5+by,x3   ,y3   ,color1,color2,0);
    plot_triangle(x4+ax,y4+ay,x5+bx,y5+by,x6+cx,y6+cy,color1,color2,0);
    plot_triangle(x4+ax,y4+ay,x2   ,y2   ,x5+bx,y5+by,color1,color2,0);

    node(x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,level,color1,color2);
  }
}

void
CLunar::
plot_triangle(int x1, int y1, int x2, int y2, int x3,
              int y3,int color1, int color2, int type)
{
  int ytt = std::max(std::max(y1, y2), y3);

  double ym1 = y_max + 240.0;
  double yt1 = ytt   + 240.0;

  int color;

  if (type == 0) {
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
  }
  else {
    if (rand() <= 24000)
      color = color1;
    else
      color = color2;
  }

  fillTriangle(x1, y1, x2, y2, x3, y3, color);
}

void
CLunar::
midpoint()
{
  int sign1, sign2;

  if (rand() > 16383)
    sign1 = 1;
  else
    sign1 = -1;

  if (rand() > 16383)
    sign2 = 1;
  else
    sign2 = -1;

  double r = 0.5 + sign1*(float)rand()/196602.0;
  double w = ((float)(rand()/819175.0) + 0.03)*sign2;

  r = 0.5 + gauss()/6;
  w = gauss()/25 + .03;

  xz = r*x - w*y;
  yz = r*y + w*x;

  xp =  0.05*y;
  yp = -0.05*x;
}

float
CLunar::
gauss()
{
  int k = rand() - 16383;

  double value = k/5461.0;

  double exponent = -(value*value)/2.;

  double gauss1 = .15915494*exp(exponent);

  k = rand();

  if (k > 16383)
    gauss1 *= -1;

  return gauss1;
}

void
CLunar::
ranFillOval(int x, int y, int b, int color, float aspect)
{
  assert(x + y + b + color + aspect);
#if 0
  #define convert(x,y) {x = (x + 319); y = (175-((93*y) >> 7));}

  union REGS reg;
  #define seqRout(index,val) {outp(Ox3C4,index); outp(0x3C5,val);}
  #define graph_out(index,val) {outp(0x3CE,index); outp(0x3CF,val);}
  uint offset;
  char * mem_address;
  float a,aspect_square;
  int col,row,dummy,mask,end_x,end_y,kx;
  long a_square,b_square,b_test;
  a = b/aspect;
  a_square = a*a;
  b = (93*b) >> 7;
  b_square = b*b;
  convert(x,y);
  end_x = x+a;
  end_Y = y+b;
  for (col=x-a; col<=end_x; col++) {
    b_test = b_square - (b_square*(col-x)*(col-x))/a_square;
    mask = 0x80 >> ((col) % 8);
    graph_out(8,mask);
    seq_out(2,0x0F);
    for (row=y-b; row<=end_y; row++) {
      kx = rand()/(32767/(1.3*radius));
      if (((row-y)*(row-y) <= b_test) && (kx < (col-x+20))) {
        offset = (long)row*80L + ((long)(col)/8L);
        mem_address = (char *) 0xA0000000L + offset;
        dummy = *mem_address;
        *mem_address = 0;
        seq_out(2,color);
        *mem_address = 0xFF;
        seq_out(2,0x0F);
      }
    }
  }

  graph_out(3,0);
  graph_out(8,0xFF);
#endif
}

void
CLunar::
fillOval(int x, int y, int b, int color, float aspect)
{
  x = x + w_/2;
  y = h_/2 - y;

  set_color(color);

  fillEllipse(CIPoint2D(x, y), b, aspect*b);
}

void
CLunar::
plot(int x, int y, int color)
{
  x = x + w_/2;
  y = h_/2 - y;

  set_color(color);

  drawPoint(CIPoint2D(x, y));
}

void
CLunar::
set_color(int color)
{
  static CRGBA
  vga_colors[16] = {
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

  static CRGBA
  ega_colors[65] = {
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

  //int color_map[16] = {0,1,2,11,10,10,34,31,47,58,18,2,6,27,62,63};

  //setForeground(colors[color_map[color]]);
  setForeground(vga_colors[color]);
}
