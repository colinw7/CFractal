#ifndef CDRAW_TREE_H
#define CDRAW_TREE_H

#include <CRGBA.h>

class CTurtle;

class CDrawTree {
 protected:
  enum { MAX_COLOURS = 16 };

  struct Line {
    double  x1;
    double  y1;
    double  x2;
    double  y2;
    double  width;
    Line   *left;
    Line   *right;
  };

 public:
  CDrawTree();

  virtual ~CDrawTree() { }

  bool read(const std::string &filename);

  void    draw();
  void    add_branch(Line *, double, double, int);
  Line   *new_line(double, double, double);
  double  line_angle(double, double, double, double);
  void    draw_line(Line *, int);
  void    set_color(int);

  virtual void setDataRange(double xmin, double ymin, double xmax, double ymax) = 0;

  virtual void setForeground(const CRGBA &rgba) = 0;

  virtual void setLineWidth(double width) = 0;

  virtual void drawLine(double x1, double y1, double x2, double y2) = 0;

 protected:
  static const char *colors_[];

  CTurtle *turtle_;

  double canvas_xmin_;
  double canvas_ymin_;
  double canvas_xmax_;
  double canvas_ymax_;

  double   tree_height_;
  double   tree_width_;
  double   tree_left_alpha_;
  double   tree_right_alpha_;
  double   tree_left_angle_;
  double   tree_right_angle_;
  int      tree_depth_;

  double   tree_left_width_factor_;
  double   tree_left_height_factor_;
  double   tree_right_width_factor_;
  double   tree_right_height_factor_;
};

#endif
