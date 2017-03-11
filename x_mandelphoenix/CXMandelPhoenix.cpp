#include <CMandelPhoenix.h>
#include <CXPointFractal.h>

class CXMandelPhoenix : public CXPointFractal {
 private:
  CMandelPhoenix *phoenix_;

 public:
  CXMandelPhoenix();
};

static CXMandelPhoenix *phoenix = NULL;

int
main(int, char **)
{
  phoenix = new CXMandelPhoenix;

  phoenix->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXMandelPhoenix::
CXMandelPhoenix() :
 CXPointFractal(phoenix_ = new CMandelPhoenix)
{
}
