#include "help-command.h"

HelpCommand::HelpCommand(Terminal* terminal) : Command("help", terminal) {

}

void HelpCommand::Execute(char **arguments, int argumentCount, int* argumentLengths) {
  terminal_->PrintLine("Help command executed", 21);
  terminal_->NextLine();
}