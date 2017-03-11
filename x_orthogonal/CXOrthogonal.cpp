#include <COrthogonal.h>
#include <CXPointFractal.h>

class CXOrthogonal : public CXPointFractal {
 private:
  COrthogonal *ortho_;

 public:
  CXOrthogonal();

  void setType(COrthogonal::Type type) {
    ortho_->setType(type);
  }
};

int
main(int argc, char **argv)
{
  CXOrthogonal *ortho = new CXOrthogonal;

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
            ortho->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
      else if (strcmp(&argv[i][1], "t5") == 0) {
        ortho->setType(COrthogonal::T5);
      }
      else if (strcmp(&argv[i][1], "c6") == 0) {
        ortho->setType(COrthogonal::C6);
      }
      else if (strcmp(&argv[i][1], "p4") == 0) {
        ortho->setType(COrthogonal::P4);
      }
      else if (strcmp(&argv[i][1], "p6") == 0) {
        ortho->setType(COrthogonal::P6);
      }
      else if (strcmp(&argv[i][1], "l4") == 0) {
        ortho->setType(COrthogonal::L4);
      }
      else if (strcmp(&argv[i][1], "h4") == 0) {
        ortho->setType(COrthogonal::H4);
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  ortho->resetRange();

  ortho->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXOrthogonal::
CXOrthogonal() :
 CXPointFractal(ortho_ = new COrthogonal)
{
}
