#ifndef CQPMANDELBROT_H
#define CQPMANDELBROT_H

#include <CRGBA.h>
#include <CColorRange.h>
#include <CTransform2D.h>
#include <CMandelbrot.h>

#include <QWidget>
#include <QImage>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

class CQPMandelbrotThread;
class QRubberBand;

class CQPMandelbrot : public QWidget {
  Q_OBJECT

 private:
  enum { NUM_SPLITS=3 };
  enum { NUM_THREADS=NUM_SPLITS*NUM_SPLITS };

 public:
  CQPMandelbrot(QWidget *parent = 0);

 ~CQPMandelbrot();

  CMandelbrot *getMandelbrot() const { return mandelbrot_; }

  void resetRange();

  void setIterations(int iterations);

  void toggleShowVector();

  void resize();

  void getRange(double *xmin, double *ymin, double *xmax, double *ymax) const {
    *xmin = xmin_;
    *ymin = ymin_;
    *xmax = xmax_;
    *ymax = ymax_;
  }

  void setRange(double xmin, double ymin, double xmax, double ymax) {
    xmin_ = xmin;
    ymin_ = ymin;
    xmax_ = xmax;
    ymax_ = ymax;
  }

  int getMaxIterations() const { return max_iterations_; }

  void setMaxIterations(int iterations) {
    max_iterations_ = iterations;
  }

  bool getShowVector() const { return show_vector_; }

  void setShowVector(bool show_vector) { show_vector_ = show_vector; }

  void redraw();

 private:
  void paintEvent(QPaintEvent *);
  void resizeEvent(QResizeEvent *);

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void updateRubberband(const QPoint &p1, const QPoint &p2);

  void selectionNotify(const QPoint &p1, const QPoint &p2);

  void conv(double px, double py, double *wx, double *wy);
  void iconv(double wx, double wy, double *px, double *py);

  void draw(int pixel_xmin, int pixel_ymin, int pixel_xmax, int pixel_ymax,
            double xmin, double ymin, double xmax, double ymax,
            int max_iterations);

 private slots:
  void drawImageSlot(int x, int y, const QImage &image);

 private:
  CMandelbrot         *mandelbrot_;
  QImage               qimage_;
  bool                 redraw_;
  CQPMandelbrotThread *threads_[NUM_THREADS];
  int                  px_[NUM_SPLITS + 1], py_[NUM_SPLITS + 1];
  double               dx_[NUM_SPLITS + 1], dy_[NUM_SPLITS + 1];
  CTransform2D         transform_;
  int                  max_iterations_;
  bool                 show_vector_;
  double               xmin_, ymin_, xmax_, ymax_;
  QRubberBand         *rubber_band_;
  QPoint               press_pos_;

  std::vector<int> pixels_;
};

class CQPMandelbrotThread : public QThread {
  Q_OBJECT

 public:
  CQPMandelbrotThread();
 ~CQPMandelbrotThread();

  void init(int pixel_xmin, int pixel_ymin, int pixel_xmax, int pixel_ymax,
            double xmin, double ymin, double xmax, double ymax,
            uint max_iterations);

  void run();

  void draw(QPainter *painter);

  void abort() { abort_ = true; }

  bool isFinished() const { return finished_; }

 signals:
  void drawImageSignal(int x, int y, const QImage &image);

 private:
  CMandelbrot    mandelbrot_;
  QMutex         mutex_;
  QWaitCondition condition_;
  QImage         qimage_;
  CColorRange    colors_;
  CTransform2D   transform_;
  int            pixel_xmin_, pixel_ymin_, pixel_xmax_, pixel_ymax_;
  double         xmin_, ymin_, xmax_, ymax_;
  uint           max_iterations_;
  bool           restart_;
  bool           abort_;
  bool           finished_;

  std::vector<double> x_store_, y_store_;
};

#endif
