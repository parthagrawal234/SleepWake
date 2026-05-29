#include "../processTracker/ProcessTracker.hpp"
#include <iostream>
#include <chrono>
#include <thread>

int main(){
    ProcessTracker tracker;
    std::string lastProcess = "";

    while(true) {
        std::string process =
            tracker.getProcessName();

        std::string title =
            tracker.getWindowTitle();

        if(process != lastProcess)
        {
            std::cout
                << process
                << " | "
                << title
                << std::endl;

            lastProcess = process;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(500)
        );
    }
    return 0;
}
