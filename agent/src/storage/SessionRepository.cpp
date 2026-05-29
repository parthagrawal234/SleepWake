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

            process_name TEXT NOT NULL,

            window_title TEXT,

            start_time INTEGER NOT NULL,

            end_time INTEGER NOT NULL,

            duration_seconds INTEGER NOT NULL
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
    auto start =
        std::chrono::system_clock::to_time_t(
            session.startTime
        );

    auto end =
        std::chrono::system_clock::to_time_t(
            session.endTime
        );

    auto duration =
        std::chrono::duration_cast<
            std::chrono::seconds
        >(
            session.endTime -
            session.startTime
        ).count();

    const char* sql =
        R"(
        INSERT INTO sessions
        (
            process_name,
            window_title,
            start_time,
            end_time,
            duration_seconds
        )
        VALUES
        (
            ?,
            ?,
            ?,
            ?,
            ?
        );
        )";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(
        db.getConnection(),
        sql,
        -1,
        &stmt,
        nullptr
    );

    sqlite3_bind_text(
        stmt,
        1,
        session.processName.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_text(
        stmt,
        2,
        session.windowTitle.c_str(),
        -1,
        SQLITE_TRANSIENT
    );

    sqlite3_bind_int64(
        stmt,
        3,
        start
    );

    sqlite3_bind_int64(
        stmt,
        4,
        end
    );

    sqlite3_bind_int64(
        stmt,
        5,
        duration
    );

    if(
        sqlite3_step(stmt)
        != SQLITE_DONE
    )
    {
        std::cerr
            << "Insert failed: "
            << sqlite3_errmsg(
                db.getConnection()
            )
            << std::endl;
    }
    else
    {
        std::cout
            << "Session stored: "
            << session.processName
            << std::endl;
    }

    sqlite3_finalize(stmt);
}
