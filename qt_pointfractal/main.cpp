#include <CQApp.h>
#include <CQPointFractalTest.h>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQPointFractalTest fractal;

  fractal.show();

  return app.exec();
}
