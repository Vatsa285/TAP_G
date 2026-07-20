#pragma once

#include <unordered_map>
#include <string>

#include "Gesture.h"

class ConfigManager
{
public:
    explicit ConfigManager(const std::string& path);

    std::string getCommand(GestureType gesture) const;

private:
    std::unordered_map<GestureType,std::string> gestureMap;

    void load(const std::string& path);
};