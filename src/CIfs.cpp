#include <CIfs.h>
#include <CCeilP.h>
#include <CFuncs.h>
#include <CThrow.h>
#include <CStrUtil.h>
#include <CRenderer2D.h>
#include <CRGBName.h>

CIfs::
CIfs(CTurtle *turtle) :
 turtle_         (turtle),
 initiator_block_(NULL),
 draw_block_     (NULL)
{
  debug_ = false;

  show_generator_ = false;

  ClParserInst->init();

  ClParserInst->setAngleType(CANGLE_TYPE_DEGREES);
}

CIfs::
~CIfs()
{
  reset();

  ClParserInst->term();
}

void
CIfs::
setTurtle(CTurtle *turtle)
{
  turtle_ = turtle;
}

void
CIfs::
reset()
{
  control_.reset();

  delete initiator_block_;

  initiator_block_ = nullptr;

  for (auto &generator_block : generator_blocks_)
    delete generator_block.second;

  generator_blocks_.clear();

  delete draw_block_;

  draw_block_ = nullptr;
}

void
CIfs::
increaseDepth()
{
  control_.increaseDepth();
}

void
CIfs::
decreaseDepth()
{
  control_.decreaseDepth();
}

void
CIfs::
redraw()
{
  turtle_->reset();

  double            length         = 1.0;
  CIfsDirectionType direction_flag = CIFS_DIRECTION_FORWARD;
  CIfsAngleType     angle_flag     = CIFS_ANGLE_ANTICLOCKWISE;
  int               last_section   = 0;
  int               depth          = control_.getDepth();

  if (! show_generator_) {
    if (initiator_block_)
      initiator_block_->draw(length, direction_flag, angle_flag, last_section, depth);
  }
  else {
    moveCommand(25, 50);

    length = 50;

    CIfsBlock *generator_block = getGeneratorBlock("");

    if (generator_block)
      generator_block->draw(length, direction_flag, angle_flag, last_section, 0);
  }
}

void
CIfs::
addGeneratorBlock(const std::string &id, CIfsBlock *generator_block)
{
  GeneratorBlockMap::const_iterator p = generator_blocks_.find(id);

  if (p != generator_blocks_.end())
    delete (*p).second;

  generator_blocks_[id] = generator_block;
}

CIfsBlock *
CIfs::
getGeneratorBlock(const std::string &id) const
{
  GeneratorBlockMap::const_iterator p = generator_blocks_.find(id);

  if (p == generator_blocks_.end())
    return NULL;

  return (*p).second;
}

void
CIfs::
drawGenerator(CIfsCommand *command, double length, CIfsDirectionType direction_flag,
              CIfsAngleType angle_flag, int last_section, int *section, uint depth)
{
  command->exec(length, direction_flag, angle_flag, last_section, section, depth);
}

void
CIfs::
moveCommand(double x, double y)
{
  if (debug_)
    std::cerr << "move: " << x << " " << y << std::endl;

  turtle_->move(x, y);
}

void
CIfs::
stepCommand(const std::string &id, double length, CIfsDirectionType direction_flag,
            CIfsAngleType angle_flag, int last_section, int *section, uint depth)
{
  if (debug_)
    std::cerr << "step: " << length << std::endl;

  CIfsBlock *generator_block = getGeneratorBlock(id);

  if (depth == 0 || generator_block == NULL) {
    turtle_->step(length);
  }
  else {
    CIfsDirection *direction = getDirection(depth);

    CIfsDirectionType direction_modifier = CIFS_DIRECTION_NORMAL;

    if (direction && direction->getNumModifiers() > 0) {
      uint i = *section + generator_block->getNumSteps()*last_section;

      if (i >= direction->getNumModifiers())
        i %= direction->getNumModifiers();

      direction_modifier = direction->getModifier(i);
    }

    if (direction_modifier == CIFS_DIRECTION_REVERSE)
      direction_flag = reverseDirection(direction_flag);

    //------

    CIfsAngle *angle = getAngle(depth);

    CIfsAngleType angle_modifier = CIFS_ANGLE_NORMAL;

    if (angle && angle->getNumModifiers() > 0) {
      uint i = *section + generator_block->getNumSteps()*last_section;

      if (i >= angle->getNumModifiers())
        i %= angle->getNumModifiers();

      angle_modifier = angle->getModifier(i);
    }

    if (angle_modifier     == CIFS_ANGLE_REVERSE &&
        direction_modifier != CIFS_DIRECTION_REVERSE)
      angle_flag = reverseAngle(angle_flag);

    //------

    depth--;

    CIfsBlock *block = generator_block;

    if (depth == 0 && draw_block_ != NULL)
      block = draw_block_;

    if (direction_modifier == CIFS_DIRECTION_REVERSE) {
      turtle_->step(length);
      turtle_->turn(180.0 );
    }

    block->draw(length, direction_flag, angle_flag, *section, depth);

    if (direction_modifier == CIFS_DIRECTION_REVERSE) {
      turtle_->turn(180.0 );
      turtle_->step(length);
    }

    (*section)++;
  }
}

void
CIfs::
drawCommand(double length)
{
  if (debug_)
    std::cerr << "draw: " << length << std::endl;

  turtle_->step(length);
}

void
CIfs::
skipCommand(double length)
{
  if (debug_)
    std::cerr << "skip: " << length << std::endl;

  turtle_->skip(length);
}

void
CIfs::
turnCommand(CIfsAngleType flag, double angle)
{
  if (debug_)
    std::cerr << "turn: " << (flag == CIFS_ANGLE_CLOCKWISE ? "+" : "-") << angle << std::endl;

  if      (flag == CIFS_ANGLE_ANTICLOCKWISE)
    turtle_->turn( angle);
  else if (flag == CIFS_ANGLE_CLOCKWISE)
    turtle_->turn(-angle);
}

void
CIfs::
saveCommand()
{
  if (debug_)
    std::cerr << "save:" << std::endl;

  save_turtle_.push_back(turtle_->dup());
}

void
CIfs::
restoreCommand()
{
  if (debug_)
    std::cerr << "restore:" << std::endl;

  if (! save_turtle_.empty()) {
    delete turtle_;

    turtle_ = save_turtle_.back();

    save_turtle_.pop_back();
  }
}

void
CIfs::
getCommand(const std::string &x_var, const std::string &y_var,
           const std::string &a_var, double factor)
{
  if (debug_)
    std::cerr << "get:" << std::endl;

  if (factor == 0.0)
    return;

  double xval = turtle_->getX    ()/factor;
  double yval = turtle_->getY    ()/factor;
  double aval = turtle_->getAngle();

  ClParserInst->setVariableValue(x_var, ClParserValueMgrInst->createValue(xval));
  ClParserInst->setVariableValue(y_var, ClParserValueMgrInst->createValue(yval));
  ClParserInst->setVariableValue(a_var, ClParserValueMgrInst->createValue(aval));

  if (debug_)
    std::cerr << "get: " << x_var << "=" << xval << ", " <<
                           y_var << "=" << yval << ", " <<
                           a_var << "=" << aval << std::endl;
}

void
CIfs::
setCommand(const std::string &x_var, const std::string &y_var,
           const std::string &a_var, double factor)
{
  if (debug_)
    std::cerr << "set:" << std::endl;

  if (factor == 0.0)
    return;

  double xval, yval, aval;

  ClParserValuePtr xvalue = ClParserInst->getVariableValue(x_var);

  if (xvalue->realValue(&xval)) {
    xval *= factor;

    turtle_->setX(xval);
  }

  ClParserValuePtr yvalue = ClParserInst->getVariableValue(y_var);

  if (yvalue->realValue(&yval)) {
    yval *= factor;

    turtle_->setY(yval);
  }

  ClParserValuePtr avalue = ClParserInst->getVariableValue(a_var);

  if (avalue->realValue(&aval))
    turtle_->setAngle(aval);

  if (debug_)
    std::cerr << "set: " << x_var << "=" << xval << ", " <<
                            y_var << "=" << yval << ", " <<
                            a_var << "=" << aval << std::endl;
}

void
CIfs::
depthCommand(const std::string &depth_var, uint depth)
{
  if (debug_)
    std::cerr << "depth:" << std::endl;

  ClParserInst->setVariableValue(depth_var, ClParserValueMgrInst->createValue(long(depth)));
}

void
CIfs::
calcCommand(const std::string &command)
{
  if (debug_)
    std::cerr << "calc:" << command << std::endl;

  ClParserExpr expr(command);

  ClParserValuePtr value;

  (void) expr.exec(value);

  if (debug_)
    std::cerr << value << std::endl;
}

void
CIfs::
colorCommand(const std::string &color)
{
  if (debug_)
    std::cerr << "color:" << color << std::endl;

  turtle_->setColor(CRGBName::toRGBA(color));
}

CIfsDirection *
CIfs::
getDirection(uint depth)
{
  return control_.getDirection(control_.getDepth() - depth);
}

CIfsAngle *
CIfs::
getAngle(uint depth)
{
  return control_.getAngle(control_.getDepth() - depth);
}

bool
CIfs::
readFile(const std::string &file_name)
{
  reset();

  //------

  CFile file(file_name);

  if (! file.exists() || ! file.isRegular())
    return false;

  std::string line;

  while (file.readLine(line)) {
    line = CStrUtil::stripSpaces(line);

    if (line == "" || line[0] == ';' || line[0] == '#')
      continue;

    uint pos = 0;

    std::string block_str;

    readString(line, &pos, block_str);

    CIfsBlockType block_id = getBlockId(block_str);

    switch (block_id) {
      case CIFS_CONTROL___BLOCK:
        readControl(file);

        break;
      case CIFS_INITIATOR_BLOCK: {
        uint                       num_steps;
        std::vector<CIfsCommand *> commands;

        readCommands(&num_steps, commands, file);

        initiator_block_ = new CIfsBlock(this, num_steps, commands);

        break;
      }
      case CIFS_GENERATOR_BLOCK: {
        std::string id;

        readString(line, &pos, id);

        uint                       num_steps;
        std::vector<CIfsCommand *> commands;

        readCommands(&num_steps, commands, file);

        CIfsBlock *generator_block =
          new CIfsBlock(this, num_steps, commands);

        addGeneratorBlock(id, generator_block);

        break;
      }
      case CIFS_DRAW______BLOCK: {
        uint                       num_steps;
        std::vector<CIfsCommand *> commands;

        readCommands(&num_steps, commands, file);

        draw_block_ = new CIfsBlock(this, num_steps, commands);

        break;
      }
      default:
        break;
    }
  }

  return true;
}

void
CIfs::
readControl(CFile &file)
{
  bool in_control = true;

  std::string line;

  while (file.readLine(line) && in_control) {
    uint pos = 0;

    std::string str;

    readString(line, &pos, str);

    CIfsControlCommandType command_id = getControlCommandId(str);

    switch (command_id) {
      case CIFS_NAME______CONTROL_COMMAND: {
        CStrUtil::skipSpace(line, &pos);

        control_.setName(line.substr(pos));

        break;
      }
      case CIFS_DEPTH_____CONTROL_COMMAND: {
        int depth;

        readInteger(line, &pos, &depth);

        if (depth >= CIFS_MIN_DEPTH && depth <= CIFS_MAX_DEPTH)
          control_.setDepth(depth);

        break;
      }
      case CIFS_DIRECTION_CONTROL_COMMAND: {
        std::string str1;
        int         depth;

        readString (line, &pos, str1);
        readInteger(line, &pos, &depth);

        CIfsDirection *direction = new CIfsDirection(str1, depth);

        control_.addDirection(direction);

        break;
      }
      case CIFS_ANGLE_____CONTROL_COMMAND: {
        std::string str1;
        int         depth;

        readString (line, &pos, str1);
        readInteger(line, &pos, &depth);

        CIfsAngle *angle = new CIfsAngle(str1, depth);

        control_.addAngle(angle);

        break;
      }
      case CIFS_END_______CONTROL_COMMAND: {
        in_control = false;

        break;
      }
      default:
        break;
    }
  }
}

void
CIfs::
readCommands(uint *num_steps, std::vector<CIfsCommand *> &block, CFile &file)
{
  bool in_block = true;

  std::string line;

  while (file.readLine(line) && in_block) {
    uint pos = 0;

    std::string str;

    readString(line, &pos, str);

    CIfsBlockCommandType command_id = getBlockCommandId(str);

    CIfsCommand *command = NULL;

    switch (command_id) {
      case CIFS_MOVE____BLOCK_COMMAND: {
        double x, y;

        readReal(line, &pos, &x);
        readReal(line, &pos, &y);

        command = new CIfsMoveCommand(this, x, y);

        break;
      }
      case CIFS_STEP____BLOCK_COMMAND: {
        double length;

        readReal(line, &pos, &length);

        std::string id;

        readString(line, &pos, id);

        command = new CIfsStepCommand(this, length, id);

        (*num_steps)++;

        break;
      }
      case CIFS_DRAW____BLOCK_COMMAND: {
        double length;

        readReal(line, &pos, &length);

        command = new CIfsDrawCommand(this, length);

        break;
      }
      case CIFS_SKIP____BLOCK_COMMAND: {
        double length;

        readReal(line, &pos, &length);

        command = new CIfsSkipCommand(this, length);

        break;
      }
      case CIFS_TURN____BLOCK_COMMAND: {
        double angle;

        readReal(line, &pos, &angle);

        command = new CIfsTurnCommand(this, angle);

        break;
      }
      case CIFS_MOVEV___BLOCK_COMMAND: {
        std::string x, y;

        readString(line, &pos, x);
        readString(line, &pos, y);

        command = new CIfsMoveVCommand(this, x, y);

        break;
      }
      case CIFS_STEPV___BLOCK_COMMAND: {
        std::string length;

        readString(line, &pos, length);

        std::string id;

        readString(line, &pos, id);

        command = new CIfsStepVCommand(this, length, id);

        (*num_steps)++;

        break;
      }
      case CIFS_DRAWV___BLOCK_COMMAND: {
        std::string length;

        readString(line, &pos, length);

        command = new CIfsDrawVCommand(this, length);

        break;
      }
      case CIFS_SKIPV___BLOCK_COMMAND: {
        std::string length;

        readString(line, &pos, length);

        command = new CIfsSkipVCommand(this, length);

        break;
      }
      case CIFS_TURNV___BLOCK_COMMAND: {
        std::string angle;

        readString(line, &pos, angle);

        command = new CIfsTurnVCommand(this, angle);

        break;
      }
      case CIFS_SAVE____BLOCK_COMMAND: {
        command = new CIfsSaveCommand(this);

        break;
      }
      case CIFS_RESTORE_BLOCK_COMMAND: {
        command = new CIfsRestoreCommand(this);

        break;
      }
      case CIFS_GET_____BLOCK_COMMAND: {
        std::string x_var, y_var, a_var;

        readString(line, &pos, x_var);
        readString(line, &pos, y_var);
        readString(line, &pos, a_var);

        command = new CIfsGetCommand(this, x_var, y_var, a_var);

        break;
      }
      case CIFS_SET_____BLOCK_COMMAND: {
        std::string x_var, y_var, a_var;

        readString(line, &pos, x_var);
        readString(line, &pos, y_var);
        readString(line, &pos, a_var);

        command = new CIfsSetCommand(this, x_var, y_var, a_var);

        break;
      }
      case CIFS_DEPTH___BLOCK_COMMAND: {
        std::string depth;

        readString(line, &pos, depth);

        command = new CIfsDepthCommand(this, depth);

        break;
      }
      case CIFS_CALC____BLOCK_COMMAND: {
        std::string cmd;

        readString(line, &pos, cmd);

        command = new CIfsCalcCommand(this, cmd);

        break;
      }
      case CIFS_COLOR___BLOCK_COMMAND: {
        std::string color;

        readString(line, &pos, color);

        command = new CIfsColorCommand(this, color);

        break;
      }
      case CIFS_END_____BLOCK_COMMAND: {
        in_block = false;

        break;
      }
      default:
        break;
    }

    if (command)
      block.push_back(command);
  }
}

CIfsBlockType
CIfs::
getBlockId(const std::string &block)
{
  struct BlockId {
    const char    *name;
    CIfsBlockType  id;
  };

  static BlockId cifs_blocks[] = {
    { "control"  , CIFS_CONTROL___BLOCK },
    { "initiator", CIFS_INITIATOR_BLOCK },
    { "generator", CIFS_GENERATOR_BLOCK },
    { "draw"     , CIFS_DRAW______BLOCK }
  };

  static int cifs_num_blocks =
    sizeof(cifs_blocks)/sizeof(cifs_blocks[0]);

  //------

  std::string lblock = CStrUtil::toLower(block);

  for (int i = 0; i < cifs_num_blocks; ++i)
    if (strcmp(cifs_blocks[i].name, lblock.c_str()) == 0)
      return cifs_blocks[i].id;

  return CIFS_NULL______BLOCK;
}

CIfsControlCommandType
CIfs::
getControlCommandId(const std::string &command)
{
  struct CommandId {
    const char             *name;
    CIfsControlCommandType  id;
  };

  static CommandId cifs_control_commands[] = {
    { "name"     , CIFS_NAME______CONTROL_COMMAND },
    { "depth"    , CIFS_DEPTH_____CONTROL_COMMAND },
    { "direction", CIFS_DIRECTION_CONTROL_COMMAND },
    { "angle"    , CIFS_ANGLE_____CONTROL_COMMAND },
    { "end"      , CIFS_END_______CONTROL_COMMAND }
  };

  static int cifs_num_control_commands =
    sizeof(cifs_control_commands)/sizeof(cifs_control_commands[0]);

  //------

  std::string lcommand = CStrUtil::toLower(command);

  for (int i = 0; i < cifs_num_control_commands; ++i)
    if (strcmp(cifs_control_commands[i].name, lcommand.c_str()) == 0)
      return cifs_control_commands[i].id;

  return CIFS_NULL______CONTROL_COMMAND;
}

CIfsBlockCommandType
CIfs::
getBlockCommandId(const std::string &command)
{
  struct CommandId {
    const char           *name;
    CIfsBlockCommandType  id;
  };

  static CommandId cifs_block_commands[] = {
    { "move"   , CIFS_MOVE____BLOCK_COMMAND },
    { "step"   , CIFS_STEP____BLOCK_COMMAND },
    { "draw"   , CIFS_DRAW____BLOCK_COMMAND },
    { "skip"   , CIFS_SKIP____BLOCK_COMMAND },
    { "turn"   , CIFS_TURN____BLOCK_COMMAND },
    { "movev"  , CIFS_MOVEV___BLOCK_COMMAND },
    { "stepv"  , CIFS_STEPV___BLOCK_COMMAND },
    { "drawv"  , CIFS_DRAWV___BLOCK_COMMAND },
    { "skipv"  , CIFS_SKIPV___BLOCK_COMMAND },
    { "turnv"  , CIFS_TURNV___BLOCK_COMMAND },
    { "save"   , CIFS_SAVE____BLOCK_COMMAND },
    { "restore", CIFS_RESTORE_BLOCK_COMMAND },
    { "get"    , CIFS_GET_____BLOCK_COMMAND },
    { "set"    , CIFS_SET_____BLOCK_COMMAND },
    { "depth"  , CIFS_DEPTH___BLOCK_COMMAND },
    { "calc"   , CIFS_CALC____BLOCK_COMMAND },
    { "color"  , CIFS_COLOR___BLOCK_COMMAND },
    { "end"    , CIFS_END_____BLOCK_COMMAND }
  };

  static int cifs_num_block_commands =
    sizeof(cifs_block_commands)/sizeof(cifs_block_commands[0]);

  //------

  std::string lcommand = CStrUtil::toLower(command);

  for (int i = 0; i < cifs_num_block_commands; ++i)
    if (strcmp(cifs_block_commands[i].name, lcommand.c_str()) == 0)
      return cifs_block_commands[i].id;

  return CIFS_NULL____BLOCK_COMMAND;
}

void
CIfs::
readReal(const std::string &line, uint *pos, double *real)
{
  CStrUtil::skipSpace(line, pos);

  std::string str;

  while (*pos < line.size() && ! isspace(line[*pos]))
    str += line[(*pos)++];

  CStrUtil::skipSpace(line, pos);

  stringToReal(str, real);
}

void
CIfs::
readInteger(const std::string &line, uint *pos, int *integer)
{
  CStrUtil::skipSpace(line, pos);

  std::string str;

  while (*pos < line.size() && ! isspace(line[*pos]))
    str += line[(*pos)++];

  CStrUtil::skipSpace(line, pos);

  stringToInteger(str, integer);
}

void
CIfs::
readString(const std::string &line, uint *pos, std::string &str)
{
  CStrUtil::skipSpace(line, pos);

  while (*pos < line.size() && ! isspace(line[*pos]))
    str += line[(*pos)++];

  CStrUtil::skipSpace(line, pos);
}

void
CIfs::
stringToReal(const std::string &str, double *real)
{
  //ClParserInst->setDebug(true);

  ClParserExpr expr(str);

  ClParserValuePtr value;

  if (expr.exec(value))
    value->realValue(real);
  else
    *real = 0.0;
}

void
CIfs::
stringToInteger(const std::string &str, int *integer)
{
  ClParserExpr expr(str);

  ClParserValuePtr value;

  if (expr.exec(value))
    value->integerValue(integer);
  else
    *integer = 0;
}

CIfsDirectionType
CIfs::
reverseDirection(CIfsDirectionType direction)
{
  if      (direction == CIFS_DIRECTION_FORWARD)
    return CIFS_DIRECTION_BACKWARD;
  else if (direction == CIFS_DIRECTION_BACKWARD)
    return CIFS_DIRECTION_FORWARD;
  else {
    CTHROW("Bad Direction");
    return CIFS_DIRECTION_FORWARD;
  }
}

CIfsAngleType
CIfs::
reverseAngle(CIfsAngleType angle)
{
  if      (angle == CIFS_ANGLE_ANTICLOCKWISE)
    return CIFS_ANGLE_CLOCKWISE;
  else if (angle == CIFS_ANGLE_CLOCKWISE)
    return CIFS_ANGLE_ANTICLOCKWISE;
  else {
    CTHROW("Bad Angle");
    return CIFS_ANGLE_CLOCKWISE;
  }
}

//------

void
CIfsMoveCommand::
exec(double, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->moveCommand(x_, y_);
}

void
CIfsStepCommand::
exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
     int last_section, int *section, uint depth)
{
  ifs_->stepCommand(id_, length*length_, direction_flag, angle_flag,
                    last_section, section, depth);
}

void
CIfsDrawCommand::
exec(double length, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->drawCommand(length*length_);
}

void
CIfsSkipCommand::
exec(double length, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->skipCommand(length*length_);
}

void
CIfsTurnCommand::
exec(double, CIfsDirectionType, CIfsAngleType angle_flag, int, int *, uint)
{
  ifs_->turnCommand(angle_flag, angle_);
}

void
CIfsMoveVCommand::
exec(double, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  double x1, y1;

  ifs_->stringToReal(x_, &x1);
  ifs_->stringToReal(y_, &y1);

  ifs_->moveCommand(x1, y1);
}

void
CIfsStepVCommand::
exec(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
     int last_section, int *section, uint depth)
{
  double length1;

  ifs_->stringToReal(length_, &length1);

  ifs_->stepCommand(id_, length*length1, direction_flag, angle_flag,
                    last_section, section, depth);
}

void
CIfsDrawVCommand::
exec(double length, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  double length1;

  ifs_->stringToReal(length_, &length1);

  ifs_->drawCommand(length*length1);
}

void
CIfsSkipVCommand::
exec(double length, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  double length1;

  ifs_->stringToReal(length_, &length1);

  ifs_->skipCommand(length*length1);
}

void
CIfsTurnVCommand::
exec(double, CIfsDirectionType, CIfsAngleType angle_flag, int, int *, uint)
{
  double angle1;

  ifs_->stringToReal(angle_, &angle1);

  ifs_->turnCommand(angle_flag, angle1);
}

void
CIfsSaveCommand::
exec(double, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->saveCommand();
}

void
CIfsRestoreCommand::
exec(double, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->restoreCommand();
}

void
CIfsGetCommand::
exec(double length, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->getCommand(x_var_, y_var_, a_var_, length);
}

void
CIfsSetCommand::
exec(double length, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->setCommand(x_var_, y_var_, a_var_, length);
}

void
CIfsDepthCommand::
exec(double, CIfsDirectionType, CIfsAngleType, int, int *, uint depth)
{
  ifs_->depthCommand(depth_, depth);
}

void
CIfsCalcCommand::
exec(double, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->calcCommand(command_);
}

void
CIfsColorCommand::
exec(double, CIfsDirectionType, CIfsAngleType, int, int *, uint)
{
  ifs_->colorCommand(color_);
}

//----------

CIfsDirection *
CIfsControl::
getDirection(uint depth)
{
  CIfsDirection *temp_direction = NULL;

  uint num = direction_list_.size();

  for (uint i = 0; i < num; ++i) {
    CIfsDirection *direction = direction_list_[i];

    if (direction->getDepth() == depth)
      return direction;

    if (direction->getDepth() < depth &&
        (temp_direction == NULL ||
         temp_direction->getDepth() < direction->getDepth()))
      temp_direction = direction;
  }

  return temp_direction;
}

CIfsAngle *
CIfsControl::
getAngle(uint depth)
{
  CIfsAngle *temp_angle = NULL;

  uint num = angle_list_.size();

  for (uint i = 0; i < num; ++i) {
    CIfsAngle *angle = angle_list_[i];

    if (angle->getDepth() == depth)
      return angle;

    if (angle->getDepth() < depth &&
        (temp_angle == NULL ||
         temp_angle->getDepth() < angle->getDepth()))
      temp_angle = angle;
  }

  return temp_angle;
}

//----------

void
CIfsBlock::
draw(double length, CIfsDirectionType direction_flag, CIfsAngleType angle_flag,
     int section, int depth)
{
  int section1 = 0;

  uint num = command_list_.size();

  for (uint i = 0; i < num; ++i) {
    CIfsCommand *command = command_list_[i];

    ifs_->drawGenerator(command, length, direction_flag, angle_flag, section, &section1, depth);
  }
}
