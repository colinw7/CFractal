#ifndef CQBARNSLEY_H
#define CQBARNSLEY_H

#include <CQPointFractal.h>

class CBarnsley;

class CQBarnsley : public CQPointFractal {
 private:
  CBarnsley *barnsley_;

 public:
  CQBarnsley(QWidget *parent = 0);

  virtual ~CQBarnsley();

  CBarnsley *getBarnsley() const { return barnsley_; }
};

#endif
