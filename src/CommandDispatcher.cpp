#include <iostream>

#include "CommandDispatcher.h"

CommandDispatcher::CommandDispatcher()
    : config()
{}

void CommandDispatcher::dispatch(const Gesture& gesture)
{
    const auto command = config.getCommand(gesture.type);

    if (!command.empty())
    {
        if(!executor.execute(command))
        {
            std::cerr << "Failed to execute command for gesture" << std::endl;
        }
    }
}

 