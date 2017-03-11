#include <CScenery.h>
#include <COSRand.h>

int CScenery::range_[SIZE] = {32, 32, 32, 22, 14, 8, 4, 2};

CScenery::Color
CScenery::colors_[32] = {
  { 0.00, 0.00, 1.00, },
  { 0.00, 0.33, 0.00, },
  { 0.00, 0.47, 0.00, },
  { 0.00, 0.67, 0.00, },
  { 0.00, 0.80, 0.00, },
  { 0.00, 0.93, 0.00, },
  { 0.27, 1.00, 0.27, },
  { 0.53, 1.00, 0.53, },
  { 0.87, 1.00, 0.00, },
  { 1.00, 1.00, 0.00, },
  { 1.00, 0.87, 0.00, },
  { 1.00, 0.73, 0.00, },
  { 1.00, 0.60, 0.00, },
  { 1.00, 0.47, 0.00, },
  { 0.93, 0.33, 0.00, },
  { 0.93, 0.20, 0.20, },
  { 0.93, 0.07, 0.07, },
  { 1.00, 0.00, 0.07, },
  { 1.00, 0.00, 0.20, },
  { 1.00, 0.00, 0.33, },
  { 1.00, 0.00, 0.47, },
  { 1.00, 0.00, 0.60, },
  { 1.00, 0.00, 0.73, },
  { 1.00, 0.00, 0.87, },
  { 1.00, 0.07, 1.00, },
  { 1.00, 0.20, 1.00, },
  { 1.00, 0.33, 1.00, },
  { 1.00, 0.47, 1.00, },
  { 1.00, 0.60, 1.00, },
  { 1.00, 0.73, 1.00, },
  { 1.00, 0.87, 1.00, },
  { 1.00, 1.00, 1.00, },
};

CScenery::
CScenery() :
 cell_(NULL)
{
  cell_ = new int [COUNT*COUNT];

  setColors();

  grow();
}

void
CScenery::
setColors()
{
  for (uint i = 0; i < 32; i++) {
    double r = colors_[i].r;
    double g = colors_[i].g;
    double b = colors_[i].b;

    rgba_[i] = CRGBA(r, g, b);
  }
}

void
CScenery::
grow()
{
  cell_[0] = 0;

  int step = COUNT;

  for (int i = 0; i < SIZE; i++) {
    int next_step = step / 2;

    for (int l = 0; l < COUNT; l += step) {
      int l1 = l + next_step;
      int l2 = l + step;

      if (l2 == COUNT)
        l2 = 0;

      int lc  = l *COUNT;
      int l1c = l1*COUNT;
      int l2c = l2*COUNT;

      for (int c = 0; c < COUNT; c += step) {
        int c1 = c + next_step;
        int c2 = c + step;

        if (c2 == COUNT)
          c2 = 0;

        set(lc  + c1, i, (cell_[lc  + c ] + cell_[lc  + c2] + 1) / 2);
        set(l1c + c , i, (cell_[lc  + c ] + cell_[l2c + c ] + 1) / 2);
        set(l1c + c1, i, (cell_[lc  + c ] + cell_[lc  + c2] +
                          cell_[l2c + c ] + cell_[l2c + c2] + 2) / 4);
      }
    }

    step = next_step;
  }
}

void
CScenery::
draw()
{
  int lc = 0;

  int mc = COUNT;
  int ml = COUNT;

  for (int l = 0; l < ml; l++) {
    for (int c = 0; c < mc; c++) {
      int cell_height = cell_[lc + c];

      if      (cell_height < 0)
        setForeground(rgba_[0]);
      else if (cell_height >= 32)
        setForeground(rgba_[31]);
      else
        setForeground(rgba_[cell_height]);

      drawPoint(c, l);
    }

    lc += COUNT;
  }
}

void
CScenery::
set(int lc, int size, int height)
{
  int rang = range_[size];

  height = height + COSRand::randIn(0, rang) - (rang + 1) / 2;

  cell_[lc] = height;
}
