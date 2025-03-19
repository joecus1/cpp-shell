#include "Commands.hpp"
#include <sstream>
#include <filesystem>
#include <iostream>
#include <unordered_map>

namespace fs = std::filesystem;

std::unordered_map<std::string, std::string> pathCommand = {};

void get_executables_from_dir(
  std::string& dir
)
{
  for (const auto& entry : fs::directory_iterator(dir))
  {
    if (pathCommand.find(entry.path().stem()) == pathCommand.end())
    {
        pathCommand[entry.path().stem()] = entry.path();
    }
  }
}


void get_commands_from_path(std::string& path)
{
    std::istringstream iss(path);
    std::string dir;
    while (std::getline(iss, dir, ':'))
    {
        get_executables_from_dir(dir);
    }
}


Command parse_input(std::string input)
{
    Command command;
    std::istringstream iss(input);
    std::string cmd;
    iss >> cmd;
     
    std::string arg;
    while (iss >> arg)
    {
        command.args.push_back(arg);
    }

    if (builtIn.find(cmd) != builtIn.end())
    {
        command.type = builtIn.at(cmd);
    }
    else if (pathCommand.find(cmd) != pathCommand.end())
    {
        command.type = COMMAND_PATH;
    }
    else
    {
        command.type = COMMAND_UNKNOWN;
    }

    return command;
}
