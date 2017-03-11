#ifndef CFractalLeaf_H
#define CFractalLeaf_H

#include <CRGBA.h>

class CFractalLeaf {
 public:
  enum Type {
    SIERPINSKI,
    FERN,
    TREE,
    CANTOR,
    CIRCLE,
    MAPLE
  };

 private:
  Type type_;

 public:
  CFractalLeaf();

  virtual ~CFractalLeaf() { }

  void setType(Type type) { type_ = type; }

  void draw(int w, int h);

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void drawPoint(const CIPoint2D &p) = 0;
};

#endif
