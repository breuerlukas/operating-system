#include "shutdown-command.h"

ShutdownCommand::ShutdownCommand(Terminal* terminal) : Command("shutdown", terminal) {

}

void ShutdownCommand::Execute(char **arguments, int argumentCount, int* argumentLengths) {
  Shutdown();
}

void ShutdownCommand::Shutdown() {
  OutputData(0xB004, 0x2000);
  OutputData(0x604, 0x2000);
  OutputData(0x4004, 0x3400);
}

void ShutdownCommand::OutputData(uint16_t port, uint16_t data) {
  __asm__ __volatile__("out %0, %1"
          :
          : "a"(data), "d"(port));
}