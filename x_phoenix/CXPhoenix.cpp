#include <CPhoenix.h>
#include <CXPointFractal.h>

class CXPhoenix : public CXPointFractal {
 private:
  CPhoenix *phoenix_;

 public:
  CXPhoenix();

  void setParams(double p, double q);
};

static CXPhoenix *phoenix = NULL;

int
main(int argc, char **argv)
{
  phoenix = new CXPhoenix;

  if (argc == 3) {
    double p, q;

    if (CStrUtil::toReal(argv[1], &p) &&
        CStrUtil::toReal(argv[2], &q))
      phoenix->setParams(p, q);
  }

  phoenix->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXPhoenix::
CXPhoenix() :
 CXPointFractal(phoenix_ = new CPhoenix)
{
}

void
CXPhoenix::
setParams(double p, double q)
{
  phoenix_->setParams(p, q);
}
