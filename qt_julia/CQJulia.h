#ifndef CQJULIA_H
#define CQJULIA_H

#include <CQPointFractal.h>

class CJulia;

class CQJulia : public CQPointFractal {

 public:
  CQJulia(QWidget *parent = 0);

  virtual ~CQJulia();

  CJulia *getJulia() const { return julia_; }

 private:
  CJulia *julia_;
};

#endif
