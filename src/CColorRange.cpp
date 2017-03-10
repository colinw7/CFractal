#include <CColorRange.h>

CColorRange::
CColorRange()
{
  init();
}

void
CColorRange::
init()
{
  colors_.resize(256);

  int i1 = 0;
  int i2 = 0;
  int i3 = 0;

  colors_[0] = CRGB(i1/255.0, i2/255.0, i3/255.0);

  /* We want Blues, Greens then Reds in our Palette */

  for (int i = 1; i < 85; ++i) {
    i1 = 0;
    i2 = 3*i;
    i3 = 3*(86 - i);

    colors_[i +   0] = CRGB(i1/255.0, i2/255.0, i3/255.0);
    colors_[i +  85] = CRGB(i2/255.0, i3/255.0, i1/255.0);
    colors_[i + 170] = CRGB(i3/255.0, i1/255.0, i2/255.0);
  }

  i1 = 0;
  i2 = 255;
  i3 = 51;

  colors_[ 85] = CRGB(i1/255.0, i2/255.0, i3/255.0);
  colors_[170] = CRGB(i2/255.0, i3/255.0, i1/255.0);
  colors_[255] = CRGB(i3/255.0, i1/255.0, i2/255.0);
}
