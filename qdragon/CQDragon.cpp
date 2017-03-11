#include <CQDragon.h>
#include <CDragon.h>
#include <CDragonCurve.h>

CQDragon::
CQDragon(QWidget *parent, bool curve) :
 CQPointFractal(parent)
{
  dragon_      = new CDragon;
  dragonCurve_ = new CDragonCurve;

  if (! curve)
    setFractal(dragon_);
  else
    setFractal(dragonCurve_);
}

CQDragon::
~CQDragon()
{
  delete dragon_;
  delete dragonCurve_;
}
