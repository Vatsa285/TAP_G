#pragma once 

enum class GestureType
{
    ThreeFingerTap,
    FourFingerTap
};

struct Gesture
{
    GestureType type;
};