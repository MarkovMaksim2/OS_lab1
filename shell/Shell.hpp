//
// Created by marko on 26.10.2024.
//

#ifndef SHELL_HPP
#define SHELL_HPP

#include "output/Output.hpp"
#include "input/Input.hpp"

namespace m2ma::app {
  class Shell {
  private:
    shell::Output output_ = shell::Output("\033[34m", "\033[32m", "\033[33m");
  public:
    void Run();
  };
}

#endif  // SHELL_HPP
