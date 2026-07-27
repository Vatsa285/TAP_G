#include <fstream>
#include <nlohmann/json.hpp>
#include "ConfigManager.h"

ConfigManager::ConfigManager():configFile_("config/config.json"){
    load();
}

std::vector<std::string> ConfigManager::getCommand(GestureType gesture) const {
    const auto it = gestureMap.find(gesture);
    if (it == gestureMap.end()) {
        return {};
    }

    return it->second;
}
void ConfigManager::ensureConfigFileExists()
{
    std::filesystem::create_directories(configFile_.parent_path());

    if (!std::filesystem::exists(configFile_))
    {
        nlohmann::json defaultConfig = {
            {"FourFingerTap", {"xdotool", "key", "Alt+Tab"}},
            {"ThreeFingerTap", {"playerctl", "play-pause"}}
        };

        std::ofstream file(configFile_);

        if (!file)
        {
            throw std::runtime_error("Failed to create config file");
        }

        file << defaultConfig.dump(4);
    }
}
void ConfigManager::load() {
    ensureConfigFileExists();
    std::ifstream file(configFile_);
    nlohmann::json json;
    file >> json;
    for (const auto& [key, value] : json.items()) {
       gestureMap[stringToGesture(key)] = value.get<std::vector<std::string>>();
    }
}

GestureType stringToGesture(const std::string& name) 
{
    if(name=="ThreeFingerTap")
    return GestureType::ThreeFingerTap;

if(name=="FourFingerTap")
    return GestureType::FourFingerTap;

throw std::runtime_error("Unknown gesture");
}