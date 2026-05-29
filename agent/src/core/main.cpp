#include "../processTracker/ProcessTracker.hpp"
#include "../sessionManager/SessionManager.hpp"
#include "../storage/Database.hpp"
#include "../storage/SessionRepository.hpp"

#include <chrono>
#include <thread>

int main()
{
    Database database(
        "focus.db"
    );

    SessionRepository repository(
        database
    );

    repository.initialize();

    SessionManager sessionManager(
        repository
    );

    ProcessTracker tracker;

    while(true)
    {
        ActivitySnapshot snapshot =
            tracker.capture();

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
