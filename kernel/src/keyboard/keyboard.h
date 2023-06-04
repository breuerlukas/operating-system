#ifndef OPERATING_SYSTEM_KEYBOARD_H
#define OPERATING_SYSTEM_KEYBOARD_H

#include <cstdint>

class Keyboard {
private:
  uint8_t ReadInputBytes(uint16_t port);
public:
  Keyboard();
  uint8_t Scan();
};

#endif //OPERATING_SYSTEM_KEYBOARD_H
