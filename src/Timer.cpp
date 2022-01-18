#include "Timer.h"
#include "pch.h"

Timer::Timer()
    : start(std::chrono::high_resolution_clock::now()) {}

Timer::~Timer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    float ms = duration.count() * 1000.0f;

    std::cout << "Timer took: " << ms << " ms";
    std::cout << "Fps: " << 1000 / ms << "\n";
}
