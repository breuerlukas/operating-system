#include "command-line.h"

CommandLine::CommandLine(Terminal* terminal, Memory* memory, CommandRegistry* commandRegistry) :
  terminal_(terminal), memory_(memory), commandRegistry_(commandRegistry) {

}

void CommandLine::Setup() {
  Keyboard keyboard = Keyboard();
  bool isBlocked = false;
  uint8_t lastInput = -1;
  while (true) {
    uint8_t input = keyboard.Scan();
    CheckShifting(input);
    if (input & 0x80) {
      isBlocked = false;
      continue;
    }
    if (isBlocked && (input == lastInput)) {
      continue;
    }
    ProcessInput(input);
    CheckInputMeaning(input);
    isBlocked = true;
    lastInput = input;
  }
}

void CommandLine::CheckShifting(uint8_t input) {
  if (!isShifting_ && (input == 0x2A || input == 0x36)) {
    isShifting_ = true;
    return;
  }
  if (isShifting_ && (input == (0x2A | 0x80) || input == (0x36 | 0x80))) {
    isShifting_ = false;
    return;
  }
}

void CommandLine::ProcessInput(uint8_t input) {
  Key key = Key(input);
  char name = isShifting_ ? key.UppercaseName() : key.LowercaseName();
  if (name == 0) {
    return;
  }
  if (currentInputLength_ == 0) {
    currentInput_ = (char*) memory_->AllocateMemory(sizeof(char));
  } else {
    currentInput_ = (char*) memory_->ReallocateMemory(currentInput_,
      (currentInputLength_) * sizeof(char), (currentInputLength_ + 1) * sizeof(char));
  }
  currentInput_[currentInputLength_] = name;
  currentInputLength_++;
  terminal_->Print(name);
}

void CommandLine::CheckInputMeaning(uint8_t input) {
  if (input == 0x0E) {
    char* updatedCurrentInput = (char*) memory_->AllocateMemory((currentInputLength_ - 1) * sizeof(char));
    for (int i = 0; i < currentInputLength_ - 1; i++) {
      updatedCurrentInput[i] = currentInput_[i];
    }
    memory_->FreeMemory(currentInput_);
    currentInput_ = updatedCurrentInput;
    currentInputLength_--;
    terminal_->Backspace();
    return;
  }
  if (input == 0x1C) {
    ExecuteCommand();
    return;
  }
}

void CallCommandInterface(
  Terminal* terminal, CommandRegistry* commandRegistry, char **arguments,
  int argumentNumber, int *argumentLengths
) {
  Command* command = commandRegistry->FindCommandByName(arguments[0], argumentLengths[0]);
  if (command == nullptr) {
    terminal->PrintLine("Error: Command not found!", 25);
    return;
  }
  command->Execute(arguments, argumentNumber, argumentLengths);
}

void CommandLine::ExecuteCommand() {
  terminal_->NextLine();
  if (currentInputLength_ == 0) {
    return;
  }
  GenerateCommandArguments(&CallCommandInterface);
  Reset();
}

void CommandLine::GenerateCommandArguments(void (*callback)(Terminal*, CommandRegistry*, char **, int, int *)) {
  char** arguments;
  int argumentNumber = 1;
  int* argumentLengths = (int*) memory_->AllocateMemory(1 * sizeof(int));
  argumentLengths[0] = 0;
  char* currentArgument = (char*) memory_->AllocateMemory(128 * sizeof(char));
  for (int i = 0; i < currentInputLength_; i++) {
    if (currentInput_[i] == ' ') {
      arguments = (char**) memory_->ReallocateMemory(arguments,
        (argumentNumber - 1) * sizeof(char*), argumentNumber * sizeof(char*));
      arguments[argumentNumber - 1] = currentArgument;
      currentArgument = (char*) memory_->AllocateMemory(128 * sizeof(char));
      argumentLengths = (int*) memory_->ReallocateMemory(argumentLengths,
        argumentNumber * sizeof(int), (argumentNumber + 1) * sizeof(int));
      argumentLengths[argumentNumber] = 0;
      argumentNumber++;
      continue;
    }
    int currentArgumentLength = argumentLengths[argumentNumber - 1];
    currentArgument[currentArgumentLength] = currentInput_[i];
    argumentLengths[argumentNumber - 1] = currentArgumentLength + 1;
  }
  arguments = (char**) memory_->ReallocateMemory(arguments,
    (argumentNumber - 1) * sizeof(char*), argumentNumber * sizeof(char*));
  arguments[argumentNumber - 1] = currentArgument;
  callback(terminal_, commandRegistry_, arguments, argumentNumber, argumentLengths);
  for (int i = 0; i < argumentNumber; i++) {
    memory_->FreeMemory(arguments[i]);
  }
  memory_->FreeMemory(arguments);
  memory_->FreeMemory(argumentLengths);
  memory_->FreeMemory(currentArgument);
}

void CommandLine::Reset() {
  memory_->FreeMemory(currentInput_);
  currentInputLength_ = 0;
}