#include <cstdlib>

#include "CommandExecutor.h"

CommandExecutor::CommandExecutor() {}

bool CommandExecutor::execute(const std::string& command)
{
    return std::system(command.c_str()) == 0;
}