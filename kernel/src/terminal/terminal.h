#ifndef OPERATING_SYSTEM_TERMINAL_H
#define OPERATING_SYSTEM_TERMINAL_H

#include <cstdint>
#include "color.h"

class Terminal {
private:
  static const uint16_t VGA_WIDTH = 80;
  static const uint16_t VGA_HEIGHT = 25;
  uint16_t* buffer_ = (uint16_t*) 0xb8000;
  uint16_t currentRow_ = 0;
  uint16_t currentColumn_ = 0;
  Color foregroundColor_;
  Color backgroundColor_;
  void WriteToTerminal(int data);
  void WriteToTerminal(const char *data, uint16_t size);
  void UpdateTerminalBuffer(char data);
  void UpdateTerminalBuffer(char data, uint8_t color, uint16_t x, uint16_t y);
  void CheckRowExceedsLimit();
  uint16_t ApplyColorToChar(char data, uint8_t color);
  uint8_t CreateTerminalColor();
public:
  Terminal(Color foregroundColor, Color backgroundColor);
  void PrintLine(char content);
  void PrintLine(int value);
  void PrintLine(const char* content, int length);
  void Print(char content);
  void Print(int value);
  void Print(const char* content, int length);
  void Backspace();
  void NextLine();
  void ChangeForegroundColor(Color color);
  void ChangeBackgroundColor(Color color);
};

#endif //OPERATING_SYSTEM_TERMINAL_H
