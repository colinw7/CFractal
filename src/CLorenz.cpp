#include <CLorenz.h>
#include <CRenderer2D.h>
#include <CRGBName.h>

CLorenz::
CLorenz(CRenderer2D *renderer) :
 renderer_    (renderer),
 color_num_   (0),
 display_type_(XY_PLANE),
 x_angle_     ( 0.0),
 y_angle_     (90.0),
 z_angle_     (45.0)
{
  addColors();
}

void
CLorenz::
addColors()
{
  addColor(CRGBName::toRGBA("green"         ));
  addColor(CRGBName::toRGBA("blue"          ));
  addColor(CRGBName::toRGBA("cyan"          ));
  addColor(CRGBName::toRGBA("magenta"       ));
  addColor(CRGBName::toRGBA("yellow"        ));
  addColor(CRGBName::toRGBA("orange"        ));
  addColor(CRGBName::toRGBA("brown"         ));
  addColor(CRGBName::toRGBA("grey50"        ));
  addColor(CRGBName::toRGBA("pink"          ));
  addColor(CRGBName::toRGBA("purple"        ));
  addColor(CRGBName::toRGBA("darkgreen"     ));
  addColor(CRGBName::toRGBA("lightblue"     ));
  addColor(CRGBName::toRGBA("seagreen"      ));
  addColor(CRGBName::toRGBA("lightsteelblue"));
  addColor(CRGBName::toRGBA("tan"           ));
  addColor(CRGBName::toRGBA("black"         ));
  addColor(CRGBName::toRGBA("white"         ));
}

void
CLorenz::
addColor(const CRGBA &rgb)
{
  colors_.push_back(rgb);
}

void
CLorenz::
nextColor()
{
  ++color_num_;

  if (color_num_ > (int) colors_.size())
    color_num_ = 0;
}

void
CLorenz::
draw()
{
  color_num_ = 0;

  //------------

  if (display_type_ == XYZ_PROJECTION) {
    sx_ = sin(x_angle_);
    sy_ = sin(y_angle_);
    sz_ = sin(z_angle_);

    cx_ = cos(x_angle_);
    cy_ = cos(y_angle_);
    cz_ = cos(z_angle_);
  }

  x1_ = 0.0; y1_ = 0.0;
  x2_ = 0.0; y2_ = 0.0;

  //------------

  CLorenzCalc::draw();
}

void
CLorenz::
drawPoint(double x, double y, double z)
{
  if      (display_type_ == XY_PLANE) {
    x2_ = x;
    y2_ = y;

    if (x1_*x2_ < 0)
      nextColor();
  }
  else if (display_type_ == XZ_PLANE) {
    x2_ = x;
    y2_ = z;

    if (x1_*x2_ < 0)
      nextColor();
  }
  else if (display_type_ == YZ_PLANE) {
    x2_ = y;
    y2_ = z;

    if (x1_*x2_ < 0)
      nextColor();
  }
  else if (display_type_ == XYZ_PROJECTION) {
    x2_ = x*cx_ + y*cy_ + z*cz_;
    y2_ = x*sx_ + y*sy_ + z*sz_;

    if (x1_*x2_ < 0)
      nextColor();
  }

  renderer_->setForeground(colors_[color_num_]);

  renderer_->drawLine(CPoint2D(x1_, y1_), CPoint2D(x2_, y2_));

  x1_ = x2_;
  y1_ = y2_;
}
