#include <CQSierpinski.h>
#include <CQWidgetPixelRenderer.h>
#include <CQApp.h>
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQSierpinskiWindow *sierpinski = new CQSierpinskiWindow;

  for (int i = 1; i < argc; ++i) {
    if      (strcmp(argv[1], "-third") == 0)
      sierpinski->setType(CQSierpinski::TYPE_THIRD);
    else if (strcmp(argv[1], "-root") == 0)
      sierpinski->setType(CQSierpinski::TYPE_ROOT);
    else if (strcmp(argv[1], "-box") == 0)
      sierpinski->setType(CQSierpinski::TYPE_BOX);
  }

  sierpinski->show();

  app.exec();

  return 0;
}

//------

CQSierpinskiWindow::
CQSierpinskiWindow()
{
  QHBoxLayout *layout = new QHBoxLayout(this);

  sierpinski_ = new CQSierpinski;

  sierpinski_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

  layout->addWidget(sierpinski_);

  QFrame *control = new QFrame;

  control->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

  layout->addWidget(control);

  QVBoxLayout *controlLayout = new QVBoxLayout(control);

  QPushButton *button1 = new QPushButton("Normal");
  QPushButton *button2 = new QPushButton("Third");
  QPushButton *button3 = new QPushButton("Root");
  QPushButton *button4 = new QPushButton("Box");

  connect(button1, &QPushButton::clicked, [=]() { setType(CQSierpinski::TYPE_NORMAL); });
  connect(button2, &QPushButton::clicked, [=]() { setType(CQSierpinski::TYPE_THIRD ); });
  connect(button3, &QPushButton::clicked, [=]() { setType(CQSierpinski::TYPE_ROOT  ); });
  connect(button4, &QPushButton::clicked, [=]() { setType(CQSierpinski::TYPE_BOX   ); });

  controlLayout->addWidget(button1);
  controlLayout->addWidget(button2);
  controlLayout->addWidget(button3);
  controlLayout->addWidget(button4);
  controlLayout->addStretch(1);

  //---

  resize(600, 600);
}

void
CQSierpinskiWindow::
setType(CSierpinski::Type type)
{
  sierpinski_->setType(type);

  sierpinski_->update();
}

//------

CQSierpinski::
CQSierpinski() :
 QWidget()
{
  renderer_ = new CQWidgetPixelRenderer(this);
}

void
CQSierpinski::
paintEvent(QPaintEvent *)
{
  CQSierpinskiRenderer sr(renderer_);

  renderer_->beginDraw();

  draw(&sr, renderer_->getWidth(), renderer_->getHeight());

  renderer_->endDraw();
}

void
CQSierpinski::
resizeEvent(QResizeEvent *)
{
  renderer_->updateSize(width(), height());
}

//------

void
CQSierpinskiRenderer::
clear(const CRGBA &bg)
{
  renderer_->setBackground(bg);

  renderer_->clear();
}

void
CQSierpinskiRenderer::
drawPoint(const CIPoint2D &p)
{
  renderer_->drawPoint(p);
}

void
CQSierpinskiRenderer::
setForeground(const CRGBA &fg)
{
  renderer_->setForeground(fg);
}

void
CQSierpinskiRenderer::
fillRectangle(const CIBBox2D &bbox)
{
  renderer_->fillRectangle(bbox);
}
