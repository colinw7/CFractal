#include <QWidget>
#include <QImage>
#include <QPointF>

#include <RGB.h>
#include <IPoint.h>
#include <Point.h>

class CQFlower : public QWidget {
  Q_OBJECT

 public:
  enum Mode {
    FLOWER_MODE,
    HEART_MODE,
    PLASMA_MODE,
    MONJORI_MODE,
    METABLOB_MODE,
    CRYSTALS_MODE,
    NOISE_MODE
  };

 public:
  CQFlower();

 private:
  void paintEvent(QPaintEvent *);

  void contextMenuEvent(QContextMenuEvent *);

  void flower();
  void heart();
  void plasma();
  void monjori();
  void metablob();
  void quasi_crystals();
  void noise();

  double dot(const Point &p1, const Point &p2);
  double dotSelf(const Point &p);

 private slots:
  void menuActionSlot(QAction *);

  void tickSlot();

 private:
  Mode   mode_;
  QImage image_;
  double t_;
  double dt_;
};
