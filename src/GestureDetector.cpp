#include<libinput.h>
#include<chrono>

#include "TapGestureDetector.h"
#include "Gesture.h"

TapGestureDetector::TapGestureDetector() : currentFingers_{0}, holdActive_{false} {}

std::optional<Gesture> TapGestureDetector::process(libinput_event* event)
{
    switch(libinput_event_get_type(event)){
        case LIBINPUT_EVENT_GESTURE_HOLD_BEGIN:
            {auto gesture=libinput_event_get_gesture_event(event);   
            currentFingers_=libinput_event_gesture_get_finger_count(gesture);
            holdStart_=std::chrono::steady_clock::now();
            holdActive_=true;
            break;
            }
        case LIBINPUT_EVENT_GESTURE_HOLD_END:
            if(holdActive_){
                auto time=std::chrono::steady_clock::now()-holdStart_;
                holdActive_=false;
                if(time<THRESHOLD){
                    switch(currentFingers_){
                        case 3:
                            return Gesture{GestureType::ThreeFingerTap};
                        case 4:
                            return Gesture{GestureType::FourFingerTap};
                        default:
                            break;
                    }
                }
            }
            break;
        default:
            break;
    }
    return std::nullopt;
}