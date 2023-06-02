#include "key.h"

Key::Key(uint8_t identifier) : identifier_(identifier) {

}

Key::Key(char name) : name_(name) {

}

uint8_t Key::Identifier() {
  return identifier_;
}

char Key::Name() {
  if (name_ == 0) {
    return FindName();
  }
  return name_;
}

char Key::FindName() {
  if (identifier_ > 84) {
    return 0;
  }
  name_ = regularKeys_[identifier_];
  return name_;
}