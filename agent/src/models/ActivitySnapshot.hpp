#pragma once

#include <string>
#include <chrono>

struct ActivitySnapshot
{
    std::string processName;
    std::string windowTitle;

    std::chrono::system_clock::time_point timestamp;
};
