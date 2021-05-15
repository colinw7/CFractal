#include <CCircles.h>
#include <CRGBName.h>
#include <cmath>

CCircles::NamedColor
CCircles::colors[] = {
  NamedColor("red"           ),
  NamedColor("green"         ),
  NamedColor("blue"          ),
  NamedColor("cyan"          ),
  NamedColor("magenta"       ),
  NamedColor("yellow"        ),
  NamedColor("orange"        ),
  NamedColor("brown"         ),
  NamedColor("grey50"        ),
  NamedColor("pink"          ),
  NamedColor("mauve"         ),
  NamedColor("darkgreen"     ),
  NamedColor("lightblue"     ),
  NamedColor("lime"          ),
  NamedColor("lightsteelblue"),
  NamedColor("ochre"         ),
};

CCircles::
CCircles()
{
  canvas_xmin = -2000.0;
  canvas_ymin = -2000.0;
  canvas_xmax =  2000.0;
  canvas_ymax =  2000.0;

  canvas_color  = 1;
  circles_depth = 6;
}

void
CCircles::
draw()
{
  setDataRange(canvas_xmin, canvas_ymin, canvas_xmax, canvas_ymax);

  double xa =  -725.0;
  double ya =   235.0;
  double ra =   625.0;

  double xb =   275.0;
  double yb =   268.0;
  double rb =   375.0;

  double xc =   180.0;
  double yc = -1048.0;
  double rc =   945.0;

  generateCircle(xa, ya, ra, xb, yb, rb, xc, yc, rc, circles_depth);

  canvas_color = 1;

  setForeground(CRGBName::toRGBA(colors[canvas_color].name));

  drawCircle(xa, ya, ra);
  drawCircle(xb, yb, rb);
  drawCircle(xc, yc, rc);
}

void
CCircles::
generateCircle(double xa, double ya, double ra,
               double xb, double yb, double rb,
               double xc, double yc, double rc, int depth)
{
  depth--;

  double rs = 1.0/ra + 1.0/rb + 1.0/rc +
              2.0*sqrt(1.0/(rb*rc) + 1.0/(rc*ra) + 1.0/(ra*rb));

  rs = 1.0/rs;

  double xs, ys;

  if (xb == xa) {
    double temp = (rs + ra)*(rs + ra) - (rs + rc)*(rs + rc) -
                  xa*xa + xc*xc - ya*ya + yc*yc;

    ys = ((xb - xa)*temp -
          (xc - xa)*((rs + ra)*(rs + ra) - (rs + rb)*(rs + rb) -
                     xa*xa + xb*xb - ya*ya + yb*yb))/
         (2.0*((yc - ya)*(xb - xa) - (yb - ya)*(xc - xa)));
    xs = (temp - 2*ys*(yc - ya))/(2.0*(xc - xa));
  }
  else {
    double temp = (rs + ra)*(rs + ra) - (rs + rb)*(rs + rb) -
                  xa*xa + xb*xb - ya*ya + yb*yb;

    ys = ((xc - xa)*temp -
          (xb - xa)*((rs + ra)*(rs + ra) - (rs + rc)*(rs + rc) -
                     xa*xa + xc*xc - ya*ya + yc*yc))/
         (2.0*((yb - ya)*(xc - xa) - (yc - ya)*(xb - xa)));
    xs = (temp - 2*ys*(yb - ya))/(2.0*(xb - xa));
  }

  if (depth > 0) {
    generateCircle(xa, ya, ra, xb, yb, rb, xs, ys, rs, depth);
    generateCircle(xb, yb, rb, xc, yc, rc, xs, ys, rs, depth);
    generateCircle(xc, yc, rc, xa, ya, ra, xs, ys, rs, depth);
  }

  canvas_color = (circles_depth - depth + 1) % MAX_COLORS;

  setForeground(CRGBName::toRGBA(colors[canvas_color].name));

  fillCircle(xs, ys, rs);
}
