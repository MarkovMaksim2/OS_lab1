//
// Created by marko on 01.11.2024.
//

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <vector>
#include <filesystem>
#include <windows.h>
#include <time.h>

#include "output/Output.hpp"

namespace m2ma::app::shell {
  class command {
  protected:
    std::string cmd_str;
  public:
    command() {}

    command(std::string new_cmd_str) : cmd_str(new_cmd_str) {}

    virtual int execute() {
      return 0;
    }

    virtual ~command() {}
  };

  class cd_command : public command {
  public:
    cd_command(std::string new_cmd_str) : command(new_cmd_str) {}

    int execute() override {
      try {
        if (cmd_str != "..") {
            std::filesystem::current_path(std::filesystem::current_path().append(cmd_str));
        } else {
            std::filesystem::current_path(std::filesystem::current_path().remove_filename());
        }
      } catch (const std::filesystem::filesystem_error& e) {
        Output::PrintMessage("No such directory", OutputError);
        return -1;
      }
      return 0;
    }
  };

  class ls_command : public command {
  public:
    ls_command() : command("") {}

    int execute() override {
      WIN32_FIND_DATA findFileData;
      HANDLE hFind;

      std::string searchPath = std::filesystem::current_path().string() + "\\*";

      hFind = FindFirstFile(searchPath.c_str(), &findFileData);

      if (hFind == INVALID_HANDLE_VALUE) {
          Output::PrintMessage("Unable to open directory " + searchPath, OutputError);
          return -1;
      } 

      do {
          const std::string fileOrDirName = std::string(findFileData.cFileName);
          
          if (fileOrDirName == "." || fileOrDirName == "..") {
              continue;
          }

          if (findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
              m2ma::app::shell::Output::Println("[DIR]  " + fileOrDirName);
          } else {
              m2ma::app::shell::Output::Println("[FILE] " + fileOrDirName);
          }
      } while (FindNextFile(hFind, &findFileData) != 0);

      FindClose(hFind);

      return 0;
    }
  };

  class default_command : public command {
  public:
    default_command(std::string new_cmd_str) : command(new_cmd_str) {}

    int execute() override {
      STARTUPINFO si;
      PROCESS_INFORMATION pi;
      ZeroMemory(&si, sizeof(si));
      si.cb = sizeof(si);
      ZeroMemory(&pi, sizeof(pi));

      char* cmd = new char[cmd_str.size() + 1];
      std::copy(cmd_str.begin(), cmd_str.end(), cmd);
      cmd[cmd_str.size()] = '\0';

      if (!CreateProcess(
              NULL,
              cmd,
              NULL,
              NULL,
              FALSE,
              0,
              NULL,
              NULL,
              &si,
              &pi)
      ) {
        m2ma::app::shell::Output::Println("Failed to start process. Error: " + std::to_string(GetLastError()));

        return -1;
      } else {
        m2ma::app::shell::Output::Println("Process started successfully.");

        WaitForSingleObject(pi.hProcess, INFINITE);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
      }

      delete[] cmd;
      return 0;
    }
  };
  
  class command_fabric {
    public:
    static command * get_command(std::vector<std::string> const &tokens) {
      if (tokens.empty()) return new command();

      if (tokens[0] == "cd") {
        if (tokens.size() < 2) {
          return new command();
        }

        std::string cmd;
        for (size_t i = 1; i < tokens.size(); i++) {
          cmd += tokens[i] + " ";
        }
        cmd.pop_back();
        return new cd_command(cmd);
      } else if (tokens[0] == "ls") {
        return new ls_command();
      } else {
        std::string cmd;
        for (size_t i = 0; i < tokens.size(); i++) {
          cmd += tokens[i] + " ";
        }
        cmd.pop_back();
        return new default_command(cmd);
      }
    }
  };
}

#endif  // COMMAND_HPP
