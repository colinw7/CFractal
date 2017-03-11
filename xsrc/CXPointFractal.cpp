#include <CXPointFractal.h>
#include <CPointFractalRenderer.h>
#include <CTransform2D.h>

class CXPointFractalRenderer : public CPointFractalRenderer {
 public:
  CXPointFractalRenderer(CXPointFractal *pf, CPointFractalCalc *fractal) :
   CPointFractalRenderer(fractal), pf_(pf) {
  }

  void setForeground(const CRGBA &rgba) {
    pf_->setForeground(rgba);
  }

  void drawPoint(int x, int y) {
    pf_->drawPoint(x, y);
  }

 private:
  CXPointFractal *pf_;
};

//------

CXPointFractal::
CXPointFractal(CPointFractalCalc *calc) :
 CXWindow(400, 400), calc_(calc)
{
  frenderer_ = new CXPointFractalRenderer(this, calc_);
  renderer_  = new CXLibPixelRenderer(this);

  canvas_width_  = 400;
  canvas_height_ = 400;

  max_iterations_ = 128;

  resetRange();

  zooming_ = false;

  draw_ = true;
}

CXPointFractal::
~CXPointFractal()
{
  delete renderer_;
  delete frenderer_;
}

void
CXPointFractal::
resetRange()
{
  canvas_xmin_ = calc_->getXMin();
  canvas_ymin_ = calc_->getYMin();
  canvas_xmax_ = calc_->getXMax();
  canvas_ymax_ = calc_->getYMax();

  frenderer_->setRange(canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);
}

bool
CXPointFractal::
buttonPressEvent(const CMouseEvent &event)
{
  int x = event.getX();
  int y = event.getY();

  zoom_x1_ = x;
  zoom_y1_ = y;

  zoom_x2_ = zoom_x1_;
  zoom_y2_ = zoom_y1_;

  zooming_ = true;

  return true;
}

bool
CXPointFractal::
buttonMotionEvent(const CMouseEvent &event)
{
  if (! zooming_)
    return true;

  int x = event.getX();
  int y = event.getY();

  if (x == zoom_x2_ && y == zoom_y2_)
    return true;

  drawXorLine(zoom_x1_, zoom_y1_, zoom_x2_, zoom_y1_);
  drawXorLine(zoom_x2_, zoom_y1_, zoom_x2_, zoom_y2_);
  drawXorLine(zoom_x2_, zoom_y2_, zoom_x1_, zoom_y2_);
  drawXorLine(zoom_x1_, zoom_y2_, zoom_x1_, zoom_y1_);

  zoom_x2_ = x;
  zoom_y2_ = y;

  drawXorLine(zoom_x1_, zoom_y1_, zoom_x2_, zoom_y1_);
  drawXorLine(zoom_x2_, zoom_y1_, zoom_x2_, zoom_y2_);
  drawXorLine(zoom_x2_, zoom_y2_, zoom_x1_, zoom_y2_);
  drawXorLine(zoom_x1_, zoom_y2_, zoom_x1_, zoom_y1_);

  return true;
}

bool
CXPointFractal::
buttonReleaseEvent(const CMouseEvent &event)
{
  int x = event.getX();
  int y = event.getY();

  zoom_x2_ = x;
  zoom_y2_ = y;

  if (zoom_x1_ == zoom_x2_) {
    zoom_x1_ = zoom_x1_ - canvas_width_/2;
    zoom_x2_ = zoom_x2_ + canvas_width_/2;
  }

  if (zoom_y1_ == zoom_y2_) {
    zoom_y1_ = zoom_y1_ - canvas_height_/2;
    zoom_y2_ = zoom_y2_ + canvas_height_/2;
  }

  double x1, y1, x2, y2;

  CTransform2D transform(0, canvas_height_ - 1, canvas_width_ - 1, 0,
                         canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);

  transform.conv(zoom_x1_, zoom_y1_, &x1, &y1);
  transform.conv(zoom_x2_, zoom_y2_, &x2, &y2);

  if   (x1 < x2) { canvas_xmin_ = x1; canvas_xmax_ = x2; }
  else           { canvas_xmin_ = x2; canvas_xmax_ = x1; }
  if   (y1 < y2) { canvas_ymin_ = y1; canvas_ymax_ = y2; }
  else           { canvas_ymin_ = y2; canvas_ymax_ = y1; }

  frenderer_->setRange(canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);

  zooming_ = false;

  expose();

  return true;
}

bool
CXPointFractal::
keyReleaseEvent(const CKeyEvent &keyData)
{
  if      (keyData.isType(CKEY_TYPE_Plus)) {
    max_iterations_ *= 2;

    frenderer_->setMaxIterations(max_iterations_);

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_Minus)) {
    max_iterations_ /= 2;

    frenderer_->setMaxIterations(max_iterations_);

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_r)) {
    resetRange();

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_Left)) {
    double dx = (canvas_xmax_ - canvas_xmin_)/8.0;

    canvas_xmin_ -= dx;
    canvas_xmax_ -= dx;

    frenderer_->setRange(canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_Right)) {
    double dx = (canvas_xmax_ - canvas_xmin_)/8.0;

    canvas_xmin_ += dx;
    canvas_xmax_ += dx;

    frenderer_->setRange(canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_Up)) {
    double dy = (canvas_ymax_ - canvas_ymin_)/8.0;

    canvas_ymin_ += dy;
    canvas_ymax_ += dy;

    frenderer_->setRange(canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_Down)) {
    double dy = (canvas_ymax_ - canvas_ymin_)/8.0;

    canvas_ymin_ -= dy;
    canvas_ymax_ -= dy;

    frenderer_->setRange(canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_p)) {
    std::cerr << canvas_xmin_ << " " << canvas_ymin_ << " " <<
                 canvas_xmax_ << " " << canvas_ymax_ << std::endl;
  }
  else if (keyData.isType(CKEY_TYPE_v)) {
    calc_->setShowVector(! calc_->getShowVector());

    expose();
  }
  else if (keyData.isType(CKEY_TYPE_s)) {
    draw_ = ! draw_;

    expose();
  }

  return true;
}

bool
CXPointFractal::
exposeEvent()
{
  if (! draw_) return true;

  clear();

  canvas_width_  = getWidth();
  canvas_height_ = getHeight();

  frenderer_->draw(canvas_width_, canvas_height_);

  return true;
}

bool
CXPointFractal::
resizeEvent()
{
  renderer_->updateSize(getWidth(), getHeight());

  expose();

  return true;
}

void
CXPointFractal::
setForeground(const CRGBA &rgba)
{
  renderer_->setForeground(rgba);
}

void
CXPointFractal::
drawPoint(int x, int y)
{
  renderer_->drawClippedPoint(CIPoint2D(x, y));
}
