cmake_minimum_required(VERSION 3.16)

project(agent)

set(CMAKE_CXX_STANDARD 17)

add_executable(
    agent

    src/core/main.cpp

    src/processTracker/ProcessTracker.cpp

    src/sessionManager/SessionManager.cpp

    src/storage/Database.cpp

    src/storage/SessionRepository.cpp

    external/sqlite/sqlite3.c
)

target_include_directories(
    agent
    PRIVATE
    external/sqlite
)

target_link_libraries(
    agent
    psapi
)
