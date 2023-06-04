#include "intro.h"

Intro::Intro(Terminal* terminal) : terminal_(terminal) {

}

void Intro::Display() {
  DisplayTitle();
  DisplayInformation();
}

void Intro::DisplayTitle() {
  terminal_->PrintLine("", 0);
  terminal_->PrintLine("        ___                    _   _             "
                       "___         _             ", 75);
  terminal_->PrintLine("       / _ \\ _ __ ___ _ _ __ _| |_(_)_ _  __ _  "
                       "/ __|_  _ __| |_ ___ _ __  ", 75);
  terminal_->PrintLine("      | (_) | '_ / -_| '_/ _` |  _| | ' \\/ _` | "
                       "\\__ | || (_-|  _/ -_| '  \\ ", 75);
  terminal_->PrintLine("       \\___/| .__\\___|_| \\__,_|\\__|_|_||_\\__"
                       ", | |___/\\_, /__/\\__\\___|_|_|_|", 75);
  terminal_->PrintLine("            |_|                          |___/   "
                       "    |__/                  ", 75);
  terminal_->PrintLine("", 0);
  terminal_->PrintLine("", 0);
}

void Intro::DisplayInformation() {
  terminal_->PrintLine("       Operating System - v1.0.0", 32);
}
