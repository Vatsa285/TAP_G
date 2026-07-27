#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include <filesystem>
#include "Gesture.h"

GestureType stringToGesture(const std::string& name);

class ConfigManager
{
public:
    explicit ConfigManager();

    std::vector<std::string> getCommand(GestureType gesture) const;

private:
    std::unordered_map<GestureType,std::vector<std::string>> gestureMap;
    std::filesystem::path configFile_;
    void ensureConfigFileExists();
    void load();
};