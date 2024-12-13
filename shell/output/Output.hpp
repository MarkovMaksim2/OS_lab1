//
// Created by marko on 26.10.2024.
//

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <string>

namespace m2ma::app::shell {
  class Output {
  private:
    std::string username_color_;
    std::string pwd_color_;
    std::string curr_time_color_;
  public:
    Output(std::string  new_username_color, std::string  new_pwd_color,
           std::string  new_curr_time_color) :
        username_color_(std::move(new_username_color)), pwd_color_(std::move(new_pwd_color)),
        curr_time_color_(std::move(new_curr_time_color)) {}

    static void Println(const std::string& message);

    static void PrintMessage(const std::string& message, int message_type);

    void DisplayPs();
  };
}  // namespace m2ma::app

extern const int OutputDebug;
extern const int OutputInfo;
extern const int OutputWarning;
extern const int OutputError;

#endif  // OUTPUT_HPP
