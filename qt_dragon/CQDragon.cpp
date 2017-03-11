#include <CQDragon.h>
#include <CDragon.h>
#include <CDragonCurve.h>

CQDragon::
CQDragon(QWidget *parent, Type type) :
 CQPointFractal(parent), type_(type)
{
  dragon_      = new CDragon;
  dragonCurve_ = new CDragonCurve;

  if      (type_ == Type::NORMAL)
    setFractal(dragon_);
  else if (type_ == Type::CURVE)
    setFractal(dragonCurve_);
}

CQDragon::
~CQDragon()
{
  delete dragon_;
  delete dragonCurve_;
}
