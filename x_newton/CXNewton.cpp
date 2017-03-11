#include <CNewton.h>
#include <CXPointFractal.h>

class CXNewton : public CXPointFractal {
 public:
  CXNewton();
};

static CXNewton *julia = NULL;

int
main(int, char **)
{
  julia = new CXNewton;

  julia->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXNewton::
CXNewton() :
 CXPointFractal(new CNewton)
{
}
