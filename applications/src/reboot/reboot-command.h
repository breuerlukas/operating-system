#ifndef OPERATING_SYSTEM_REBOOT_COMMAND_H
#define OPERATING_SYSTEM_REBOOT_COMMAND_H

#define check_flag(flags, n) ((flags)&(1 << (n)))

#include <cstdint>
#include "../../../kernel/src/command/command.h"

class RebootCommand : public Command {
private:
  void Reboot();
  uint8_t InputData(uint16_t port);
  void OutputData(uint16_t port, uint16_t data);
public:
  RebootCommand(Terminal* terminal);
  void Execute(char** arguments, int argumentCount, int* argumentLengths) override;
};

#endif //OPERATING_SYSTEM_REBOOT_COMMAND_H
