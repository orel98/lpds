#pragma once
#include "pch.h"

class Timer
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<float> duration;

public:
    Timer();

    ~Timer();
};