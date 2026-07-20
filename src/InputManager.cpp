#include <fcntl.h>
#include<unistd.h>
#include <iostream>
#include <poll.h>
#include "InputManager.h"
#include "TapGestureDetector.h"
#include "CommandDispatcher.h"
static int openRestricted(const char* path, int flags, void* user_data)
{
    return open(path, flags);
}

static void closeRestricted(int fd, void* user_data)
{
    close(fd);
}

static const libinput_interface interface={
    .open_restricted=openRestricted,
    .close_restricted=closeRestricted
};



InputManager::InputManager() : udev_(nullptr), libinput_(nullptr),dispatcher("../config/config.json"){
    initialize();
}

InputManager::~InputManager() {
    if (libinput_) {
        libinput_unref(libinput_);
    }
    if (udev_) {
        udev_unref(udev_);
     }
}

void InputManager::initialize() {
    udev_ = udev_new();
    if (!udev_) {
        throw std::runtime_error("Failed to create udev context");
    }

    libinput_ = libinput_udev_create_context(&interface, nullptr, udev_);
    if (!libinput_) {
        throw std::runtime_error("Failed to create libinput context");
    }

    if (libinput_udev_assign_seat(libinput_, "seat0") != 0) {
        throw std::runtime_error("Failed to assign seat0");
    }
    detector = std::make_unique<TapGestureDetector>();
}


void InputManager::run()
{
    struct pollfd pfd_;
    pfd_.fd = libinput_get_fd(libinput_);
    pfd_.events = POLLIN;
    while (true)
    {
        poll(&pfd_, 1, -1);
        libinput_dispatch(libinput_);

        libinput_event* event;

        while ((event = libinput_get_event(libinput_)) != nullptr)
        {
            if(auto gesture = detector->process(event))
            {
                dispatcher.dispatch(*gesture);
            }
            libinput_event_destroy(event);
        }
    }
}
