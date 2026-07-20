#include <iostream>

#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher(const std::string& configFile)
    : config(configFile)
{}

void CommandDispatcher::dispatch(const Gesture& gesture)
{
    const auto command = config.getCommand(gesture.type);

    if (!command.empty())
    {
        executor.execute(command);
    }
}

