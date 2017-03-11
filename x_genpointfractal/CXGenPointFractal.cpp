#include <CGenPointFractal.h>
#include <CXPointFractal.h>

class CXGenPointFractal : public CXPointFractal {
 private:
  CGenPointFractal *fractal_;

 public:
  CXGenPointFractal();

  void mandelbrot() { fractal_->mandelbrot(); }
  void julia() { fractal_->julia(); }
  void dragon() { fractal_->dragon(); }
  void dragonSet() { fractal_->dragonSet(); }

  void setParams(double p, double q);
};

int
main(int argc, char **argv)
{
  CXGenPointFractal *fractal = new CXGenPointFractal;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (argv[i][1] == 'c') {
        if (i >= argc - 2)
          std::cerr << "Missing values for " << argv[i] << std::endl;
        else {
          double p, q;

          if (CStrUtil::toReal(argv[i + 1], &p) &&
              CStrUtil::toReal(argv[i + 2], &q))
            fractal->setParams(p, q);
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
            fractal->setRange(xmin, ymin, xmax, ymax);
          }
        }

        i += 4;
      }
      else if (strcmp(&argv[i][1], "mandelbrot") == 0) {
        fractal->mandelbrot();
      }
      else if (strcmp(&argv[i][1], "julia") == 0) {
        fractal->julia();
      }
      else if (strcmp(&argv[i][1], "dragon") == 0) {
        fractal->dragon();
      }
      else if (strcmp(&argv[i][1], "dragon_set") == 0) {
        fractal->dragonSet();
      }
    }
    else
      std::cerr << "Invalid argument " << argv[i] << std::endl;
  }

  fractal->resetRange();

  fractal->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXGenPointFractal::
CXGenPointFractal() :
 CXPointFractal(fractal_ = new CGenPointFractal)
{
}

void
CXGenPointFractal::
setParams(double, double)
{
  //fractal_->setParams(p, q);
}
