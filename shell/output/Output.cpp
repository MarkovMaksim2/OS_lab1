
#include <iostream>
#include <string>
#include <windows.h>
#include <userenv.h>
#include <ctime>
#include <filesystem>

#include "Output.hpp"

constexpr std::string_view RESET          = "\033[0m";
constexpr std::string_view BOLD           = "\033[1m";
constexpr std::string_view DIM            = "\033[2m";
constexpr std::string_view BoldItalic     = "\033[3;1m";

constexpr std::string_view RED            = "\033[0;31m";
constexpr std::string_view GREEN          = "\033[0;32m";
constexpr std::string_view YELLOW         = "\033[0;33m";
constexpr std::string_view CYAN           = "\033[0;36m";
constexpr std::string_view WHITE          = "\033[0;37m";
constexpr std::string_view GRAY           = "\033[90m";

constexpr int LEN = 1024;

const int OutputDebug = -1;
const int OutputInfo = 0;
const int OutputWarning = 1;
const int OutputError = 2;

void m2ma::app::shell::Output::Println(const std::string& message) {
  std::cout << message << '\n';
}

void m2ma::app::shell::Output::PrintMessage(const std::string& message, int message_type) {
  std::string color;
  std::string format;
  std::string msgtype_string;

  switch (message_type) {
    case OutputDebug:
      color = CYAN;
      format = BOLD;
      msgtype_string = "[OUTPUT_DEBUG]";
      break;
    case OutputInfo:
      color = GREEN;
      format = BOLD;
      msgtype_string = "[OutputInfo]";
      break;
    case OutputWarning:
      color = YELLOW;
      format = DIM;
      msgtype_string = "[OutputWarning]";
      break;
    case OutputError:
      color = RED;
      format = BoldItalic;
      msgtype_string = "[OutputError]";
      break;
    default:
      color = WHITE;
      format = RESET;
      msgtype_string = "[DEFAULT]";
      break;
  }

  if (message_type == OutputError) {
    std::cerr << RESET << color << format << msgtype_string << RESET << message << '\n';
  } else {
    std::cout << RESET << color << format << msgtype_string << RESET << message << '\n';
  }

  std::cout << RESET;
}

void m2ma::app::shell::Output::DisplayPs() {
  TCHAR username[LEN];
  DWORD username_len = LEN + 1;
  GetUserName(username, &username_len);

  std::filesystem::path cwd = std::filesystem::current_path();

  time_t rawtime;
  time(&rawtime);
  struct tm* timeinfo = localtime(&rawtime);

  std::cout << DIM << "#" << RESET << GRAY << username_color_ << username << RESET << "[";

  std::cout << pwd_color_ << cwd.string() << GRAY << "]" << RESET;

  std::cout << GRAY << "[" << RESET << curr_time_color_
            << timeinfo->tm_hour << ":"
            << timeinfo->tm_min
            << RESET << GRAY << "]" << RESET << "> ";
}