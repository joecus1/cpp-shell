#pragma once

#include <unordered_map>
#include <string>
#include <vector>


enum CommandType {
    COMMAND_EXIT,
    COMMAND_CD,
    COMMAND_PWD,
    COMMAND_ECHO,
    COMMAND_TYPE,
    COMMAND_PATH,
    COMMAND_UNKNOWN
};

const std::unordered_map<std::string, CommandType> builtIn = {
    {"exit", COMMAND_EXIT},
    {"cd", COMMAND_CD},
    {"pwd", COMMAND_PWD},
    {"echo", COMMAND_ECHO},
    {"type", COMMAND_TYPE}
};

struct Command {
    int type;
    std::vector<std::string> args;
};

extern std::unordered_map<std::string, std::string> pathCommand;
void get_executables_from_dir(std::string& dir);
void get_commands_from_path(std::string& path);
Command parse_input(std::string input);

