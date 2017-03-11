#include <CQJulia.h>
#include <CJulia.h>

CQJulia::
CQJulia(QWidget *parent) :
 CQPointFractal(parent)
{
  julia_ = new CJulia;

  setFractal(julia_);
}

CQJulia::
~CQJulia()
{
  delete julia_;
}
