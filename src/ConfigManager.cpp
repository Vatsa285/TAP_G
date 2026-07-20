#include <fstream>
#include <nlohmann/json.hpp>
#include "ConfigManager.h"

ConfigManager::ConfigManager(const std::string& path) {
    load(path);
}

std::string ConfigManager::getCommand(GestureType gesture) const {
    const auto it = gestureMap.find(gesture);
    if (it == gestureMap.end()) {
        return {};
    }

    return it->second;
}

void ConfigManager::load(const std::string& path) {
    std::ifstream file(path);
    nlohmann::json json;
    file >> json;
    for (const auto& [key, value] : json.items()) {
        GestureType gestureType;
        if (key == "ThreeFingerTap") {
            gestureType = GestureType::ThreeFingerTap;
        } else if (key == "FourFingerTap") {
            gestureType = GestureType::FourFingerTap;
        } else {
            continue;
        }
        gestureMap[gestureType] = value.get<std::string>();
    }
}