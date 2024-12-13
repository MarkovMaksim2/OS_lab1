//
// Created by marko on 30.10.2024.
//
#include <iostream>
#include <string>
#include <vector>

#include "Input.hpp"

constexpr int DefaultBufferSize             = 128;
constexpr std::string_view TokensDelimeters = " \t";

std::vector<std::string> m2ma::app::shell::Input::ReadInput() {
  std::string input_string;

  getline(std::cin, input_string);

  return Tokenize(input_string);
}

std::vector<std::string> m2ma::app::shell::Input::Tokenize(const std::string& input_string) {
  std::vector<std::string> tokens;
  size_t start = 0;
  size_t pos = input_string.find_first_of(TokensDelimeters, start);

  while (pos != std::string::npos) {
    if (pos > start) {
      tokens.push_back(input_string.substr(start, pos - start));
    }
    start = pos + 1;
    pos = input_string.find_first_of(TokensDelimeters, start);
  }

  if (start < input_string.length()) {
    tokens.push_back(input_string.substr(start));
  }

  return tokens;
}
