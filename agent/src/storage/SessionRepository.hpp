#pragma once

#include "../models/ActivitySession.hpp"
#include "Database.hpp"

class SessionRepository
{
public:
    SessionRepository(
        Database& database
    );

    void initialize();

    void saveSession(
        const ActivitySession& session
    );

private:
    Database& db;
};
