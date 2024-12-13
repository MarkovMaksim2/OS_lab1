//
// Created by marko on 26.10.2024.
//

#include "Shell.hpp"
#include "Command.hpp"

#include <windows.h>
#include <string>

void m2ma::app::Shell::Run() {
  while (true) {
    output_.DisplayPs();
    std::vector<std::string> tokens = shell::Input::ReadInput();

    if (!tokens.empty() && tokens[0] == "quit") {
      m2ma::app::shell::Output::Println("Shell process ended, goodbye <3");
      return;
    }

    shell::command *command = shell::command_fabric::get_command(tokens);

    command->execute();
    delete command;    
  }
}