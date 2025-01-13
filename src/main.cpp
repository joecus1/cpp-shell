#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <unordered_map>

namespace fs = std::filesystem;

void command_not_found(const std::string& command) 
{
  std::cout << command << ": not found" << std::endl;
}

void get_executables_from_dir(
  const std::string& dir, 
  std::unordered_map<std::string, std::string>& commands
)
{
  for (const auto& entry : fs::directory_iterator(dir))
  {
    // std::cout << entry.path() << std::endl;
    if (commands.find(entry.path().stem()) == commands.end())
    {
      commands[entry.path().stem()] = entry.path();
    }
  }
}

std::unordered_map<std::string, std::string> get_commands_from_path(const std::string& path)
{
  std::istringstream iss(path);
  std::string dir;
  std::unordered_map<std::string, std::string> commands;
  while (std::getline(iss, dir, ':'))
  {
    get_executables_from_dir(dir, commands);
  }
  return commands;
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

    // Split input by spaces
    std::istringstream iss(input);
    std::string command;
    iss >> command;

    std::string path(std::getenv("PATH"));
    std::unordered_map<std::string, std::string> path_commands = get_commands_from_path(path);

    std::string arg;
    std::vector<std::string> args;
    while (iss >> arg) 
    {
      args.push_back(arg);
    }

    if (command == "echo")
    {
      for (std::string arg : args) 
      {
        std::cout << arg << " ";
      }
      std::cout << std::endl;
      continue;
    }
    else if (command == "exit") 
    {
      if (args.size() > 0 && args[0] == "0") 
      {
        return 0;
      }
    }
    else if (command == "type")
    {
      std::vector<std::string> builtins = {"exit", "echo", "type"};
      if (args.size() > 0 && std::find(builtins.begin(), builtins.end(), args[0]) != builtins.end()) 
      {
        std::cout << args[0] << " is a shell builtin" << std::endl;
      } 
      else if(path_commands.find(args[0]) != path_commands.end())
      {
        std::cout << args[0] << " is " << path_commands[args[0]] << std::endl;
      }
      else 
      {
        command_not_found(args[0]);
      }
    }
    else if (path_commands.find(command) != path_commands.end())
    {
      std::string full_command = path_commands[command];
      for (std::string arg : args)
      {
        full_command += " " + arg;
      }

      const char *command_ptr = full_command.c_str();
      
      int result = std::system(command_ptr);
    }
    else
    {
      command_not_found(command);
    }
  }
}
