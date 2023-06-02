#ifndef OPERATING_SYSTEM_INTRO_H
#define OPERATING_SYSTEM_INTRO_H

#include "terminal/terminal.h"

class Intro {
private:
  Terminal* terminal_;
  void DisplayTitle();
  void DisplayInformation();
public:
  Intro(Terminal* terminal);
  void Display();
};

#endif //OPERATING_SYSTEM_INTRO_H
