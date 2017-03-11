#include <CTranscendental.h>
#include <CXPointFractal.h>

class CXTranscendental : public CXPointFractal {
 private:
  CTranscendental *trans_;

 public:
  CXTranscendental();

  void setType(CTranscendental::Type type) {
    trans_->setType(type);
  }
};

int
main(int argc, char **argv)
{
  CXTranscendental *trans = new CXTranscendental;

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
            trans->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
      else if (strcmp(&argv[i][1], "sin") == 0) {
        trans->setType(CTranscendental::SIN);
      }
      else if (strcmp(&argv[i][1], "cos") == 0) {
        trans->setType(CTranscendental::COS);
      }
      else if (strcmp(&argv[i][1], "exp") == 0) {
        trans->setType(CTranscendental::EXP);
      }
      else if (strcmp(&argv[i][1], "sinh") == 0) {
        trans->setType(CTranscendental::SINH);
      }
      else if (strcmp(&argv[i][1], "cosh") == 0) {
        trans->setType(CTranscendental::COSH);
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  trans->resetRange();

  trans->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXTranscendental::
CXTranscendental() :
 CXPointFractal(trans_ = new CTranscendental)
{
}
