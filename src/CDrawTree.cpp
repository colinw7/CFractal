#include <CDrawTree.h>
#include <CTurtle.h>
#include <CRGBName.h>
#include <CFile.h>
#include <CStrUtil.h>

const char *
CDrawTree::
colors_[] = {
  "#BF3F3F",
  "#B24B3A",
  "#A55836",
  "#986532",
  "#8C722E",
  "#7F7F2A",
  "#728B25",
  "#659821",
  "#59A51D",
  "#4CB219",
  "#3FBF15",
  "#32CB10",
  "#26D80C",
  "#19E508",
  "#0CF204",
  "#00FF00",
};

CDrawTree::
CDrawTree()
{
  turtle_ = NULL;

  canvas_xmin_ = 0.0;
  canvas_ymin_ = 0.0;
  canvas_xmax_ = 1.0;
  canvas_ymax_ = 1.0;

  tree_height_      = 10.0;
  tree_width_       = 1.0;
  tree_left_alpha_  = 1.1;
  tree_right_alpha_ = 1.1;
  tree_left_angle_  = 25.0;
  tree_right_angle_ = 25.0;
  tree_depth_       = 6;

  tree_left_width_factor_   = 1.0;
  tree_left_height_factor_  = 1.0;
  tree_right_width_factor_  = 1.0;
  tree_right_height_factor_ = 1.0;
}

bool
CDrawTree::
read(const std::string &filename)
{
  CFile file(filename);

  std::vector<std::string> lines;

  file.toLines(lines);

  if (lines.size() != 7) {
    std::cerr << "Bad input file" << std::endl;
    return false;
  }

  double height;
  double width;
  double lalpha;
  double ralpha;
  double langle;
  double rangle;
  int    depth;

  if (! CStrUtil::toReal   (lines[0], &height) ||
      ! CStrUtil::toReal   (lines[1], &width ) ||
      ! CStrUtil::toReal   (lines[2], &lalpha) ||
      ! CStrUtil::toReal   (lines[3], &ralpha) ||
      ! CStrUtil::toReal   (lines[4], &langle) ||
      ! CStrUtil::toReal   (lines[5], &rangle) ||
      ! CStrUtil::toInteger(lines[6], &depth )) {
    std::cerr << "Bad input file" << std::endl;
    return false;
  }

  tree_height_      = height;
  tree_width_       = width;
  tree_left_alpha_  = lalpha;
  tree_right_alpha_ = ralpha;
  tree_left_angle_  = langle;
  tree_right_angle_ = rangle;
  tree_depth_       = depth;

  return true;
}

void
CDrawTree::
draw()
{
  canvas_xmin_ = 0.0;
  canvas_ymin_ = 0.0;
  canvas_xmax_ = 0.0;
  canvas_ymax_ = 0.0;

  tree_left_width_factor_   = pow(2.0, -1.0/     tree_left_alpha_);
  tree_left_height_factor_  = pow(2.0, -2.0/(3.0*tree_left_alpha_));
  tree_right_width_factor_  = pow(2.0, -1.0/     tree_right_alpha_);
  tree_right_height_factor_ = pow(2.0, -2.0/(3.0*tree_right_alpha_));

  turtle_ = new CTurtle;

  turtle_->setX(0.0);
  turtle_->setY(0.0);

  turtle_->setAngle(90.0);

  turtle_->step(tree_height_);

  Line *line = new_line(0.0, 0.0, tree_width_);

  line->x2 = turtle_->getX();
  line->y2 = turtle_->getY();

  if (line->x2 < canvas_xmin_) canvas_xmin_ = line->x2;
  if (line->x2 > canvas_xmax_) canvas_xmax_ = line->x2;
  if (line->y2 < canvas_ymin_) canvas_ymin_ = line->y2;
  if (line->y2 > canvas_ymax_) canvas_ymax_ = line->y2;

  turtle_->setAngle(line_angle(line->x1, line->x1, line->x2, line->y2));

  turtle_->turn(tree_left_angle_);

  line->left = new_line(line->x2, line->y2,
                        line->width*tree_left_width_factor_);

  add_branch(line->left,
             tree_left_height_factor_*tree_height_,
             tree_left_angle_,
             tree_depth_);

  turtle_->setAngle(line_angle(line->x1, line->x1, line->x2, line->y2));

  turtle_->turn(-tree_right_angle_);

  line->right = new_line(line->x2, line->y2,
                         line->width*tree_right_width_factor_);

  add_branch(line->right,
             tree_right_height_factor_*tree_height_,
             tree_right_angle_,
             tree_depth_);

  delete turtle_;

  setDataRange(canvas_xmin_, canvas_ymin_, canvas_xmax_, canvas_ymax_);

  draw_line(line, 0);
}

void
CDrawTree::
add_branch(Line *line, double height, double /*angle*/, int depth)
{
  turtle_->setX(line->x1);
  turtle_->setY(line->y1);

  turtle_->step(height);

  line->x2 = turtle_->getX();
  line->y2 = turtle_->getY();

  if (line->x2 < canvas_xmin_) canvas_xmin_ = line->x2;
  if (line->x2 > canvas_xmax_) canvas_xmax_ = line->x2;
  if (line->y2 < canvas_ymin_) canvas_ymin_ = line->y2;
  if (line->y2 > canvas_ymax_) canvas_ymax_ = line->y2;

  depth--;

  if (depth == 0)
    return;

  turtle_->setAngle(line_angle(line->x1, line->y1, line->x2, line->y2));

  turtle_->turn(tree_left_angle_);

  line->left = new_line(line->x2, line->y2,
                        line->width*tree_left_width_factor_);

  add_branch(line->left,
             tree_left_height_factor_*height,
             tree_left_angle_,
             depth);

  turtle_->setAngle(line_angle(line->x1, line->y1, line->x2, line->y2));

  turtle_->turn(-tree_right_angle_);

  line->right = new_line(line->x2, line->y2,
                         line->width*tree_right_width_factor_);

  add_branch(line->right,
             tree_right_height_factor_*height,
             tree_right_angle_,
             depth);
}

CDrawTree::Line *
CDrawTree::
new_line(double x, double y, double width)
{
  Line *line = new Line;

  line->x1    = x;
  line->y1    = y;
  line->width = width;
  line->left  = NULL;
  line->right = NULL;

  return line;
}

double
CDrawTree::
line_angle(double x1, double y1, double x2, double y2)
{
  double  angle;

  if (fabs(x2 - x1) < 1E-6) {
    if (fabs(y2 - y1) < 1E-6)
      return(0.0);
    else if (y2 > y1)
      return(90.0);
    else
      return(270.0);
  }
  else {
    angle = 180.0*atan((y2 - y1)/(x2 - x1))/M_PI;

    if (x2 < x1)
      return(angle + 180.0);
    else if (y2 < y1)
      return(angle + 360.0);
    else
      return(angle);
  }
}

void
CDrawTree::
draw_line(Line *line, int depth)
{
  setLineWidth(line->width);

  int color = (MAX_COLOURS - 1)*depth/tree_depth_;

  set_color(color);

  drawLine(line->x1, line->y1, line->x2, line->y2);

  depth++;

  if (line->left  != NULL)
    draw_line(line->left , depth);

  if (line->right != NULL)
    draw_line(line->right, depth);

  delete line;
}

void
CDrawTree::
set_color(int color)
{
  setForeground(CRGBName::toRGBA(colors_[color]));
}
