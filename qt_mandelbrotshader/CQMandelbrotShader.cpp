#include <CQMandelbrotShader.h>
#include <QApplication>
#include <QGLWidget>
#include <QOpenGLShaderProgram>
#include <QMouseEvent>
#include <iostream>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  Canvas *canvas = new Canvas;

  canvas->show();

  app.exec();
}

Canvas::
Canvas() :
 QGLWidget(), maxIter_(256)
{
  resetRange();
}

void
Canvas::
initializeGL()
{
  glClearColor(0.0, 0.0, 0.0, 0.0);

  program_ = new QOpenGLShaderProgram();

  textureId_ = loadTexture("gradient.png");

  if (! program_->addShaderFromSourceFile(QOpenGLShader::Vertex, "vertex_shader.glsl"))
    std::cerr << program_->log().toStdString() << std::endl;

  if (! program_->addShaderFromSourceFile(QOpenGLShader::Fragment, "fragment_shader.glsl"))
    std::cerr << program_->log().toStdString() << std::endl;

  program_->link();
}

void
Canvas::
paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT);

  program_->bind();

  QVector3D vertices[] = {
    QVector3D(-1.0f, -1.0f, 1.0f),
    QVector3D( 1.0f, -1.0f, 1.0f),
    QVector3D( 1.0f,  1.0f, 1.0f),
    QVector3D( 1.0f,  1.0f, 1.0f),
    QVector3D(-1.0f,  1.0f, 1.0f),
    QVector3D(-1.0f, -1.0f, 1.0f)
  };

  //---

  int textureLocation = program_->uniformLocation("u_TextureUnit");

  int xMinLocation    = program_->uniformLocation("u_XMin");
  int yMinLocation    = program_->uniformLocation("u_YMin");
  int xMaxLocation    = program_->uniformLocation("u_XMax");
  int yMaxLocation    = program_->uniformLocation("u_YMax");
  int maxIterLocation = program_->uniformLocation("u_MaxIter");

  int coordsLocation = program_->attributeLocation("a_Coordinates");

  //---

  program_->enableAttributeArray(coordsLocation);

  program_->setAttributeArray(coordsLocation, vertices);

  glActiveTexture(GL_TEXTURE0);

  glBindTexture(GL_TEXTURE_2D, textureId_);

  program_->setUniformValue(textureLocation, 0);

  program_->setUniformValue(xMinLocation   , rangeXMin_);
  program_->setUniformValue(yMinLocation   , rangeYMin_);
  program_->setUniformValue(xMaxLocation   , rangeXMax_);
  program_->setUniformValue(yMaxLocation   , rangeYMax_);
  program_->setUniformValue(maxIterLocation, maxIter_  );

  glDrawArrays(GL_TRIANGLES, 0, 6);

  program_->disableAttributeArray(coordsLocation);

  program_->release();
}

void
Canvas::
resizeGL(int width, int height)
{
  glViewport(0, 0, width, height);

  float aspectRatio = width > height ?
    (float) width / (float) height : (float) height / (float) width;

  if (width > height) {
    xmin_ = -aspectRatio; ymin_ = -1.0f;
    xmax_ =  aspectRatio; ymax_ =  1.0f;
  }
  else {
    xmin_ = -1.0f; ymin_ = -aspectRatio;
    xmax_ =  1.0f; ymax_ =  aspectRatio;
  }

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  glMatrixMode(GL_MODELVIEW);
}

void
Canvas::
mousePressEvent(QMouseEvent *e)
{
  pressButton_ = e->button();
  pressX1_     = e->pos().x();
  pressY1_     = e->pos().y();
}

void
Canvas::
mouseMoveEvent(QMouseEvent *e)
{
  pressX2_ = e->pos().x();
  pressY2_ = e->pos().y();

  double x1, y1, x2, y2;

  pixelToWindow(pressX1_, pressY1_, x1, y1);
  pixelToWindow(pressX2_, pressY2_, x2, y2);

  if (pressButton_ == Qt::MidButton) {
    double dx = x1 - x2;
    double dy = y1 - y2;

    rangeXMin_ += dx;
    rangeYMin_ += dy;
    rangeXMax_ += dx;
    rangeYMax_ += dy;

    pressX1_ = pressX2_;
    pressY1_ = pressY2_;

    update();
  }
}

void
Canvas::
mouseReleaseEvent(QMouseEvent *e)
{
  pressX2_ = e->pos().x();
  pressY2_ = e->pos().y();

  double x1, y1, x2, y2;

  pixelToWindow(pressX1_, pressY1_, x1, y1);
  pixelToWindow(pressX2_, pressY2_, x2, y2);

  if      (pressButton_ == Qt::LeftButton) {
    rangeXMin_ = std::min(x1, x2);
    rangeYMin_ = std::min(y1, y2);
    rangeXMax_ = std::max(x1, x2);
    rangeYMax_ = std::max(y1, y2);

    update();
  }
  else if (pressButton_ == Qt::MidButton) {
    double dx = x2 - x1;
    double dy = y1 - y2;

    rangeXMin_ += dx;
    rangeYMin_ += dy;
    rangeXMax_ += dx;
    rangeYMax_ += dy;

    update();
  }
}

void
Canvas::
pixelToWindow(int px, int py, double &rx, double &ry)
{
  double dx =       (1.0*px)/QWidget::width ();
  double dy = 1.0 - (1.0*py)/QWidget::height();

  rx = rangeXMin_ + dx*(rangeXMax_ - rangeXMin_);
  ry = rangeYMin_ + dy*(rangeYMax_ - rangeYMin_);
}

void
Canvas::
resetRange()
{
  rangeXMin_ = -2.0f;
  rangeYMin_ = -1.2f;
  rangeXMax_ =  1.2f;
  rangeYMax_ =  1.2f;
}

GLuint
Canvas::
loadTexture(const std::string &name)
{
  glEnable(GL_TEXTURE_2D);

  QImage texBuf;

  texBuf.load(name.c_str());

  QImage tex = QGLWidget::convertToGLFormat(texBuf);

  GLuint id = 0;

  glGenTextures(1, &id);

  glBindTexture(GL_TEXTURE_2D, id);

  GLint internFormat;

  GLenum format;

  if (tex.hasAlphaChannel()) {
    internFormat = 4;

    format = GL_RGBA;
  }
  else {
    internFormat = 3;

    format = GL_RGB;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, internFormat, tex.width(), tex.height(),
               0, format, GL_UNSIGNED_BYTE, tex.bits());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glDisable(GL_TEXTURE_2D);

  return id;
}
