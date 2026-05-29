#pragma once

#include "../models/ActivitySnapshot.hpp"
#include "../models/ActivitySession.hpp"

class SessionManager
{
public:
    void update(
        const ActivitySnapshot& snapshot
    );

private:
    ActivitySession currentSession;

    bool hasSession = false;
};
