cmake_minimum_required(VERSION 3.16)

project(SleepWake)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(
    SleepWake
    src/core/main.cpp
    src/processTracker/ProcessTracker.cpp
)

target_link_libraries(
    SleepWake
    psapi
)
