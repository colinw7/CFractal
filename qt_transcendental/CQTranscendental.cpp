#include <CQApp.h>
#include <CQPointFractal.h>
#include <CTranscendental.h>
#include <CStrUtil.h>

class CQTranscendental : public CQPointFractal {
 private:
  CTranscendental *trans_;

 public:
  CQTranscendental();

  void setType(CTranscendental::Type type) {
    trans_->setType(type);
  }
};

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQTranscendental *trans = new CQTranscendental;

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
            trans->setRange(QRectF(xmin, ymin, xmax - xmin, ymax - ymin));
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

  trans->show();

  return app.exec();
}

CQTranscendental::
CQTranscendental() :
 CQPointFractal()
{
  trans_ = new CTranscendental;

  setFractal(trans_);
}
