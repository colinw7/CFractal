#ifndef CQSierpinski_H
#define CQSierpinski_H

#include <CSierpinski.h>
#include <QWidget>

class CQWidgetPixelRenderer;

class CQSierpinski : public QWidget, public CSierpinski {
 public:
  CQSierpinski();

  void paintEvent(QPaintEvent *);

  void resizeEvent(QResizeEvent *);

 private:
  CQWidgetPixelRenderer *renderer_ { nullptr };
};

//---

class CQSierpinskiRenderer : public CSierpinskiRenderer {
 public:
  CQSierpinskiRenderer(CQWidgetPixelRenderer *renderer) :
   renderer_(renderer) {
  }

  void clear(const CRGBA &bg);

  void drawPoint(const CIPoint2D &p);

  void setForeground(const CRGBA &fg);

  void fillRectangle(const CIBBox2D &bbox);

 private:
  CQWidgetPixelRenderer *renderer_ { nullptr };
};

//---

class CQSierpinskiWindow : public QWidget {
 public:
  CQSierpinskiWindow();

  void setType(CSierpinski::Type type);

 private:
  CQSierpinski *sierpinski_ { nullptr };
};

#endif
