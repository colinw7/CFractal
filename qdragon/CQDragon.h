#ifndef CQDragon_H
#define CQDragon_H

#include <CQPointFractal.h>

class CDragon;
class CDragonCurve;

class CQDragon : public CQPointFractal {
  Q_OBJECT

 public:
  CQDragon(QWidget *parent = 0, bool curve=false);

  virtual ~CQDragon();

  CDragon *getDragon() const { return dragon_; }

  CDragonCurve *getDragonCurve() const { return dragonCurve_; }

 private:
  CDragon      *dragon_;
  CDragonCurve *dragonCurve_;
};

#endif
