#ifndef CQNewton_H
#define CQNewton_H

#include <CQPointFractal.h>

class CNewton;

class CQNewton : public CQPointFractal {
  Q_OBJECT

 public:
  CQNewton(QWidget *parent = 0);

  virtual ~CQNewton();

  CNewton *getNewton() const { return newton_; }

 private:
  CNewton *newton_;
};

#endif
