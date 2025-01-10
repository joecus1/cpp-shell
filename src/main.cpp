#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

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

    // Split input by spaces
    std::istringstream iss(input);
    std::string command;
    iss >> command;

    std::string arg;
    std::vector<std::string> args;
    while (iss >> arg) 
    {
      args.push_back(arg);
    }

    
    if (command == "echo")
    {
      for (const auto& arg : args) 
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
      std::vector<std::string> valid_commands = {"exit", "echo", "type"};
      if (args.size() > 0 && std::find(valid_commands.begin(), valid_commands.end(), args[0]) != valid_commands.end()) 
      {
        std::cout << args[0] << " is a shell builtin" << std::endl;
      } 
      else 
      {
        command_not_found(args[0]);
      }
    }
    else
    {
      command_not_found(command);
    }
  }
}
