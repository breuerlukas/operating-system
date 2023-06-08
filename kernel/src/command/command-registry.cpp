#include "command-registry.h"

CommandRegistry::CommandRegistry(Memory* memory) : memory_(memory) {

}

void CommandRegistry::AddCommand(Command* command) {
  commands_ = (Command**) memory_->ReallocateMemory(commands_,
    commandsNumber_ * sizeof(Command*), (commandsNumber_ + 1) * sizeof(Command*));
  commands_[commandsNumber_] = command;
  commandsNumber_++;
}

void CommandRegistry::RemoveCommand(Command* command) {
  Command** updatedCommands = (Command**) memory_->AllocateMemory((commandsNumber_ - 1) * sizeof(Command*));
  int updatedCommandsIndex = 0;
  for (int i = 0; i < commandsNumber_; i++) {
    if (commands_[i]->Name() == command->Name()) {
      continue;
    }
    updatedCommands[updatedCommandsIndex] = commands_[i];
    updatedCommandsIndex++;
  }
  memory_->FreeMemory(commands_);
  commands_ = updatedCommands;
  commandsNumber_--;
}

Command* CommandRegistry::FindCommandByName(char *name, int nameLength) {
  for (int i = 0; i < commandsNumber_; i++) {
    bool isSuspect = true;
    for (int j = 0; j < nameLength; j++) {
      if (commands_[i]->Name()[j] != name[j]) {
        isSuspect = false;
        break;
      }
    }
    if (isSuspect) {
      return commands_[i];
    }
  }
  return nullptr;
}

Command** CommandRegistry::Commands() {
  return commands_;
}