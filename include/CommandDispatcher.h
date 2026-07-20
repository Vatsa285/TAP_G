#pragma once

#include <string>

#include "Gesture.h"
#include "ConfigManager.h"
#include "CommandExecutor.h"

class CommandDispatcher
{
public:
    explicit CommandDispatcher(const std::string& configFile);

    void dispatch(const Gesture& gesture);

private:
    ConfigManager config;
    CommandExecutor executor;
};