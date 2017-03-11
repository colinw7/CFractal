#include <CSierpinski.h>
#include <CMathRand.h>

CSierpinski::
CSierpinski() :
 type_(TYPE_NORMAL)
{
}

void
CSierpinski::
draw(CSierpinskiRenderer *renderer, int w, int h)
{
  w_ = w;
  h_ = h;

  if      (type_ == TYPE_NORMAL)
    drawNormal(renderer);
  else if (type_ == TYPE_THIRD)
    drawThird(renderer);
  else if (type_ == TYPE_ROOT)
    drawRoot(renderer);
  else if (type_ == TYPE_BOX)
    drawBox(renderer);
}

void
CSierpinski::
drawNormal(CSierpinskiRenderer *renderer)
{
  renderer->clear(CRGBA(1,1,1));

  renderer->setForeground(CRGBA(0,0,0));

  double x = CMathRand::randInRange(0, w_ - 1);
  double y = CMathRand::randInRange(0, h_ - 1);

  uint num_iterations = 250000;

  for (uint i = 0; i < num_iterations; ++i) {
    int type = CMathRand::randInRange(0, 2);

    switch (type) {
      case 0:
        x /= 2;
        y /= 2;
        break;
      case 1:
        x = (x + w_ - 1)/2;
        y /= 2;
        break;
      case 2:
        x = (x + w_/2  )/2;
        y = (y + h_ - 1)/2;
        break;
      default:
        break;
    }

    renderer->drawPoint(CIPoint2D(x, h_ - 1 - y));
  }
}

void
CSierpinski::
drawThird(CSierpinskiRenderer *renderer)
{
  renderer->clear(CRGBA(1,1,1));

  renderer->setForeground(CRGBA(0,0,0));

  double x = CMathRand::randInRange(0, w_ - 1);
  double y = CMathRand::randInRange(0, h_ - 1);

  uint num_iterations = 250000;

  for (uint i = 0; i < num_iterations; ++i) {
    int type = CMathRand::randInRange(0, 3);

    switch (type) {
      case 0:
        x /= 3;
        y /= 3;
        break;
      case 1:
        x = (x + w_ - 1)*2/3;
        y /= 3;
        break;
      case 2:
        x = (x + w_ - 1)/3;
        y = (y + h_ - 1)*2/3;
        break;
      case 3:
        x /= 3;
        y = (y + h_ - 1)*2/3;
        break;
      default:
        break;
    }

    renderer->drawPoint(CIPoint2D(x, y));
  }
}

void
CSierpinski::
drawRoot(CSierpinskiRenderer *renderer)
{
  renderer->clear(CRGBA(1,1,1));

  renderer->setForeground(CRGBA(0,0,0));

  double x = CMathRand::randInRange(0, w_ - 1);
  double y = CMathRand::randInRange(0, h_ - 1);

  double s2 = sqrt(0.5);

  uint num_iterations = 250000;

  for (uint i = 0; i < num_iterations; ++i) {
    int type = CMathRand::randInRange(0, 2);

    switch (type) {
      case 0:
        x *= s2;
        y *= s2;
        break;
      case 1:
        x = sqrt(((w_ - 1)*(w_ - 1) + x*x)/2);
        y *= s2;
        break;
      case 2:
        x = sqrt((w_*w_/4 + x*x)/2);
        y = sqrt(((h_ - 1)*(h_ - 1) + y*y)/2);
        break;
      default:
        break;
    }

    renderer->drawPoint(CIPoint2D(x, y));
  }
}

void
CSierpinski::
drawBox(CSierpinskiRenderer *renderer)
{
  renderer->clear(CRGBA(1,1,1));

  int length = std::min(w_, h_);

  int x1 = -length/2;
  int y1 = -length/2;
  int x2 =  length/2;
  int y2 =  length/2;

  fillBox(renderer, x1, y1, x2, y2, true);

  int level = 4;

  generateBox(renderer, x1, y1, x2, y2, level, length);
}

void
CSierpinski::
generateBox(CSierpinskiRenderer *renderer, int x1, int y1, int x2, int y2,
            int level, int length)
{
  int length1 = length/3;

  int x3 = x1 + length1;
  int y3 = y1 + length1;
  int x4 = x2 - length1;
  int y4 = y2 - length1;

  nodeBox(renderer, x1, y1, x2, y2, x3, y3, x4, y4, level, length1);
}

void
CSierpinski::
nodeBox(CSierpinskiRenderer *renderer, int x1, int y1, int x2, int y2,
        int x3, int y3, int x4, int y4, int level, int length)
{
  fillBox(renderer, x3, y3, x4, y4, false);

  if (level == 0) return;

  generateBox(renderer, x1, y1, x3, y3, level - 1, length);
  generateBox(renderer, x3, y1, x4, y3, level - 1, length);
  generateBox(renderer, x4, y1, x2, y3, level - 1, length);
  generateBox(renderer, x1, y3, x3, y4, level - 1, length);
  generateBox(renderer, x4, y3, x2, y4, level - 1, length);
  generateBox(renderer, x1, y4, x3, y2, level - 1, length);
  generateBox(renderer, x3, y4, x4, y2, level - 1, length);
  generateBox(renderer, x4, y4, x2, y2, level - 1, length);
}

void
CSierpinski::
fillBox(CSierpinskiRenderer *renderer, int x1, int y1, int x2, int y2, bool solid)
{
  x1 = w_/2 + x1; y1 = h_/2 + y1;
  x2 = w_/2 + x2; y2 = h_/2 + y2;

  if (solid)
    renderer->setForeground(CRGBA(0,0,0));
  else
    renderer->setForeground(CRGBA(1,1,1));

  renderer->fillRectangle(CIBBox2D(x1, y1, x2, y2));
}
