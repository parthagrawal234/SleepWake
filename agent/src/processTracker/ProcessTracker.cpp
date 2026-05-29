#include "ProcessTracker.hpp"

#include <windows.h>
#include <psapi.h>

std::string ProcessTracker::getWindowTitle()
{
    HWND hwnd = GetForegroundWindow();

    if (!hwnd)
    {
        return "Unknown";
    }

    char title[256];

    GetWindowTextA(
        hwnd,
        title,
        sizeof(title)
    );

    return std::string(title);
}

std::string ProcessTracker::getProcessName()
{
    HWND hwnd = GetForegroundWindow();

    if (!hwnd)
    {
        return "Unknown";
    }

    DWORD processId;

    GetWindowThreadProcessId(
        hwnd,
        &processId
    );

    HANDLE processHandle =
        OpenProcess(
            PROCESS_QUERY_INFORMATION |
            PROCESS_VM_READ,
            FALSE,
            processId
        );

    if (!processHandle)
    {
        return "Unknown";
    }

    char processName[MAX_PATH];

    if (
        GetModuleBaseNameA(
            processHandle,
            NULL,
            processName,
            sizeof(processName)
        )
    )
    {
        CloseHandle(processHandle);

        return std::string(processName);
    }

    CloseHandle(processHandle);

    return "Unknown";
}

ActivitySnapshot ProcessTracker::capture()
{
    ActivitySnapshot snapshot;

    snapshot.processName =
        getProcessName();

    snapshot.windowTitle =
        getWindowTitle();

    snapshot.timestamp =
        std::chrono::system_clock::now();

    return snapshot;
}
