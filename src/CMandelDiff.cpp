#include <CMandelDiff.h>
#include <CMathGen.h>

CMandelDiff::
CMandelDiff()
{
  cr_ = 0.238498;
  ci_ = 0.519198;
}

CMandelDiff *
CMandelDiff::
dup() const
{
  return new CMandelDiff;
}

void
CMandelDiff::
setRange(double xmin, double ymin, double xmax, double ymax)
{
  cr_ = (xmin + xmax)/2;
  ci_ = (ymin + ymax)/2;
}

int
CMandelDiff::
calc(double x, double y, int max_iterations) const
{
  julia_.setC(x, y);

  int iter1 = julia_.iterate(x, y, max_iterations);

  julia_.setC(cr_, ci_);

  int iter2 = julia_.iterate(x, y, max_iterations);

  int color = 0;

  if (iter1 != iter2) {
    int iteration = abs(iter1 - iter2);

    if (iteration < max_iterations)
      color = 254*iteration/(max_iterations - 1) + 1;
  }

  return color;
}
