#pragma once
#include "ProcessTracker.hpp"

#include <windows.h>
#include <psapi.h>

std::string ProcessTracker::getWindowTitle() {
    HWND hwnd = GetForegroundWindow();
    if(!hwnd) return "Unknown";
    char title[256];
    GetWindowText(hwnd, title, sizeof(title));
    return std::string(title);
}

std::string ProcessTracker::getProcessName() {
    HWND hwnd = GetForegroundWindow();
    if(!hwnd) return "Unknown";
    DWORD processId;
    GetWindowThreadProcessId(hwnd, &processId);
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, false, processId);
    if(!process)
        return "Unknown";

    char processName[MAX_PATH];
    if(GetModeuleBaseNameA(
        process,
        NULL,
        processName,
        sizeof(processName)
    )) {
        CloseHandle(process);
        return std::string(processName);
    }
    CloseHandle(process);
    return "Unknown";
}
