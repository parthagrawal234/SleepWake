#pragma once

#include "../models/ActivitySnapshot.hpp"

class ProcessTracker
{
public:
    ActivitySnapshot capture();

private:
    std::string getProcessName();
    std::string getWindowTitle();
};
