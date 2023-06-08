#include "command.h"

Command::Command(char *name, Terminal* terminal) : name_(name), terminal_(terminal) {

}

void Command::Execute(char** arguments, int argumentCount, int* argumentLengths) {

}

char* Command::Name() {
  return name_;
}