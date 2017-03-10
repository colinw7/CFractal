#ifndef CQPOINT_FRACTAL_H
#define CQPOINT_FRACTAL_H

#include <QWidget>
#include <QImage>

#include <CRGBA.h>

class CPointFractalCalc;
class CQPointFractalRenderer;
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

 private:
  friend class CQPointFractalRenderer;

  void setForeground(const CRGBA &rgba);

  void drawPoint(int x, int y);

 private:
  void paintEvent (QPaintEvent *);
  void resizeEvent(QResizeEvent *);

  void mousePressEvent  (QMouseEvent *event);
  void mouseMoveEvent   (QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void updateRubberband(const QPoint &p1, const QPoint &p2);

  void selectionNotify(const QPoint &p1, const QPoint &p2);

 private:
  CQPointFractalRenderer *renderer_;
  QImage                  qimage_;
  bool                    threaded_;
  bool                    redraw_;
  QPainter               *painter_;
  QRubberBand            *rubber_band_;
  QPoint                  press_pos_;
};

#endif
