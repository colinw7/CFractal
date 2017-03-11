#include <CQBarnsley.h>
#include <CBarnsley.h>

CQBarnsley::
CQBarnsley(QWidget *parent) :
 CQPointFractal(parent)
{
  barnsley_ = new CBarnsley;

  setFractal(barnsley_);
}

CQBarnsley::
~CQBarnsley()
{
  delete barnsley_;
}
