#include <CQNewton.h>
#include <CNewton.h>

CQNewton::
CQNewton(QWidget *parent) :
 CQPointFractal(parent)
{
  newton_ = new CNewton;

  setFractal(newton_);
}

CQNewton::
~CQNewton()
{
  delete newton_;
}
