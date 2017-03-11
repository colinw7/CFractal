#include <QMainWindow>
#include <CPoint2D.h>
#include <CLine2D.h>
#include <CDisplayRange2D.h>

class QMouseEvent;
class QKeyEvent;
class QPainterPath;

class CQIfsInitiator;
class CQIfsGenerator;
class CQIfsFractal;

class CQIfsExplorer : public QMainWindow {
  Q_OBJECT

 public:
  typedef std::vector<CLine2D> LineList;

 public:
  CQIfsExplorer();

  CQIfsInitiator *getInitiator() const { return initiator_; }
  CQIfsGenerator *getGenerator() const { return generator_; }

  void updateAll();

 private slots:
  void incSlot();
  void decSlot();
  void quitSlot();
  void help();

 private:
  CQIfsInitiator *initiator_;
  CQIfsGenerator *generator_;
  CQIfsFractal   *fractal_;
};

class CQIfsInitiator : public QWidget {
 public:
  typedef CQIfsExplorer::LineList LineList;

 public:
  CQIfsInitiator(CQIfsExplorer *explorer);

  void increment();
  void decrement();

  void getLines(LineList &lines);

 private:
  void updateLines();

  void paintEvent(QPaintEvent *);
  void enterEvent(QEvent *);

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *);

 private:
  CQIfsExplorer   *explorer_;
  uint             sides_;
  LineList         lines_;
  CDisplayRange2D  range_;
  QTransform       t_;
  QTransform       it_;
  bool             pressed_;
  CPoint2D         press_point_;
  CPoint2D         current_point_;
  int              current_ind_;
};

class CQIfsGenerator : public QWidget {
 public:
  typedef CQIfsExplorer::LineList LineList;

 public:
  CQIfsGenerator(CQIfsExplorer *explorer);

  void increment();
  void decrement();

  void getLines(LineList &lines);

 private:
  void updateLines();

  void paintEvent(QPaintEvent *);
  void enterEvent(QEvent *);

  void mousePressEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *);

 private:
  typedef std::vector<CPoint2D> PointList;

  CQIfsExplorer   *explorer_;
  PointList        points_;
  LineList         lines_;
  CDisplayRange2D  range_;
  QTransform       t_;
  QTransform       it_;
  bool             pressed_;
  CPoint2D         press_point_;
  Qt::MouseButton  press_button_;
  CPoint2D         current_point_;
  int              current_ind_;
};

class CQIfsFractal : public QWidget {
 public:
  typedef CQIfsExplorer::LineList LineList;

 public:
  CQIfsFractal(CQIfsExplorer *explorer);

  void increment();
  void decrement();

 private:
  void paintEvent(QPaintEvent *);
  void enterEvent(QEvent *);

  void keyPressEvent(QKeyEvent *);

  void drawGenerator(QPainter *painter, const CLine2D &line, uint depth, const LineList &lines);

 private:
  CQIfsExplorer   *explorer_;
  CDisplayRange2D  range_;
  uint             depth_;
  bool             fill_;
  QPainterPath    *path_;
};
