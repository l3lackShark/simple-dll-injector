#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

DWORD GetProcId(const char *procName) {
    DWORD nProcId = 0;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 procEntry;

        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry)) {
            do {
                if (!strcmp(procEntry.szExeFile, procName)) {
                    nProcId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }

    CloseHandle(hSnap);

    return nProcId;
}

void usage() { puts("Usage: injector.exe <process_name> <dll_full_path>"); }

void Inject(const DWORD processId, const char *dllPath) {

    printf("Injecting Dll: %s\n", dllPath);

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);

    if (hProc && hProc != INVALID_HANDLE_VALUE) {
        printf("Got a handle to the process: 0x%p\n", hProc);
        void *location = VirtualAllocEx(
            hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

        if (location) {
            printf("Injection location: 0x%p\n", location);
            WriteProcessMemory(hProc, location, dllPath, strlen(dllPath) + 1,
                               0);

            HANDLE hThread = CreateRemoteThread(
                hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, location, 0,
                0);

            if (hThread) {
                printf("Thread created at: 0x%p\n", hThread);
                CloseHandle(hThread);
                puts("Injection completed!");
            }

        } else {
            puts("Could not allocate memory.");
            exit(1);
        }
    }

    if (hProc) {
        CloseHandle(hProc);
    }
}

int main(int argc, char **argv) {

    if (argc < 3) {
        usage();
        return -1;
    }

    const char *processName = argv[1];
    const char *dllPath = argv[2];

    DWORD nProcId = 0;

    while (!nProcId) {
        nProcId = GetProcId(processName);
        Sleep(30);
    }

    printf("Process %s was found with id: 0x%p\n", processName, nProcId);

    Inject(nProcId, dllPath);
    return 0;
}
