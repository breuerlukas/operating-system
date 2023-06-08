#ifndef OPERATING_SYSTEM_COMMAND_REGISTRY_H
#define OPERATING_SYSTEM_COMMAND_REGISTRY_H

#include "../memory/memory.h"
#include "command.h"

class CommandRegistry {
private:
  Memory* memory_;
  Command** commands_;
  int commandsNumber_ = 0;
public:
  CommandRegistry(Memory* memory);
  void AddCommand(Command* command);
  void RemoveCommand(Command* command);
  Command* FindCommandByName(char* name, int nameLength);
  Command** Commands();
};

#endif //OPERATING_SYSTEM_COMMAND_REGISTRY_H
