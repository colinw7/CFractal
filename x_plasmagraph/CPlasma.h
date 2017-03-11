#ifndef CPLASMA_H
#define CPLASMA_H

#include <CRGBA.h>

class CPlasma {
 private:
  uint   width_, height_;
  double da_;
  CRGBA  colors_[256];

 public:
  CPlasma(uint width, uint height);

  virtual ~CPlasma() { }

  void drawSimpleSine();
  void drawSine();
  void drawDoubleSine();
  void drawMovingSine();

  void drawBasicPlasma();
  void drawRealPlasma();

  void loadPalette(uint id);

  void setPixel(uint x, uint y, uint col);

  virtual void setForeground(const CRGBA &rgba) = 0;
  virtual void drawPoint(uint x, uint y) = 0;
  virtual void drawLine(uint x1, uint y1, uint x2, uint y2) = 0;
};

#endif
