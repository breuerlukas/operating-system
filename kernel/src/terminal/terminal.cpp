#include "terminal.h"

Terminal::Terminal(Color foregroundColor, Color backgroundColor) :
  foregroundColor_(foregroundColor), backgroundColor_(backgroundColor) {

}

void Terminal::PrintLine(char content) {
  if (content == 0) {
    return;
  }
  const char text[1] {
          (const char) content
  };
  PrintLine(text, 1);
}

int itoa(int value, char *buffer, int radius) {
  char tmp[16];
  char *tp = tmp;
  int i;
  unsigned v;
  int sign = (radius == 10 && value < 0);
  if (sign) {
    v = -value;
  } else {
    v = (unsigned) value;
  }
  while (v || tp == tmp) {
    i = v % radius;
    v /= radius;
    if (i < 10) {
      *tp++ = i + '0';
    } else {
      *tp++ = i + 'a' - 10;
    }
  }
  int len = tp - tmp;
  if (sign) {
    *buffer++ = '-';
    len++;
  }
  while (tp > tmp) {
    *buffer++ = *--tp;
  }
  return len;
}

void Terminal::PrintLine(int value) {
  char *buffer;
  int length = itoa(value, buffer, 10);
  PrintLine(buffer, length);
}

void Terminal::PrintLine(const char* content, int length) {
  Print(content, length);
  NextLine();
}

void Terminal::Print(char content) {
  if (content == 0) {
    return;
  }
  const char text[1] {
    (const char) content
  };
  Print(text, 1);
}

void Terminal::Print(int value) {
  char *buffer;
  int length = itoa(value, buffer, 10);
  Print(buffer, length);
}

void Terminal::Print(const char* content, int length) {
  for (uint16_t i = 0; i < length; i++) {
    WriteToTerminal((int) ((const unsigned char *) content)[i]);
  }
}

void Terminal::WriteToTerminal(int data) {
  char transformedData = (char) data;
  WriteToTerminal(&transformedData, sizeof(transformedData));
}

void Terminal::WriteToTerminal(const char *data, uint16_t size) {
  for (uint16_t i = 0; i < size; i++) {
    UpdateTerminalBuffer(data[i]);
  }
}

void Terminal::UpdateTerminalBuffer(char data) {
  UpdateTerminalBuffer(data, CreateTerminalColor(), currentColumn_, currentRow_);
  if (++currentColumn_ == VGA_WIDTH) {
    currentColumn_ = 0;
    if (++currentRow_ == VGA_HEIGHT) {
      currentRow_ = 0;
    }
  }
}

void Terminal::UpdateTerminalBuffer(char data, uint8_t color, uint16_t x, uint16_t y) {
  const uint16_t index = y * VGA_WIDTH + x;
  buffer_[index] = ApplyColorToChar(data, color);
}

uint16_t Terminal::ApplyColorToChar(char data, uint8_t color) {
  uint16_t transformedData = data;
  uint16_t transformedColor = color;
  return transformedData | transformedColor << 8;
}

uint8_t Terminal::CreateTerminalColor() {
  return foregroundColor_ | backgroundColor_ << 4;
}

void Terminal::Backspace() {
  currentColumn_--;
  Print(' ');
  currentColumn_--;
}

void Terminal::NextLine() {
  currentRow_++;
  currentColumn_ = 0;
}

void Terminal::ChangeForegroundColor(Color color) {
  foregroundColor_ = color;
}

void Terminal::ChangeBackgroundColor(Color color) {
  backgroundColor_ = color;
}