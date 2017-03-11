#include <CIfs.h>
#include <CXLib.h>
#include <CXLibRenderer2D.h>
#include <CTurtle2D.h>

class CXIfs : public CXWindow {
 private:
  CXLibRenderer2D *renderer_;
  CTurtle2D       *turtle_;
  CIfs            *ifs_;

 public:
  CXIfs(int width, int height);

  void setDebug() { ifs_->setDebug(); }

  void setDepth(uint depth) { ifs_->setDepth(depth); }

  void readFile(const std::string &fileName);

  bool exposeEvent();

  bool resizeEvent();

  bool keyPressEvent(const CKeyEvent &event);
};

int
main(int argc, char **argv)
{
  CXIfs *ifs = new CXIfs(400, 400);

  ifs->map();

  std::string filename;

  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] == '-') {
      if      (strcmp(&argv[i][1], "debug") == 0)
        ifs->setDebug();
      else if (strcmp(&argv[i][1], "depth") == 0) {
        if (i < argc - 1)
          ifs->setDepth(CStrUtil::toInteger(argv[++i]));
        else
          std::cerr << "Missing value for depth" << std::endl;
      }
      else
        std::cerr << "Invalid option " << argv[i] << std::endl;
    }
    else
      filename = argv[i];
  }

  if (filename != "")
    ifs->readFile(filename);

  CXMachineInst->mainLoop();

  return 0;
}

CXIfs::
CXIfs(int width, int height) :
 CXWindow(width, height)
{
  renderer_ = new CXLibRenderer2D(this);

  turtle_ = new CTurtle2D(renderer_);

  ifs_ = new CIfs(turtle_);

  renderer_->setDataRange(0, 0, 100, 100);
}

void
CXIfs::
readFile(const std::string &fileName)
{
  ifs_->readFile(fileName);
}

bool
CXIfs::
exposeEvent()
{
  renderer_->resetDataRange();

  renderer_->setBackground(CRGB(1,1,1));
  renderer_->setForeground(CRGB(0,0,0));

  renderer_->setLineWidth(0);

  renderer_->clear();

  std::string title = ifs_->getName();

  title += " (Depth " + CStrUtil::toString(ifs_->getDepth()) + ")";

  setWindowTitle(title);

  ifs_->redraw();

  return true;
}

bool
CXIfs::
resizeEvent()
{
  renderer_->updateSize(100, 100);

  return true;
}

bool
CXIfs::
keyPressEvent(const CKeyEvent &event)
{
  if      (event.isType(CKEY_TYPE_Plus)) {
    ifs_->increaseDepth();

    expose();
  }
  else if (event.isType(CKEY_TYPE_Minus)) {
    ifs_->decreaseDepth();

    expose();
  }
  else if (event.isType(CKEY_TYPE_g)) {
    ifs_->setShowGenerator(! ifs_->getShowGenerator());

    expose();
  }

  return true;
}
