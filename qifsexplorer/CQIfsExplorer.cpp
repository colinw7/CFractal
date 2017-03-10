#include <CQIfsExplorer.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <CQUtil.h>

#include <QTabWidget>
#include <QGridLayout>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQIfsExplorer ifs;

  ifs.resize(600, 600);

  ifs.show();

  return app.exec();
}

CQIfsExplorer::
CQIfsExplorer()
{
  QWidget *w = new QWidget;

  setCentralWidget(w);

  QGridLayout *grid = new QGridLayout(w);

  grid->setMargin(1); grid->setSpacing(1);

  initiator_ = new CQIfsInitiator(this);
  generator_ = new CQIfsGenerator(this);
  fractal_   = new CQIfsFractal(this);

  grid->addWidget(initiator_, 0, 0);
  grid->addWidget(generator_, 0, 1);
  grid->addWidget(fractal_  , 1, 0, 2, 2);

  //----

  CQMenu *fileMenu = new CQMenu(this, "&File");

  CQMenuItem *quitItem = new CQMenuItem(fileMenu, "&Quit");

  QObject::connect(quitItem->getAction(), SIGNAL(triggered()), this, SLOT(quitSlot()));

  //----

  CQMenu *viewMenu = new CQMenu(this, "&View");

  CQMenuItem *incItem = new CQMenuItem(viewMenu, "&Increase Depth");
  CQMenuItem *decItem = new CQMenuItem(viewMenu, "&Decrease Depth");

  incItem->setShortcut(QKeySequence(Qt::Key_Plus));
  decItem->setShortcut(QKeySequence(Qt::Key_Minus));

  QObject::connect(incItem->getAction(), SIGNAL(triggered()), this, SLOT(incSlot()));
  QObject::connect(decItem->getAction(), SIGNAL(triggered()), this, SLOT(decSlot()));

  //----

  CQMenu *help_menu = new CQMenu(this, "&Help");

  CQMenuItem *help_item = new CQMenuItem(help_menu, "&Help");

  QObject::connect(help_item->getAction(), SIGNAL(triggered()), this, SLOT(help()));
}

void
CQIfsExplorer::
updateAll()
{
  initiator_->update();
  generator_->update();
  fractal_  ->update();
}

void
CQIfsExplorer::
incSlot()
{
  QWidget *w = qApp->focusWidget();

  if      (w == initiator_)
    initiator_->increment();
  else if (w == generator_)
    generator_->increment();
  else if (w == fractal_)
    fractal_->increment();
}

void
CQIfsExplorer::
decSlot()
{
  QWidget *w = qApp->focusWidget();

  if      (w == initiator_)
    initiator_->decrement();
  else if (w == generator_)
    generator_->decrement();
  else if (w == fractal_)
    fractal_->decrement();
}

void
CQIfsExplorer::
quitSlot()
{
  exit(0);
}

void
CQIfsExplorer::
help()
{
}

CQIfsInitiator::
CQIfsInitiator(CQIfsExplorer *explorer) :
 QWidget(0), explorer_(explorer), sides_(1), current_ind_(0)
{
  setFocusPolicy(Qt::StrongFocus);

  setMouseTracking(true);

  updateLines();
}

void
CQIfsInitiator::
increment()
{
  if (sides_ < 6) {
    ++sides_;

    updateLines();

    explorer_->updateAll();
  }
}

void
CQIfsInitiator::
decrement()
{
  if (sides_ > 1) {
    --sides_;

    updateLines();

    explorer_->updateAll();
  }
}

void
CQIfsInitiator::
getLines(LineList &lines)
{
  lines = lines_;
}

void
CQIfsInitiator::
updateLines()
{
  lines_.clear();

  double da;

  if (sides_ > 2)
    da = 2*M_PI/sides_;
  else
    da = M_PI/sides_;

  double r = 0.8;

  double a1 = 0;

  if (sides_ > 2)
    a1 = M_PI/2.0;

  double x1 = r*cos(a1);
  double y1 = r*sin(a1);

  for (uint i = 0; i < sides_; ++i) {
    double a2 = a1 + da;
    double x2 = r*cos(a2);
    double y2 = r*sin(a2);

    lines_.push_back(CLine2D(CPoint2D(x1, y1), CPoint2D(x2, y2)));

    a1 = a2;
    x1 = x2;
    y1 = y2;
  }
}

void
CQIfsInitiator::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  if (hasFocus())
    painter.fillRect(rect(), QColor(240,240,255));
  else
    painter.fillRect(rect(), QColor(255,255,255));

  painter.setRenderHints(QPainter::Antialiasing);

  range_.setEqualScale(true);

  range_.setPixelRange(0, 0, width() - 1, height() - 1);
  range_.setWindowRange(-1, -1, 1, 1);

  t_  = CQUtil::toQTransform(range_.getMatrix());
  it_ = t_.inverted();

  QPointF p1 = it_.map(QPointF(0, 0));
  QPointF p2 = it_.map(QPointF(1, 1));

  double pixel_size = fabs(p2.x() - p1.x());

  painter.setWorldTransform(t_);

  QPen pen(QColor(0,0,0));

  pen.setWidth(0);
  pen.setCosmetic(false);

  painter.setPen(pen);

  uint num_lines = lines_.size();

  for (uint i = 0; i < num_lines; ++i) {
    const CLine2D &line = lines_[i];

    const CPoint2D &p1 = line.start();
    const CPoint2D &p2 = line.end  ();

    painter.drawLine(QPointF(p1.x, p1.y), QPointF(p2.x, p2.y));
  }

  for (uint i = 0; i <= num_lines; ++i) {
    CPoint2D p;

    if (i < num_lines) {
      const CLine2D &line = lines_[i];

      p = line.start();
    }
    else {
      const CLine2D &line = lines_[i - 1];

      p = line.end();
    }

    if (int(i) == current_ind_)
      pen.setColor(QColor(255,0,0));
    else
      pen.setColor(QColor(0,0,0));

    painter.setPen(pen);

    double x = p.x;
    double y = p.y;

    painter.drawLine(QPointF(x - 3*pixel_size, y), QPointF(x + 3*pixel_size, y));
    painter.drawLine(QPointF(x, y - 3*pixel_size), QPointF(x, y + 3*pixel_size));
  }
}

void
CQIfsInitiator::
enterEvent(QEvent *)
{
  setFocus(Qt::OtherFocusReason);
}

void
CQIfsInitiator::
mousePressEvent(QMouseEvent *event)
{
  pressed_ = true;

  QPointF p = event->pos();
  QPointF w = it_.map(p);

  press_point_ = CPoint2D(w.x(), w.y());
}

void
CQIfsInitiator::
mouseMoveEvent(QMouseEvent *event)
{
  QPointF p = event->pos();
  QPointF w = it_.map(p);

  current_point_ = CPoint2D(w.x(), w.y());

  if (! pressed_) {
    double d = 1E50;
    int    n = -1;

    uint num_lines = lines_.size();

    for (uint i = 0; i < num_lines; ++i) {
      const CLine2D &line = lines_[i];

      const CPoint2D &p1 = line.start();
      const CPoint2D &p2 = line.end  ();

      double dx1 = (p1.x - current_point_.x);
      double dy1 = (p1.y - current_point_.y);

      double d1 = dx1*dx1 + dy1*dy1;

      if (n < 0 || d1 < d) {
        d = d1;
        n = i;
      }

      double dx2 = (p2.x - current_point_.x);
      double dy2 = (p2.y - current_point_.y);

      double d2 = dx2*dx2 + dy2*dy2;

      if (n < 0 || d2 < d) {
        d = d2;
        n = i + 1;
      }
    }

    if (current_ind_ != n) {
      current_ind_ = n;

      update();
    }
  }
  else {
    uint num_lines = lines_.size();

    if (current_ind_ < 0 || current_ind_ > int(num_lines))
      return;

    if      (current_ind_ == 0) {
      lines_[0            ].setStart(current_point_);
      lines_[num_lines - 1].setEnd  (current_point_);
    }
    else if (current_ind_ == int(num_lines)) {
      lines_[num_lines - 1].setEnd  (current_point_);
      lines_[0            ].setStart(current_point_);
    }
    else {
      lines_[current_ind_    ].setStart(current_point_);
      lines_[current_ind_ - 1].setEnd  (current_point_);
    }

    explorer_->updateAll();
  }
}

void
CQIfsInitiator::
mouseReleaseEvent(QMouseEvent *event)
{
  pressed_ = false;

  QPointF p = event->pos();
  QPointF w = it_.map(p);

  current_point_ = CPoint2D(w.x(), w.y());
}

void
CQIfsInitiator::
keyPressEvent(QKeyEvent *)
{
}

//--------------

CQIfsGenerator::
CQIfsGenerator(CQIfsExplorer *explorer) :
 QWidget(0), explorer_(explorer), pressed_(false), current_ind_(-1)
{
  setFocusPolicy(Qt::StrongFocus);

  setMouseTracking(true);

  points_.push_back(CPoint2D(0.0, 0));
  points_.push_back(CPoint2D(1.0, 0));

  updateLines();
}

void
CQIfsGenerator::
increment()
{
  uint num_points = points_.size();

  if (num_points < 16) {
    for (uint i = 0; i < num_points; ++i)
      points_[i].x = points_[i].x*0.9;

    points_.push_back(CPoint2D(1.0, 0));

    updateLines();

    explorer_->updateAll();
  }
}

void
CQIfsGenerator::
decrement()
{
  uint num_points = points_.size();

  if (num_points > 2) {
    points_.pop_back();

    updateLines();

    explorer_->updateAll();
  }
}

void
CQIfsGenerator::
getLines(LineList &lines)
{
  lines = lines_;
}

void
CQIfsGenerator::
updateLines()
{
  uint num_points = points_.size();

#if 0
  double xmin = points_[0].x;
  double xmax = xmin;

  for (uint i = 1; i < num_points; ++i) {
    xmin = std::min(xmin, points_[i].x);
    xmax = std::max(xmax, points_[i].x);
  }

  double xs = xmax - xmin;

  if (xs > 1E-3) {
    for (uint i = 0; i < num_points; ++i)
      points_[i].x = (points_[i].x - xmin)/xs;
  }
  else {
    double dx = 1.0/(num_points - 1);

    for (uint i = 0; i < num_points; ++i)
      points_[i].x = i*dx;
  }
#endif

  lines_.clear();

  for (uint i = 1; i < num_points; ++i) {
    double x1 = points_[i - 1].x;
    double y1 = points_[i - 1].y;
    double x2 = points_[i    ].x;
    double y2 = points_[i    ].y;

    lines_.push_back(CLine2D(CPoint2D(x1, y1), CPoint2D(x2, y2)));
  }
}

void
CQIfsGenerator::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  if (hasFocus())
    painter.fillRect(rect(), QColor(240,240,255));
  else
    painter.fillRect(rect(), QColor(255,255,255));

  painter.setRenderHints(QPainter::Antialiasing);

  range_.setEqualScale(true);

  range_.setPixelRange(0, 0, width() - 1, height() - 1);
  range_.setWindowRange(-0.2, -0.5, 1.2, 0.5);

  t_  = CQUtil::toQTransform(range_.getMatrix());
  it_ = t_.inverted();

  QPointF p1 = it_.map(QPointF(0, 0));
  QPointF p2 = it_.map(QPointF(1, 1));

  double pixel_size = fabs(p2.x() - p1.x());

  painter.setWorldTransform(t_);

  QPen pen(QColor(150,150,255));

  pen.setWidth(0);
  pen.setCosmetic(false);

  painter.setPen(pen);

  painter.drawLine(QPointF(0,0), QPointF(1,0));

  pen.setColor(QColor(0,0,0));

  painter.setPen(pen);

  uint num_lines = lines_.size();

  for (uint i = 0; i < num_lines; ++i) {
    const CLine2D &line = lines_[i];

    const CPoint2D &p1 = line.start();
    const CPoint2D &p2 = line.end  ();

    painter.drawLine(QPointF(p1.x, p1.y), QPointF(p2.x, p2.y));
  }

  for (uint i = 0; i <= num_lines; ++i) {
    CPoint2D p;

    if (i < num_lines) {
      const CLine2D &line = lines_[i];

      p = line.start();
    }
    else {
      const CLine2D &line = lines_[i - 1];

      p = line.end();
    }

    if (int(i) == current_ind_)
      pen.setColor(QColor(255,0,0));
    else
      pen.setColor(QColor(0,0,0));

    painter.setPen(pen);

    double x = p.x;
    double y = p.y;

    painter.drawLine(QPointF(x - 3*pixel_size, y), QPointF(x + 3*pixel_size, y));
    painter.drawLine(QPointF(x, y - 3*pixel_size), QPointF(x, y + 3*pixel_size));
  }
}

void
CQIfsGenerator::
enterEvent(QEvent *)
{
  setFocus(Qt::OtherFocusReason);
}

void
CQIfsGenerator::
mousePressEvent(QMouseEvent *event)
{
  pressed_ = true;

  QPointF p = event->pos();
  QPointF w = it_.map(p);

  press_point_  = CPoint2D(w.x(), w.y());
  press_button_ = event->button();
}

void
CQIfsGenerator::
mouseMoveEvent(QMouseEvent *event)
{
  QPointF p = event->pos();
  QPointF w = it_.map(p);

  current_point_ = CPoint2D(w.x(), w.y());

  if (! pressed_) {
    double d = 1E50;
    int    n = -1;

    uint num_points = points_.size();

    for (uint i = 0; i < num_points; ++i) {
      double x = points_[i].x;
      double y = points_[i].y;

      double dx = (x - current_point_.x);
      double dy = (y - current_point_.y);

      double d1 = dx*dx + dy*dy;

      if (n < 0 || d1 < d) {
        d = d1;
        n = i;
      }
    }

    if (current_ind_ != n) {
      current_ind_ = n;

      update();
    }
  }
  else {
    if (press_button_ == Qt::LeftButton) {
      uint num_points = points_.size();

      if (current_ind_ < 0 || current_ind_ >= int(num_points))
        return;

      CPoint2D p = current_point_;

      p.x = int(p.x/0.01 + 0.5)*0.01;
      p.y = int(p.y/0.01 + 0.5)*0.01;

      p.x = std::min(std::max(p.x, 0.0), 1.0);

      points_[current_ind_] = p;

      updateLines();

      explorer_->updateAll();
    }
  }
}

void
CQIfsGenerator::
mouseReleaseEvent(QMouseEvent *event)
{
  pressed_ = false;

  QPointF p = event->pos();
  QPointF w = it_.map(p);

  current_point_ = CPoint2D(w.x(), w.y());

  if (press_button_ == Qt::MidButton) {
    uint num_points = points_.size();

    if (current_ind_ < 0 || current_ind_ >= int(num_points))
      return;

    CPoint2D p = current_point_;

    p.x = int(p.x/0.01 + 0.5)*0.01;
    p.y = int(p.y/0.01 + 0.5)*0.01;

    p.x = std::min(std::max(p.x, 0.0), 1.0);

    points_.push_back(p);

    if (current_ind_ == int(num_points) - 1)
      --current_ind_;

    for (int i = num_points - 1; i > current_ind_; --i)
      points_[i + 1] = points_[i];

    points_[current_ind_ + 1] = p;

    updateLines();

    explorer_->updateAll();
  }
}

void
CQIfsGenerator::
keyPressEvent(QKeyEvent *)
{
}

//--------------

CQIfsFractal::
CQIfsFractal(CQIfsExplorer *explorer) :
 QWidget(0), explorer_(explorer), depth_(1), fill_(false), path_(0)
{
  setFocusPolicy(Qt::StrongFocus);
}

void
CQIfsFractal::
increment()
{
  if (depth_ < 8) {
    ++depth_;

    update();
  }
}

void
CQIfsFractal::
decrement()
{
  if (depth_ > 1) {
    --depth_;

    update();
  }
}

void
CQIfsFractal::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  if (hasFocus())
    painter.fillRect(rect(), QColor(240,240,255));
  else
    painter.fillRect(rect(), QColor(255,255,255));

  painter.setRenderHints(QPainter::Antialiasing);

  range_.setEqualScale(true);

  range_.setPixelRange(0, 0, width() - 1, height() - 1);
  range_.setWindowRange(-1, -1, 1, 1);

  QTransform t = CQUtil::toQTransform(range_.getMatrix());

  painter.setWorldTransform(t);

  QPen pen(QColor(0,0,0));

  pen.setWidth(0);
  pen.setCosmetic(false);

  painter.setPen(pen);

  if (fill_)
    path_ = new QPainterPath;
  else
    path_ = 0;

  //------

  CQIfsInitiator *initiator = explorer_->getInitiator();
  CQIfsGenerator *generator = explorer_->getGenerator();

  LineList ilines, glines;

  initiator->getLines(ilines);
  generator->getLines(glines);

  uint num_ilines = ilines.size();

  for (uint i = 0; i < num_ilines; ++i) {
    drawGenerator(&painter, ilines[i], depth_ - 1, glines);
  }

  if (path_) {
    QBrush brush(QColor(255,200,200));

    painter.fillPath(*path_, brush);

    QPen pen(QColor(0,0,0));

    pen.setWidth(0);
    pen.setCosmetic(false);

    painter.strokePath(*path_, pen);
  }

  delete path_;
}

void
CQIfsFractal::
enterEvent(QEvent *)
{
  setFocus(Qt::OtherFocusReason);
}

void
CQIfsFractal::
keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_F) {
    fill_ = ! fill_;

    update();
  }
}

void
CQIfsFractal::
drawGenerator(QPainter *painter, const CLine2D &line, uint depth, const LineList &lines)
{
  const CPoint2D &p1 = line.start();
  const CPoint2D &p2 = line.end  ();

  if (depth == 0) {
    if (fill_) {
      if (path_->length() == 0)
        path_->moveTo(QPointF(p1.x, p1.y));

      path_->lineTo(QPointF(p2.x, p2.y));
    }
    else
      painter->drawLine(QPointF(p1.x, p1.y), QPointF(p2.x, p2.y));
  }
  else {
    double x1 = p1.x;
    double y1 = p1.y;
    double x2 = p2.x;
    double y2 = p2.y;

    //if (x1 > x2) { std::swap(x1, x2); std::swap(y1, y2); }

    double dx = x2 - x1;
    double dy = y2 - y1;

    double l = sqrt(dx*dx + dy*dy);

    double s = dy/l;
    double c = dx/l;

    uint num_lines = lines.size();

    for (uint i = 0; i < num_lines; ++i) {
      const CLine2D &line1 = lines[i];

      const CPoint2D &pl1 = line1.start();
      const CPoint2D &pl2 = line1.end  ();

      CPoint2D pr1, pr2;

      pr1.x = x1 + l*pl1.x*c - l*pl1.y*s;
      pr1.y = y1 + l*pl1.x*s + l*pl1.y*c;

      pr2.x = x1 + l*pl2.x*c - l*pl2.y*s;
      pr2.y = y1 + l*pl2.x*s + l*pl2.y*c;

      drawGenerator(painter, CLine2D(pr1, pr2), depth - 1, lines);
    }
  }
}
