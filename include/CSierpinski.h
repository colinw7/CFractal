#ifndef CSIERPINSKI_H
#define CSIERPINSKI_H

#include <CIBBox2D.h>
#include <CRGBA.h>

class CSierpinskiRenderer {
 public:
  CSierpinskiRenderer() { }

  virtual void clear(const CRGBA &bg) = 0;

  virtual void drawPoint(const CIPoint2D &p) = 0;

  virtual void setForeground(const CRGBA &fg) = 0;

  virtual void fillRectangle(const CIBBox2D &bbox) = 0;
};

//------

class CSierpinski {
 public:
  enum Type {
    TYPE_NORMAL,
    TYPE_THIRD,
    TYPE_ROOT,
    TYPE_BOX
  };

 public:
  CSierpinski();

  void setType(Type type) { type_ = type; }

  void draw(CSierpinskiRenderer *renderer, int w, int h);

 private:
  void drawNormal(CSierpinskiRenderer *renderer);
  void drawThird (CSierpinskiRenderer *renderer);
  void drawRoot  (CSierpinskiRenderer *renderer);
  void drawBox   (CSierpinskiRenderer *renderer);

  void generateBox(CSierpinskiRenderer *renderer, int x1, int y1, int x2, int y2,
                   int level, int length);

  void nodeBox(CSierpinskiRenderer *renderer, int x1, int y1, int x2, int y2,
               int x3, int y3, int x4, int y4, int level, int length);

  void fillBox(CSierpinskiRenderer *renderer, int x1, int y1, int x2, int y2, bool solid);

 private:
  Type type_;
  int  w_, h_;
};

#endif
