#include "SessionManager.hpp"

#include "../storage/SessionRepository.hpp"

#include <iostream>

SessionManager::SessionManager(
    SessionRepository& repository
)
    : repository(repository)
{
}

void SessionManager::update(
    const ActivitySnapshot& snapshot
)
{
    if(snapshot.processName == "explorer.exe")
    {
        return;
    }

    if(!hasSession)
    {
        currentSession.processName =
            snapshot.processName;

        currentSession.windowTitle =
            snapshot.windowTitle;

        currentSession.startTime =
            snapshot.timestamp;

        hasSession = true;

        return;
    }

    if(
        snapshot.processName !=
        currentSession.processName
    )
    {
        currentSession.endTime =
            snapshot.timestamp;

        auto duration =
            std::chrono::duration_cast<
                std::chrono::seconds
            >(
                currentSession.endTime -
                currentSession.startTime
            );

        std::cout
            << "\nSession Ended\n"
            << "Process: "
            << currentSession.processName
            << "\nDuration: "
            << duration.count()
            << " seconds\n"
            << std::endl;

        repository.saveSession(
            currentSession
        );

        currentSession.processName =
            snapshot.processName;

        currentSession.windowTitle =
            snapshot.windowTitle;

        currentSession.startTime =
            snapshot.timestamp;
    }
}
