#include "key.h"

Key::Key(uint8_t identifier) : identifier_(identifier) {

}

Key::Key(char name) : name_(name) {

}

uint8_t Key::Identifier() {
  return identifier_;
}

char Key::LowercaseName() {
  if (name_ == 0) {
    return FindName(regularKeys_);
  }
  return name_;
}

char Key::UppercaseName() {
  if (name_ == 0) {
    return FindName(capitalizedKeys_);
  }
  return name_;
}

char Key::FindName(char* keys) {
  if (identifier_ > 87) {
    return 0;
  }
  name_ = keys[identifier_];
  return name_;
}