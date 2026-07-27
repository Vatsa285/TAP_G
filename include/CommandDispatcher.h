#pragma once

#include <string>

#include "Gesture.h"
#include "ConfigManager.h"
#include "CommandExecutor.h"

class CommandDispatcher
{
public:
    explicit CommandDispatcher();

    void dispatch(const Gesture& gesture);

private:
    ConfigManager config;
    CommandExecutor executor;
};