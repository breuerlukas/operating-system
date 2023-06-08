#ifndef OPERATING_SYSTEM_COMMAND_LINE_H
#define OPERATING_SYSTEM_COMMAND_LINE_H

#include <cstdint>
#include "../terminal/terminal.h"
#include "../command/command-registry.h"
#include "../keyboard/keyboard.h"
#include "../keyboard/key.h"

class CommandLine {
private:
  Terminal* terminal_;
  Memory* memory_;
  CommandRegistry* commandRegistry_;
  bool isShifting_ = false;
  char* currentInput_;
  int currentInputLength_ = 0;
  void CheckShifting(uint8_t input);
  void ProcessInput(uint8_t input);
  void CheckInputMeaning(uint8_t input);
  void ExecuteCommand();
  void GenerateCommandArguments(void (*callback)(Terminal*, CommandRegistry*, char**, int, int*));
  void Reset();
public:
  CommandLine(Terminal* terminal, Memory* memory, CommandRegistry* commandRegistry);
  void Setup();
};

#endif //OPERATING_SYSTEM_COMMAND_LINE_H
