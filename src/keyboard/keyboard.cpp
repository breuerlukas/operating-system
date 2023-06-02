#include "keyboard.h"

Keyboard::Keyboard() {

}

uint8_t Keyboard::Scan() {
  uint8_t input = ReadInputBytes(0x60);
  if ((input & 0x7f) != 0) {
    return input;
  } else {
    return -1;
  }
}

uint8_t Keyboard::ReadInputBytes(uint16_t port) {
  uint8_t ret;
  __asm__ __volatile__("inb %1, %0"
          : "= a"(ret)
          : "Nd"(port));
  return ret;
}