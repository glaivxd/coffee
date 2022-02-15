#include <Windows.h>
#include <TlHelp32.h>

#include "process.hpp"

Process::Process()
{
    pid = 0;
    handle = NULL;
}

Process::~Process()
{
    if (handle)
        CloseHandle(handle);
}

int Process::attach(const std::wstring& processName)
{
    HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 proc_entry;
    proc_entry.dwSize = sizeof(PROCESSENTRY32);

    if (snap_shot == INVALID_HANDLE_VALUE)
        return 0;

    // Loop through running processes
    if (Process32First(snap_shot, &proc_entry))
    {
        while (Process32Next(snap_shot, &proc_entry))
        {
            if (proc_entry.szExeFile == processName)
            {
                pid = proc_entry.th32ProcessID;
                handle = OpenProcess(PROCESS_ALL_ACCESS, 0, pid);

                CloseHandle(snap_shot);
                return pid;
            }
        }
    }

    CloseHandle(snap_shot);
    return 0;
}

uint32_t Process::get_module(const std::wstring& module_name)
{
    HANDLE snap_shot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    MODULEENTRY32 module_entry;
    module_entry.dwSize = sizeof(MODULEENTRY32);

    if (snap_shot == INVALID_HANDLE_VALUE)
        return 0;

    if (Module32First(snap_shot, &module_entry))
    {
        // Loop through all loaded modules
        while (Module32Next(snap_shot, &module_entry))
        {
            if (module_entry.szModule == module_name)
            {
                CloseHandle(snap_shot);
                return reinterpret_cast<uintptr_t>(module_entry.modBaseAddr);
            }
        }
    }

    CloseHandle(snap_shot);
    return 0;
}