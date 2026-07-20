#pragma once

#include <memory>
#include "CommandDispatcher.h"
struct udev;
struct libinput;

class IGestureDetector;

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void run();

private:
    struct udev* udev_;
    struct libinput* libinput_;
    CommandDispatcher dispatcher;
    std::unique_ptr<IGestureDetector> detector;
    void initialize();
};