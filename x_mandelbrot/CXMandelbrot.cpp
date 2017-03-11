#include <CMandelbrot.h>
#include <CXPointFractal.h>

class CXMandelbrot : public CXPointFractal {
 private:
  CMandelbrot *mandelbrot_;

 public:
  CXMandelbrot();

  void setDistance(bool distance) {
    mandelbrot_->setDistance(distance);
  }
};

static CXMandelbrot *mandelbrot = NULL;

int
main(int argc, char **argv)
{
  mandelbrot = new CXMandelbrot;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (argv[i][1] == 'r') {
        if (i >= argc - 4)
          std::cerr << "Missing values for " << argv[i] << std::endl;
        else {
          double xmin, ymin, xmax, ymax;

          if (CStrUtil::toReal(argv[i + 1], &xmin) &&
              CStrUtil::toReal(argv[i + 2], &ymin) &&
              CStrUtil::toReal(argv[i + 3], &xmax) &&
              CStrUtil::toReal(argv[i + 4], &ymax)) {
            mandelbrot->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
      else if (strcmp(&argv[i][1], "distance") == 0) {
        mandelbrot->setDistance(true);
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  mandelbrot->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXMandelbrot::
CXMandelbrot() :
 CXPointFractal(mandelbrot_ = new CMandelbrot)
{
}
