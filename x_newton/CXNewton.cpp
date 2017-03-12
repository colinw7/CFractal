#include <CNewton.h>
#include <CXPointFractal.h>

class CXNewton : public CXPointFractal {
 public:
  CXNewton();
};

static CXNewton *newton = nullptr;

int
main(int, char **)
{
  newton = new CXNewton;

  newton->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXNewton::
CXNewton() :
 CXPointFractal(new CNewton)
{
}
