#ifndef CQDragon_H
#define CQDragon_H

#include <CQPointFractal.h>

class CDragon;
class CDragonCurve;
class CDragonOutline;

class CQDragon : public CQPointFractal {
  Q_OBJECT

 public:
  enum class Type {
    NORMAL,
    CURVE,
  };

 public:
  CQDragon(QWidget *parent = 0, Type type=Type::NORMAL);

  virtual ~CQDragon();

  CDragon *getDragon() const { return dragon_; }

  CDragonCurve *getDragonCurve() const { return dragonCurve_; }

 private:
  Type          type_ { Type::NORMAL };
  CDragon      *dragon_;
  CDragonCurve *dragonCurve_;
};

#endif
