#include <iostream>
#include <sstream>
#include <vector>

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

    if (command =="echo")
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
    else
    {
      std::cout << input << ": command not found" << std::endl;
    }
  }
}
