#ifndef OPERATING_SYSTEM_HELP_COMMAND_H
#define OPERATING_SYSTEM_HELP_COMMAND_H

#include "../../../kernel/src/command/command.h"

class HelpCommand : public Command {
public:
  HelpCommand(Terminal* terminal);
  void Execute(char** arguments, int argumentCount, int* argumentLengths) override;
};

#endif //OPERATING_SYSTEM_HELP_COMMAND_H
