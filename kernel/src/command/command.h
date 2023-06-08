#ifndef OPERATING_SYSTEM_COMMAND_H
#define OPERATING_SYSTEM_COMMAND_H

#include "../terminal/terminal.h"

class Command {
private:
  char* name_;
protected:
  Terminal* terminal_;
public:
  explicit Command(char* name, Terminal* terminal);
  virtual void Execute(char** arguments, int argumentCount, int* argumentLengths);
  char* Name();
};

#endif //OPERATING_SYSTEM_COMMAND_H
