#ifndef CQMandelbrotShader_H
#define CQMandelbrotShader_H

#include <QWindow>
#include <QGLWidget>

class QOpenGLShaderProgram;

class Canvas : public QGLWidget {
  Q_OBJECT

 public:
  Canvas();

  void initializeGL();

  void paintGL();

  void resizeGL(int, int);

  void resetRange();

  float xmin() { return xmin_; }
  float ymin() { return ymin_; }
  float xmax() { return xmax_; }
  float ymax() { return ymax_; }

  float width () { return xmax_ - xmin_; }
  float height() { return ymax_ - ymin_; }

  void mousePressEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

  void pixelToWindow(int px, int py, double &rx, double &ry);

 private:
  GLuint loadTexture(const std::string &name);

 private:
  QOpenGLShaderProgram *program_;
  int                   maxIter_;
  float                 xmin_, ymin_, xmax_, ymax_;
  GLfloat               rangeXMin_, rangeYMin_, rangeXMax_, rangeYMax_;
  GLuint                textureId_;
  int                   pressX1_, pressY1_;
  int                   pressX2_, pressY2_;
  Qt::MouseButton       pressButton_;
};

#endif
