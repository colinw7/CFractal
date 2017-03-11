#include <CJulia.h>
#include <CXPointFractal.h>

class CXJulia : public CXPointFractal {
 private:
  CJulia *julia_;

 public:
  CXJulia();

  void setC(double cr, double ci) {
    julia_->setC(cr, ci);
  }
};

int
main(int argc, char **argv)
{
  CXJulia *julia = new CXJulia;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (argv[i][1] == 'c') {
        if (i >= argc - 2)
          std::cerr << "Missing values for " << argv[i] << std::endl;
        else {
          double ci, cr;

          if (CStrUtil::toReal(argv[i + 1], &ci) &&
              CStrUtil::toReal(argv[i + 2], &cr))
            julia->setC(ci, cr);
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
            julia->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  julia->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXJulia::
CXJulia() :
 CXPointFractal(julia_ = new CJulia)
{
}
