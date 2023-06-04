#ifndef OPERATING_SYSTEM_KEY_H
#define OPERATING_SYSTEM_KEY_H

#include <cstdint>

class Key {
private:
  char regularKeys_[87] = {
          0, 0, '1', '2', '3', '4', '5', '6',
          '7', '8', '9', '0', 0, 0, 0, 0,
          'q', 'w', 'e', 'r', 't', 'z', 'u', 'i',
          'o', 'p', 0, '+', 0, 0, 'a', 's',
          'd', 'f', 'g', 'h', 'j', 'k', 'l', 0,
          0, 0, 0, '#', 'y', 'x', 'c', 'v',
          'b', 'n', 'm', ',', '.', '-', 0, '*',
          0, ' ', 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, '7',
          '8', '9', '-', '4', '5', '6', '+', '1',
          '2', '3', '0', '.', 0, 0, '<'
  };
  char capitalizedKeys_[87] = {
          0, 0, '!', '"', 0, '$', '%', '&',
          '/', '(', ')', '=', '?', 0, 0, 0,
          'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I',
          'O', 'P', 0, '*', 0, 0, 'A', 'S',
          'D', 'F', 'G', 'H', 'J', 'K', 'L', 0,
          0, 0, 0, '\'', 'Y', 'X', 'C', 'V',
          'B', 'N', 'M', ';', ':', '_', 0, '*',
          0, ' ', 0, 0, 0, 0, 0, 0,
          0, 0, 0, 0, 0, 0, 0, '7',
          '8', '9', '-', '4', '5', '6', '+', '1',
          '2', '3', '0', '.', 0, 0, '>'
  };
  uint8_t identifier_ = -1;
  char name_ = 0;
  char FindName(char* keys);
public:
  Key(uint8_t identifier);
  Key(char name);
  uint8_t Identifier();
  char LowercaseName();
  char UppercaseName();
};

#endif //OPERATING_SYSTEM_KEY_H
