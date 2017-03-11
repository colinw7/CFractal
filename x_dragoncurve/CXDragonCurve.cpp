#include <CDragonCurve.h>
#include <CXPointFractal.h>

class CXDragonCurve : public CXPointFractal {
 private:
  CDragonCurve *dragon_;

 public:
  CXDragonCurve();

  void setParams(double p, double q);
};

static CXDragonCurve *dragon = NULL;

int
main(int argc, char **argv)
{
  dragon = new CXDragonCurve;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (argv[i][1] == 'c') {
        if (i >= argc - 2)
          std::cerr << "Missing values for " << argv[i] << std::endl;
        else {
          double p, q;

          if (CStrUtil::toReal(argv[i + 1], &p) &&
              CStrUtil::toReal(argv[i + 2], &q))
            dragon->setParams(p, q);
        }

        i += 2;
      }
      else if (argv[i][1] == 'r') {
        if (i >= argc - 4)
          std::cerr << "Missing values for " << argv[i] << std::endl;
        else {
          double xmin, ymin, xmax, ymax;

          if (CStrUtil::toReal(argv[i + 1], &xmin) &&
              CStrUtil::toReal(argv[i + 2], &ymin) &&
              CStrUtil::toReal(argv[i + 3], &xmax) &&
              CStrUtil::toReal(argv[i + 4], &ymax)) {
            dragon->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  dragon->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXDragonCurve::
CXDragonCurve() :
 CXPointFractal(dragon_ = new CDragonCurve)
{
}

void
CXDragonCurve::
setParams(double p, double q)
{
  dragon_->setParams(p, q);
}
