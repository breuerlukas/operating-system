#include "help-command.h"

HelpCommand::HelpCommand(Terminal* terminal) : Command("help", terminal) {

}

void HelpCommand::Execute(char **arguments, int argumentCount, int* argumentLengths) {
  terminal_->PrintLine("Commands:", 9);
  terminal_->PrintLine(" - help", 7);
  terminal_->PrintLine(" - reboot", 9);
  terminal_->PrintLine(" - shutdown", 11);
  terminal_->NextLine();
}