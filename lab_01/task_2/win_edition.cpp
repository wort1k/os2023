#include <Windows.h>
#include <processthreadsapi.h>
#include <stdio.h>

volatile bool isRunning = true;

BOOL WINAPI CtrlHandler(_In_ DWORD dwCtrlType) {
    if (dwCtrlType == CTRL_C_EVENT) {
        printf("Ctrl-C event\n");
        isRunning = false;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

DWORD WINAPI printRandomNumber(LPVOID lpParam) {
    while (isRunning) {
        printf("%f\n", (double)rand() / RAND_MAX);
        Sleep(1500);
    }
    return 0;
}

DWORD WINAPI reverseString(LPVOID lpParam) {
    while (isRunning) {
        char str[250];
        scanf_s("%s", str, 250);
        printf("%s\n", _strrev(str));
    }
    return 0;
}

int main() {
    SetConsoleCtrlHandler(CtrlHandler, TRUE);

    HANDLE thread1 = CreateThread(NULL, 0, printRandomNumber, NULL, 0, NULL);
    if (thread1 == NULL) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    HANDLE thread2 = CreateThread(NULL, 0, reverseString, NULL, 0, NULL);
    if (thread2 == NULL) {
        fprintf(stderr, "Error creating thread 2\n");
        CloseHandle(thread1);
        return 1;
    }


    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    CloseHandle(thread1);
    CloseHandle(thread2);

    return 0;
}
