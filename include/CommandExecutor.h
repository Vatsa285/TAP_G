#pragma once

#include <string>

class CommandExecutor
{
    public:
        CommandExecutor();
    bool execute(const std::string& command);
};