#ifndef CIFS_H
#define CIFS_H

#include <CFuncs.h>
#include <CTurtle.h>
#include <map>

#define CIFS_MIN_DEPTH 0
#define CIFS_MAX_DEPTH 20

class CFile;

enum CIfsDirectionType {
  CIFS_DIRECTION_FORWARD  = 0,
  CIFS_DIRECTION_BACKWARD = 1,
  CIFS_DIRECTION_NORMAL   = 2,
  CIFS_DIRECTION_REVERSE  = 3
};

enum CIfsAngleType {
  CIFS_ANGLE_ANTICLOCKWISE = 0,
  CIFS_ANGLE_CLOCKWISE     = 1,
  CIFS_ANGLE_NORMAL        = 1,
  CIFS_ANGLE_REVERSE       = 2
};

/* Block Names */

enum CIfsBlockType {
  CIFS_NULL______BLOCK = 0,
  CIFS_CONTROL___BLOCK = 1,
  CIFS_INITIATOR_BLOCK = 2,
  CIFS_GENERATOR_BLOCK = 3,
  CIFS_DRAW______BLOCK = 4
};

/* Control Command Names */

enum CIfsControlCommandType {
  CIFS_NULL______CONTROL_COMMAND = 0,
  CIFS_NAME______CONTROL_COMMAND = 1,
  CIFS_DEPTH_____CONTROL_COMMAND = 2,
  CIFS_DIRECTION_CONTROL_COMMAND = 3,
  CIFS_ANGLE_____CONTROL_COMMAND = 4,
  CIFS_END_______CONTROL_COMMAND = 5
};

/* Block Command Names */

enum CIfsBlockCommandType {
  CIFS_NULL____BLOCK_COMMAND = 0,
  CIFS_MOVE____BLOCK_COMMAND = 1,
  CIFS_STEP____BLOCK_COMMAND = 2,
  CIFS_DRAW____BLOCK_COMMAND = 3,
  CIFS_SKIP____BLOCK_COMMAND = 4,
  CIFS_TURN____BLOCK_COMMAND = 5,
  CIFS_MOVEV___BLOCK_COMMAND = 6,
  CIFS_STEPV___BLOCK_COMMAND = 7,
  CIFS_DRAWV___BLOCK_COMMAND = 8,
  CIFS_SKIPV___BLOCK_COMMAND = 9,
  CIFS_TURNV___BLOCK_COMMAND = 10,
  CIFS_SAVE____BLOCK_COMMAND = 11,
  CIFS_RESTORE_BLOCK_COMMAND = 12,
  CIFS_GET_____BLOCK_COMMAND = 13,
  CIFS_SET_____BLOCK_COMMAND = 14,
  CIFS_DEPTH___BLOCK_COMMAND = 15,
  CIFS_CALC____BLOCK_COMMAND = 16,
  CIFS_COLOR___BLOCK_COMMAND = 17,
  CIFS_END_____BLOCK_COMMAND = 18
};

/* Structures */

class CIfsDirection {
 private:
  uint               depth_;
  uint               num_modifiers_;
  CIfsDirectionType *modifiers_;

 public:
  CIfsDirection() :
   depth_(0), num_modifiers_(0), modifiers_(nullptr) {
  }

  CIfsDirection(const std::string &modifiers, int depth) :
   depth_(depth), num_modifiers_(0), modifiers_(nullptr) {
    setModifiers(modifiers);
  }

 ~CIfsDirection() {
    delete [] modifiers_;
  }

  uint getDepth() const { return depth_; }

  void setDepth(uint depth) { depth_ = depth; }

  uint getNumModifiers() const { return num_modifiers_; }

  CIfsDirectionType getModifier(uint i) const { return modifiers_[i]; }

  void setModifiers(const std::string &str) {
    num_modifiers_ = str.size();

    modifiers_ = new CIfsDirectionType [num_modifiers_];

    for (uint i = 0; i < str.size(); ++i) {
      if (str[i] == 'r')
        modifiers_[i] = CIFS_DIRECTION_REVERSE;
      else
        modifiers_[i] = CIFS_DIRECTION_NORMAL ;
    }
  }
};

class CIfsAngle {
 private:
  uint           depth_;
  uint           num_modifiers_;
  CIfsAngleType *modifiers_;

 public:
  CIfsAngle() :
    depth_(0), num_modifiers_(0), modifiers_(nullptr) {
  }

  CIfsAngle(const std::string &modifiers, int depth) :
   depth_(depth), num_modifiers_(0), modifiers_(nullptr) {
    setModifiers(modifiers);
  }

 ~CIfsAngle() {
    delete [] modifiers_;
  }

  uint getDepth() const { return depth_; }

  void setDepth(uint depth) { depth_ = depth; }

  uint getNumModifiers() const { return num_modifiers_; }

  CIfsAngleType getModifier(uint i) const { return modifiers_[i]; }

  void setModifiers(const std::string &str) {
    num_modifiers_ = str.size();

    modifiers_ = new CIfsAngleType [num_modifiers_];

    for (uint i = 0; i < str.size(); ++i) {
      if (str[i] == 'r')
        modifiers_[i] = CIFS_ANGLE_REVERSE;
      else
        modifiers_[i] = CIFS_ANGLE_NORMAL ;
    }
  }
};

class CIfsControl {
 private:
  enum { DEFAULT_DEPTH = 3 };

  typedef std::vector<CIfsDirection *> DirectionList;
  typedef std::vector<CIfsAngle *>     AngleList;

  std::string   name_;
  uint          depth_;
  DirectionList direction_list_;
  AngleList     angle_list_;

 public:
  CIfsControl(uint depth=DEFAULT_DEPTH) :
   depth_(depth) {
  }

 ~CIfsControl() {
    reset();
  }

  void reset() {
    name_ = "Ifs";

    depth_ = DEFAULT_DEPTH;

    for (auto &direction : direction_list_)
      delete direction;

    for (auto &angle : angle_list_)
      delete angle;

    direction_list_.clear();
    angle_list_    .clear();
  }

  const std::string &getName() const { return name_; }

  void setName(const std::string &name) { name_ = name; }

  uint getDepth() const { return depth_; }

  void setDepth(uint depth) { depth_ = depth; }

  void increaseDepth() {
    if (depth_ >= CIFS_MAX_DEPTH)
      return;

    ++depth_;
  }

  void decreaseDepth() {
    if (depth_ <= CIFS_MIN_DEPTH)
      return;

    --depth_;
  }

  void addDirection(CIfsDirection *direction) {
    direction_list_.push_back(direction);
  }

  void addAngle(CIfsAngle *angle) {
    angle_list_.push_back(angle);
  }

  CIfsDirection *getDirection(uint depth);

  CIfsAngle *getAngle(uint depth);
};

class CIfs;

struct CIfsState {
  double            length;
  CIfsDirectionType direction_flag;
  CIfsAngleType     angle_flag;
  int               last_section;
  int               section;
  uint              depth;
};

class CIfsCommand {
 protected:
  CIfs                 *ifs_;
  CIfsBlockCommandType  id_;

 public:
  CIfsCommand(CIfs *ifs, CIfsBlockCommandType id) :
   ifs_(ifs), id_(id) {
  }

  virtual ~CIfsCommand() { }

  virtual void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
                    int last_section, int *section, uint depth) = 0;
};

class CIfsBlock {
 private:
  typedef std::vector<CIfsCommand *> CommandList;

  CIfs        *ifs_;
  uint         num_steps_;
  CommandList  command_list_;

 public:
  CIfsBlock(CIfs *ifs) :
   ifs_(ifs), num_steps_(0) {
  }

  CIfsBlock(CIfs *ifs, uint num_steps, const CommandList &commands) :
   ifs_(ifs), num_steps_(num_steps), command_list_(commands) {
  }

 ~CIfsBlock() {
    for (const auto &command: command_list_)
      delete command;
  }

  uint getNumSteps() const { return num_steps_; }

  void draw(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int section, int depth);
};

class CIfsMoveCommand : public CIfsCommand {
 private:
  double x_;
  double y_;

 public:
  CIfsMoveCommand(CIfs *ifs, double x, double y) :
   CIfsCommand(ifs, CIFS_MOVE____BLOCK_COMMAND), x_(x), y_(y) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsStepCommand : public CIfsCommand {
 private:
  double      length_;
  std::string id_;

 public:
  CIfsStepCommand(CIfs *ifs, double length, const std::string &id="") :
   CIfsCommand(ifs, CIFS_STEP____BLOCK_COMMAND), length_(length), id_(id) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsDrawCommand : public CIfsCommand {
 private:
  double length_;

 public:
  CIfsDrawCommand(CIfs *ifs, double length) :
   CIfsCommand(ifs, CIFS_DRAW____BLOCK_COMMAND), length_(length) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsSkipCommand : public CIfsCommand {
 private:
  double length_;

 public:
  CIfsSkipCommand(CIfs *ifs, double length) :
   CIfsCommand(ifs, CIFS_SKIP____BLOCK_COMMAND), length_(length) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsTurnCommand : public CIfsCommand {
 private:
  double angle_;

 public:
  CIfsTurnCommand(CIfs *ifs, double angle) :
   CIfsCommand(ifs, CIFS_TURN____BLOCK_COMMAND), angle_(angle) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsMoveVCommand : public CIfsCommand {
 private:
  std::string x_;
  std::string y_;

 public:
  CIfsMoveVCommand(CIfs *ifs, const std::string &x, const std::string &y) :
   CIfsCommand(ifs, CIFS_MOVEV___BLOCK_COMMAND), x_(x), y_(y) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsStepVCommand : public CIfsCommand {
 private:
  std::string length_;
  std::string id_;

 public:
  CIfsStepVCommand(CIfs *ifs, const std::string &length, const std::string &id) :
   CIfsCommand(ifs, CIFS_STEPV___BLOCK_COMMAND), length_(length), id_(id) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsDrawVCommand : public CIfsCommand {
 private:
  std::string length_;

 public:
  CIfsDrawVCommand(CIfs *ifs, const std::string &length) :
   CIfsCommand(ifs, CIFS_DRAWV___BLOCK_COMMAND), length_(length) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsSkipVCommand : public CIfsCommand {
 private:
  std::string length_;

 public:
  CIfsSkipVCommand(CIfs *ifs, const std::string &length) :
   CIfsCommand(ifs, CIFS_SKIPV___BLOCK_COMMAND), length_(length) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsTurnVCommand : public CIfsCommand {
 private:
  std::string angle_;

 public:
  CIfsTurnVCommand(CIfs *ifs, const std::string &angle) :
   CIfsCommand(ifs, CIFS_TURNV___BLOCK_COMMAND), angle_(angle) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsSaveCommand : public CIfsCommand {
 public:
  CIfsSaveCommand(CIfs *ifs) :
   CIfsCommand(ifs, CIFS_SAVE____BLOCK_COMMAND) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsRestoreCommand : public CIfsCommand {
 public:
  CIfsRestoreCommand(CIfs *ifs) :
   CIfsCommand(ifs, CIFS_RESTORE_BLOCK_COMMAND) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsGetCommand : public CIfsCommand {
 private:
  std::string x_var_;
  std::string y_var_;
  std::string a_var_;

 public:
  CIfsGetCommand(CIfs *ifs, const std::string &x_var, const std::string &y_var,
                 const std::string &a_var) :
   CIfsCommand(ifs, CIFS_GET_____BLOCK_COMMAND), x_var_(x_var), y_var_(y_var), a_var_(a_var) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsSetCommand : public CIfsCommand {
 private:
  std::string x_var_;
  std::string y_var_;
  std::string a_var_;

 public:
  CIfsSetCommand(CIfs *ifs, const std::string &x_var, const std::string &y_var,
                 const std::string &a_var) :
   CIfsCommand(ifs, CIFS_SET_____BLOCK_COMMAND), x_var_(x_var), y_var_(y_var), a_var_(a_var) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsDepthCommand : public CIfsCommand {
 private:
  std::string depth_;

 public:
  CIfsDepthCommand(CIfs *ifs, const std::string &depth) :
   CIfsCommand(ifs, CIFS_DEPTH___BLOCK_COMMAND), depth_(depth) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsCalcCommand : public CIfsCommand {
 private:
  std::string command_;

 public:
  CIfsCalcCommand(CIfs *ifs, const std::string &command) :
   CIfsCommand(ifs, CIFS_CALC____BLOCK_COMMAND), command_(command) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfsColorCommand : public CIfsCommand {
 private:
  std::string color_;

 public:
  CIfsColorCommand(CIfs *ifs, const std::string &color) :
   CIfsCommand(ifs, CIFS_COLOR___BLOCK_COMMAND), color_(color) {
  }

  void exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
            int last_section, int *section, uint depth);
};

class CIfs {
 public:
   CIfs(CTurtle *turtle=nullptr);
  ~CIfs();

   void setTurtle(CTurtle *turtle);

   void reset();

   void setDebug(bool debug=true) { debug_ = debug; }
   bool getDebug() const { return debug_; }

   void setShowGenerator(bool show=true) { show_generator_ = show; }
   bool getShowGenerator() const { return show_generator_; }

   void setDepth(uint depth) { control_.setDepth(depth); }

   uint getDepth() const { return control_.getDepth(); }

   const std::string &getName() const { return control_.getName(); }

   void increaseDepth();
   void decreaseDepth();

   void redraw();

   void addGeneratorBlock(const std::string &id, CIfsBlock *generator_block);

   CIfsBlock *getGeneratorBlock(const std::string &id) const;

   void drawGenerator(CIfsCommand *command, double length, CIfsDirectionType direction_flag,
                      CIfsAngleType angle_flag, int last_section, int *section, uint depth);

   void moveCommand(double x, double y);
   void stepCommand(const std::string &id, double length, CIfsDirectionType direction_flag,
                    CIfsAngleType angle_flag, int last_section, int *section, uint depth);
   void drawCommand(double length);
   void skipCommand(double length);
   void turnCommand(CIfsAngleType flag, double angle);
   void saveCommand();
   void restoreCommand();
   void getCommand(const std::string &x_var, const std::string &y_var,
                   const std::string &a_var, double factor);
   void setCommand(const std::string &x_var, const std::string &y_var,
                   const std::string &a_var, double factor);
   void depthCommand(const std::string &depth_var, uint depth);
   void calcCommand(const std::string &command);
   void colorCommand(const std::string &color);

   CIfsDirection *getDirection(uint depth);
   CIfsAngle     *getAngle(uint depth);

   bool readFile(const std::string &file_name);
   void readControl(CFile &file);
   void readCommands(uint *num_steps, std::vector<CIfsCommand *> &block, CFile &file);

   CIfsBlockType          getBlockId(const std::string &block);
   CIfsControlCommandType getControlCommandId(const std::string &command);
   CIfsBlockCommandType   getBlockCommandId(const std::string &command);

   void readReal(const std::string &line, uint *pos, double *real);
   void readInteger(const std::string &line, uint *pos, int *integer);
   void readString(const std::string &line, uint *pos, std::string &str);

   void stringToReal(const std::string &str, double *real);
   void stringToInteger(const std::string &str, int *integer);

   void moveTo(double x, double y);
   void lineTo(double x, double y);

   CIfsDirectionType reverseDirection(CIfsDirectionType direction);
   CIfsAngleType     reverseAngle(CIfsAngleType direction);

 private:
  typedef std::vector<CTurtle *>            TurtleStack;
  typedef std::map<std::string,CIfsBlock *> GeneratorBlockMap;

  CTurtle*    turtle_;
  TurtleStack save_turtle_;

  CIfsControl        control_;
  CIfsBlock         *initiator_block_;
  GeneratorBlockMap  generator_blocks_;
  CIfsBlock         *draw_block_;

  bool show_generator_;
  bool debug_;
};

#endif
