#include <CBarnsley.h>
#include <CXPointFractal.h>

class CXBarnsley : public CXPointFractal {
 private:
  CBarnsley *barnsley_;

 public:
  CXBarnsley();

  void setType(CBarnsley::Type type) {
    barnsley_->setType(type);
  }
};

int
main(int argc, char **argv)
{
  CXBarnsley *barnsley = new CXBarnsley;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 'r') {
        if (i >= argc - 4)
          std::cerr << "Missing values for " << argv[i] << std::endl;
        else {
          double xmin, ymin, xmax, ymax;

          if (CStrUtil::toReal(argv[i + 1], &xmin) &&
              CStrUtil::toReal(argv[i + 2], &ymin) &&
              CStrUtil::toReal(argv[i + 3], &xmax) &&
              CStrUtil::toReal(argv[i + 4], &ymax)) {
            barnsley->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
      else if (strcmp(&argv[i][1], "1") == 0) {
        barnsley->setType(CBarnsley::B1);
      }
      else if (strcmp(&argv[i][1], "2") == 0) {
        barnsley->setType(CBarnsley::B2);
      }
      else if (strcmp(&argv[i][1], "3") == 0) {
        barnsley->setType(CBarnsley::B3);
      }
      else if (strcmp(&argv[i][1], "4") == 0) {
        barnsley->setType(CBarnsley::B4);
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  barnsley->resetRange();

  barnsley->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXBarnsley::
CXBarnsley() :
 CXPointFractal(barnsley_ = new CBarnsley)
{
}
