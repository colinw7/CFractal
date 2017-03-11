#include <CMandelDiff.h>
#include <CXPointFractal.h>

class CXMandelDiff : public CXPointFractal {
 private:
  CMandelDiff *mandel_;

 public:
  CXMandelDiff();

  void setC(double cr, double ci) {
    mandel_->setC(cr, ci);
  }
};

static CXMandelDiff *mandelDiff = NULL;

int
main(int argc, char **argv)
{
  mandelDiff = new CXMandelDiff;

  if (argc == 7) {
    double xmin, ymin, xmax, ymax, ci, cr;

    if (CStrUtil::toReal(argv[1], &xmin) &&
        CStrUtil::toReal(argv[2], &ymin) &&
        CStrUtil::toReal(argv[3], &xmax) &&
        CStrUtil::toReal(argv[4], &ymax) &&
        CStrUtil::toReal(argv[5], &ci) &&
        CStrUtil::toReal(argv[6], &cr)) {
      mandelDiff->setC(ci, cr);

      mandelDiff->setRange(xmin, ymin, xmax, ymax);
    }
  }

  mandelDiff->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXMandelDiff::
CXMandelDiff() :
 CXPointFractal(mandel_ = new CMandelDiff)
{
}
