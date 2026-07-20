#pragma once

#include "IGestureDetector.h"
#include <chrono>

class TapGestureDetector : public IGestureDetector
{
private:
    unsigned int currentFingers_{0};
    bool holdActive_{false};
    std::chrono::steady_clock::time_point holdStart_;
    static constexpr auto THRESHOLD = std::chrono::milliseconds(250);

public:
    TapGestureDetector();
    std::optional<Gesture> process(libinput_event* event) override;
};