#pragma once

#include <string>
#include <chrono>

struct ActivitySession
{
    std::string processName;
    std::string windowTitle;

    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
};
