#include <CPlasma.h>

#define SPEEDCOMP 1.3

#define DEF_WIDTH  320
#define DEF_HEIGHT 200

CPlasma::
CPlasma(uint width, uint height) :
 width_(width), height_(height)
{
  loadPalette(1);

  da_ = 2.0*M_PI/width_;
}

/*--------------------------------------------------------------------------*/

void
CPlasma::
drawSimpleSine()
{
  int ym = height_/2;
  int dy = int(ym*0.8);

  for (uint i = 0; i < width_; ++i) {
    double angle = da_*i;

    setPixel(i, ym + dy*sin(angle), 15);
  }

  drawLine(0, ym, width_ - 1, ym);
}

/*--------------------------------------------------------------------------*/

void
CPlasma::
drawSine()
{
  double dy = height_/4;

  int y1 = dy;
  int y2 = y1 + dy;
  int y3 = y2 + dy;

  dy *= 0.9;

  for (uint i = 0; i < width_; ++i) {
    double angle = da_*i;

    setPixel(i, y1 + dy*sin(  angle + 2.0*M_PI/8), 15);
  }

  drawLine(0, y1, width_ - 1, y1);

  for (uint i = 0; i < width_; ++i) {
    double angle = da_*i;

    setPixel(i, y2 + dy*sin(2*angle             ), 15);
  }

  drawLine(0, y2, width_ - 1, y2);

  for (uint i = 0; i < width_; ++i) {
    double angle = da_*i;

    setPixel(i, y3 + dy*sin(2*angle + 2.0*M_PI/8), 15);
  }

  drawLine(0, y3, width_ - 1, y3);
}

/*--------------------------------------------------------------------------*/

void
CPlasma::
drawDoubleSine()
{
  int ym = height_/2;

  int dy1 = int(ym*0.4);
  int dy2 = int(ym*0.3);
  int dy3 = int(ym*0.2);

  for (uint i = 0; i <width_; ++i) {
    double angle = da_*i;

    setPixel(i, ym + dy1*sin(angle) + dy2*sin(2*angle) + dy3*sin(4*angle), 15);
  }

  drawLine(0, ym, width_ - 1, ym);
}

/*--------------------------------------------------------------------------*/

void
CPlasma::
drawMovingSine()
{
  static double angle1 = 0, angle2 = 0, angle3 = 0;

  int ym = height_/2;

  int dy1 = int(ym*0.40);
  int dy2 = int(ym*0.25);
  int dy3 = int(ym*0.15);

  double angle1bak = angle1;
  double angle2bak = angle2;
  double angle3bak = angle3;

  for (uint i = 0; i < width_; ++i) {
    setPixel(i, ym + dy1*sin(angle1) + dy2*sin(angle2) + dy3*sin(angle3), 15);

    angle1 +=   da_;
    angle2 += 2*da_;
    angle3 += 4*da_;
  }

  angle1 = angle1bak + 1*da_*SPEEDCOMP/10;
  angle2 = angle2bak + 3*da_*SPEEDCOMP/10;
  angle3 = angle3bak + 2*da_*SPEEDCOMP/10;
}

/*--------------------------------------------------------------------------*/

void
CPlasma::
drawBasicPlasma()
{
  static double angle1 = 0, angle2 = 0, angle3 = 0;

  uint width1 = 500;

  int border = 4;

  int graph_scale  = 28;
  int graph_center = border + graph_scale;;
  int plasma_pos   = graph_center + graph_scale + border;

  double color_start = 64;
  double color_end   = 92;
  double color_range = color_end - color_start;

  double da1 = 2.0*M_PI/width1;

  double iw = 1.0/width1;

  double angle1bak = angle1;
  double angle2bak = angle2;
  double angle3bak = angle3;

  for (uint i = 0; i < width1; ++i) {
    angle1 -=   da1;
    angle2 += 2*da1;
    angle3 += 4*da1;

    // -1, 1
    double value = 0.571*sin(angle1) + 0.286*sin(angle2) + 0.143*sin(angle3);

    setPixel(i + border, graph_center + graph_scale*value, 15);

    for (uint j = 0; j < width1; ++j) {
      setPixel(i + border, plasma_pos + j, color_start + color_range*value);

      value += 6*iw;
    }
  }

  angle1 = angle1bak + 1*da_*SPEEDCOMP/2;
  angle2 = angle2bak + 3*da_*SPEEDCOMP/2;
  angle3 = angle3bak + 2*da_*SPEEDCOMP/2;
}

/*--------------------------------------------------------------------------*/

void
CPlasma::
drawRealPlasma()
{
  static double angle1 = 0, angle2 = 0, angle3 = 0, angle4 = 0, angle5 = 0;

  int xbuffer[128], ybuffer[128];

  uint width1 = 128;

  double da1 = 2.0*M_PI/width1;

  //----

  double angle1bak = angle1;
  double angle2bak = angle2;
  double angle3bak = angle3;

  for (uint i = 0; i < width1; ++i) {
    double value = 16*sin(angle1) + 8*sin(angle2) + 4*sin(angle3);

    setPixel(i + 100, 32 + value, 15);

    xbuffer[i] = value;

    angle1 +=   da1;
    angle2 += 2*da1;
    angle3 += 4*da1;
  }

  //----

  angle1 = angle1bak - 1*da_*SPEEDCOMP;
  angle2 = angle2bak + 3*da_*SPEEDCOMP;
  angle3 = angle3bak + 2*da_*SPEEDCOMP;

  double angle4bak = angle4;
  double angle5bak = angle5;

  for (uint i = 0; i < width1; ++i) {
    double value = 16*sin(angle4) + 8*sin(angle5);

    setPixel(40 + value, 70 + i, 15);

    ybuffer[i] = value;

    angle4 +=   da1;
    angle5 += 2*da1;
  }

  //angle4 = angle1bak + 3*da_*SPEEDCOMP;
  //angle5 = angle2bak + 5*da_*SPEEDCOMP;

  angle4 = angle4bak + 3*da_*SPEEDCOMP;
  angle5 = angle5bak + 5*da_*SPEEDCOMP;

  //----

  for (uint j = 0; j < width1; j++) {
    int value = ybuffer[j];

    for (uint i = 0; i < width1; ++i) {
      setPixel(i + 100, j + 70, 128 + value + xbuffer[i]);
    }
  }
}

void
CPlasma::
loadPalette(uint id)
{
  const char *fname;

  if (id == 1)
    fname = "plas1.pal";
  else
    fname = "plas2.pal";

  struct PalEntry {
    unsigned char red, green, blue;
  };

  PalEntry palette[256];

  FILE *fp = fopen(fname, "rb");

  if (fp == NULL) {
    fprintf(stderr, "Error loading %s !\n", fname);
    return;
  }

  fseek(fp, 18, SEEK_CUR);

  PalEntry *entry = palette;

  for (uint i = 0; i < 256; ++i) {
    fread((char*) entry, 1, 3, fp);

    ++entry;
  }

  fclose(fp);

  for (uint i = 0; i < 256; ++i)
    colors_[i] = CRGBA(palette[i].red  /255.0,
                       palette[i].green/255.0,
                       palette[i].blue /255.0);
}

void
CPlasma::
setPixel(uint x, uint y, uint col)
{
  setForeground(colors_[col]);

  drawPoint(x, y);
}
