#include "../processTracker/ProcessTracker.hpp"
#include "../sessionManager/SessionManager.hpp"

#include <chrono>
#include <thread>

int main()
{
    ProcessTracker tracker;

    SessionManager sessionManager;

    while (true)
    {
        ActivitySnapshot snapshot =
            tracker.capture();

        std::cout
            << snapshot.processName
            << " | "
            << snapshot.windowTitle
            << std::endl;

        sessionManager.update(
            snapshot
        );

        std::this_thread::sleep_for(
            std::chrono::milliseconds(
                500
            )
        );
    }

    return 0;
}
