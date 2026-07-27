#pragma once

#include <vector>
#include <string>

class CommandExecutor
{
    public:
        CommandExecutor();
        bool execute(const std::vector<std::string>& command);
};