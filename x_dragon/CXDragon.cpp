#include <CDragon.h>
#include <CXPointFractal.h>

class CXDragon : public CXPointFractal {
 public:
  CXDragon();
};

static CXDragon *dragon = NULL;

int
main(int, char **)
{
  dragon = new CXDragon;

  dragon->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXDragon::
CXDragon() :
 CXPointFractal(new CDragon)
{
}
