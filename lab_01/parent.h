#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void LaunchChildProcess(const TCHAR* commandLine)
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    DWORD exitCode;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcess(NULL,
        commandLine,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi)
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);

    GetExitCodeProcess(pi.hProcess, &exitCode);

    printf("Child process exited with code: %d\n", exitCode);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int _tmain(int argc, TCHAR* argv[])
{
    if (argc != 2)
    {
        _tprintf(_T("Usage: %s [cmdline]\n"), argv[0]);
        return 1;
    }

    LaunchChildProcess(argv[1]);

    return 0;
}
