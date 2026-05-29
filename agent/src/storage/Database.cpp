#include "Database.hpp"

#include <iostream>

Database::Database(
    const std::string& path
)
{
    if(
        sqlite3_open(
            path.c_str(),
            &db
        )
    )
    {
        std::cerr
            << "Failed to open DB\n";
    }
}

Database::~Database()
{
    sqlite3_close(db);
}

sqlite3* Database::getConnection()
{
    return db;
}
