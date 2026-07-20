#pragma once
#include<optional>
#include<libinput.h>
#include<chrono>
#include "Gesture.h"

class IGestureDetector
{
public:
    virtual ~IGestureDetector() = default;
    virtual std::optional<Gesture> process(libinput_event* event) = 0;
};