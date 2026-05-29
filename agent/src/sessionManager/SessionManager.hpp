#pragma once

#include "../models/ActivitySnapshot.hpp"
#include "../models/ActivitySession.hpp"

class SessionRepository;

class SessionManager
{
public:
    SessionManager(
        SessionRepository& repository
    );

    void update(
        const ActivitySnapshot& snapshot
    );

private:
    SessionRepository& repository;

    ActivitySession currentSession;

    bool hasSession = false;
};
