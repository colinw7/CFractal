#include <CBifuricationLib.h>
#include <CXLib.h>

class CXBifurication : public CXWindow, public CBifurication {
 public:
  CXBifurication(int width, int height);

  void setFeigenbaum(bool feigenbaum);

  bool exposeEvent();
  bool resizeEvent();

  void drawPoint(int x, int y);
};

int
main(int argc, char **argv)
{
  bool feigenbaum = false;

  if (argc > 1 && strcmp(argv[1], "-feigenbaum") == 0)
    feigenbaum = true;

  CXBifurication *bifurication = new CXBifurication(600, 600);

  bifurication->setFeigenbaum(feigenbaum);

  bifurication->map();

  CXMachineInst->mainLoop();

  return 0;
}

CXBifurication::
CXBifurication(int width, int height) :
 CXWindow(width, height)
{
}

void
CXBifurication::
setFeigenbaum(bool feigenbaum)
{
  CBifurication::setFeigenbaum(feigenbaum);
}

bool
CXBifurication::
exposeEvent()
{
  clear();

  CBifurication::draw(CXWindow::getWidth(), CXWindow::getHeight());

  return true;
}

bool
CXBifurication::
resizeEvent()
{
  return true;
}

void
CXBifurication::
drawPoint(int x, int y)
{
  CXWindow::drawPoint(x, y);
}
