#include <QWidget>
#include <QImage>
#include <QPointF>

class CQLinear : public QWidget {
  Q_OBJECT

 public:
  CQLinear();

 private:
  void paintEvent(QPaintEvent *);

  void linear();

 private slots:
  void tickSlot();

 private:
  QImage image_;
  double t_;
  double dt_;
};
