#include "terminal/terminal.h"
#include "terminal/color.h"
#include "intro.h"
#include "memory/memory.h"
#include "command/command-line.h"
#include "command/command-registry.h"
#include "../../applications/src/help/help-command.h"
#include "../../applications/src/shutdown/shutdown-command.h"
#include "../../applications/src/reboot/reboot-command.h"

extern "C" int main() {
  Terminal terminal = Terminal(Color::kLightCyan, Color::kBlack);
  Intro intro = Intro(&terminal);
  intro.Display();
  Memory memory = Memory();
  CommandRegistry commandRegistry = CommandRegistry(&memory);
  HelpCommand helpCommand = HelpCommand(&terminal);
  commandRegistry.AddCommand(&helpCommand);
  ShutdownCommand shutdownCommand = ShutdownCommand(&terminal);
  commandRegistry.AddCommand(&shutdownCommand);
  RebootCommand rebootCommand = RebootCommand(&terminal);
  commandRegistry.AddCommand(&rebootCommand);
  CommandLine commandLine = CommandLine(&terminal, &memory, &commandRegistry);
  commandLine.Setup();
  return 0;
}