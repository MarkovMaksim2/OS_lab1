//
// Created by marko on 30.10.2024.
//

#ifndef INPUT_HPP
#define INPUT_HPP

#include <vector>
#include <string>

namespace m2ma::app::shell {
  class Input {
  private:
    static std::vector<std::string> Tokenize(const std::string& input_string);
  public:
    static std::vector<std::string> ReadInput();
  };
}  // namespace m2ma::app

#endif  // INPUT_HPP
