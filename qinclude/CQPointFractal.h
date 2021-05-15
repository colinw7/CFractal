#ifndef CQPOINT_FRACTAL_H
#define CQPOINT_FRACTAL_H

#include <QWidget>
#include <QImage>

#include <CRGBA.h>

class CPointFractalCalc;
class CQPointFractalRenderer;
class CQColorsPalette;
class QPainter;
class QRubberBand;

class CQPointFractal : public QWidget {
  Q_OBJECT

  Q_PROPERTY(bool   threaded   READ isThreaded WRITE setThreaded  )
  Q_PROPERTY(int    iterations READ iterations WRITE setIterations)
  Q_PROPERTY(bool   showVector READ showVector WRITE setShowVector)
  Q_PROPERTY(QRectF range      READ range      WRITE setRange     )

 public:
  CQPointFractal(QWidget *parent = 0);

  virtual ~CQPointFractal();

  void setFractal(CPointFractalCalc *fractal);

  void setThreaded(bool threaded);
  bool isThreaded() const { return threaded_; }

  void resetRange();

  QRectF range() const;
  void setRange(const QRectF &r);

  int iterations() const;
  void setIterations(int iterations);

  bool showVector() const;
  void setShowVector(bool show);

  void toggleShowVector();

  void redraw();

  void setPalette(const QString &name);

 private:
  friend class CQPointFractalRenderer;

  void setForeground(int color);
  void setForeground(const CRGBA &rgba);

  void drawPoint(int x, int y);

 private:
  void paintEvent (QPaintEvent *) override;
  void resizeEvent(QResizeEvent *) override;

  void mousePressEvent  (QMouseEvent *event) override;
  void mouseMoveEvent   (QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

  void updateRubberband(const QPoint &p1, const QPoint &p2);

  void selectionNotify(const QPoint &p1, const QPoint &p2);

 private:
  CQPointFractalRenderer* renderer_    { nullptr };
  CQColorsPalette*        palette_     { nullptr };
  QImage                  qimage_;
  bool                    threaded_    { true };
  bool                    redraw_      { true };
  QPainter*               painter_     { nullptr };
  QRubberBand*            rubber_band_ { nullptr };
  QPoint                  press_pos_;
};

#endif
