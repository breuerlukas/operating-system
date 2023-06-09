#include "reboot-command.h"

RebootCommand::RebootCommand(Terminal* terminal) : Command("reboot", terminal) {

}

void RebootCommand::Execute(char **arguments, int argumentCount, int* argumentLengths) {
  terminal_->PrintLine("Operating System will be restarted now...", 41);
  Reboot();
}

void RebootCommand::Reboot() {
  uint8_t temp;
  asm volatile("cli");
  do {
    temp = InputData(0x64);
    if ((temp & (1<<0)) != 0) {
      InputData(0x60);
    }
  } while ((temp & (1 <<1)) != 0);
  OutputData(0x64, 0xFE);
  loop:
  asm volatile("hlt");
  goto loop;
}

uint8_t RebootCommand::InputData(uint16_t port) {
  uint8_t ret;
  __asm__ __volatile__("inb %1, %0"
          : "= a"(ret)
          : "Nd"(port));
  return ret;
}

void RebootCommand::OutputData(uint16_t port, uint16_t data) {
  __asm__ __volatile__("out %0, %1"
          :
          : "a"(data), "d"(port));
}