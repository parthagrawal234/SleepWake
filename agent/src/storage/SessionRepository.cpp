#include "SessionRepository.hpp"

#include <sqlite3.h>
#include <iostream>

SessionRepository::SessionRepository(
    Database& database
)
    : db(database)
{
}

void SessionRepository::initialize()
{
    const char* sql =
        R"(
        CREATE TABLE IF NOT EXISTS sessions
        (
            id INTEGER PRIMARY KEY,

            process_name TEXT,

            window_title TEXT,

            start_time INTEGER,

            end_time INTEGER,

            duration_seconds INTEGER
        );
        )";

    char* err = nullptr;

    sqlite3_exec(
        db.getConnection(),
        sql,
        nullptr,
        nullptr,
        &err
    );

    if(err)
    {
        std::cerr
            << "SQLite Error: "
            << err
            << std::endl;

        sqlite3_free(err);
    }
}

void SessionRepository::saveSession(
    const ActivitySession& session
)
{
    std::cout
        << "Saving session: "
        << session.processName
        << std::endl;
}
