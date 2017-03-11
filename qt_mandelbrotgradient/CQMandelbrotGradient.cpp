#include <CQMandelbrotGradient.h>
#include <CQUtil.h>
#include <CMandelbrot.h>
#include <QApplication>
#include <QPainter>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQMandelbrotGradient *mandelbrot = new CQMandelbrotGradient;

  mandelbrot->show();

  return app.exec();
}

CQMandelbrotGradient::
CQMandelbrotGradient() :
 palette_(new CExpr)
{
}

void
CQMandelbrotGradient::
paintEvent(QPaintEvent *)
{
  QPainter p(this);

  p.fillRect(rect(), Qt::black);

  CTransform2D transform;

  transform.setFrom(0, 0, width() - 1, height() - 1);

  double xmin = mandelbrot_.getXMin();
  double ymin = mandelbrot_.getYMin();
  double xmax = mandelbrot_.getXMax();
  double ymax = mandelbrot_.getYMax();

  int max_iterations = 256;

  transform.setTo(xmin, ymin, xmax, ymax);

  std::vector<double> x_store, y_store;

  x_store.resize(width ());
  y_store.resize(height());

  double dummy;

  for (int x = 0; x < width(); ++x)
    transform.conv(x, 0, &x_store[x], &dummy);

  for (int y = 0; y < height(); ++y)
    transform.conv(0, y, &dummy, &y_store[y]);

  mandelbrot_.setRange(xmin, ymin, xmax, ymax);

  mandelbrot_.initCalc(0, 0, width() - 1, height() - 1, xmin, ymin, xmax, ymax, max_iterations);

  for (int y = 0; y < height(); ++y) {
    double yy = y_store[y];

    for (int x = 0; x < width(); ++x) {
      double xx = x_store[x];

      int c = mandelbrot_.calc(xx, yy, max_iterations);

      if (c >= 0) {
        double x = (1.0*c)/max_iterations;

        CRGBA c1 = palette_.getColor(x).rgba();

        QColor c2 = CQUtil::toQColor(c1);

        p.setPen(c2);
      }

      p.drawPoint(x, y);
    }
  }
}
