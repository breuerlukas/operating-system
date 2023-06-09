#ifndef OPERATING_SYSTEM_SHUTDOWN_COMMAND_H
#define OPERATING_SYSTEM_SHUTDOWN_COMMAND_H

#include <cstdint>
#include "../../../kernel/src/command/command.h"

class ShutdownCommand : public Command {
private:
  void Shutdown();
  void OutputData(uint16_t port, uint16_t data);
public:
  ShutdownCommand(Terminal* terminal);
  void Execute(char** arguments, int argumentCount, int* argumentLengths) override;
};

#endif //OPERATING_SYSTEM_SHUTDOWN_COMMAND_H
