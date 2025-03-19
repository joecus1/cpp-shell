#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <unordered_map>
#include "Commands.hpp"

namespace fs = std::filesystem;

void command_not_found(const std::string& command) 
{
  std::cout << command << ": not found" << std::endl;
}

int main() 
{
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  
  while (true) 
  {
    std::cout << "$ ";

    std::string input;
    std::getline(std::cin, input);

    Command command = parse_input(input);

    std::string home(std::getenv("HOME"));
    std::string path(std::getenv("PATH"));

    get_commands_from_path(path);

    switch (command.type)
    {
    case COMMAND_ECHO:
      for (std::string arg : command.args) 
      {
        std::cout << arg << " ";
      }
      std::cout << std::endl;
      break;
    case COMMAND_EXIT:
      if (command.args.size() == 1 && command.args[0] == "0") 
      {
        return 0;
      }
      break;
    case COMMAND_TYPE:
      if (builtIn.find(command.args[0]) != builtIn.end()) 
      {
        std::cout << command.args[0] << " is a shell builtin" << std::endl;
      } 
      else if(pathCommand.find(command.args[0]) != pathCommand.end())
      {
        std::cout << command.args[0] << " is " << pathCommand.at(command.args[0]) << std::endl;
      }
      else 
      {
        command_not_found(command.args[0]);
      }
      break;
    case COMMAND_PWD:
      std::cout << fs::current_path().string() << std::endl;
      break;
    case COMMAND_CD:
      if (command.args[0] == "~")
      {
        fs::current_path(home);
      }
      else if (fs::exists(command.args[0]))
      {
        fs::current_path(command.args[0]);
      }
      else
      {
        std::cout << "cd: " << command.args[0] << ": No such file or directory" << std::endl;
      }
      break;
    case COMMAND_PATH:
      std::system(input.c_str());
      break;
    default:
      std::cout << "Issue parsing command" << std::endl;
      break;
    }
  }
}
