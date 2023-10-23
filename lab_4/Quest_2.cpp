#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    // Создаем процесс с флагом CREATE_SUSPENDED для приостановки первичного потока
    if (CreateProcess("C:\\Windows\\system32\\notepad.exe", NULL, NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi)) {
        cout << "ID of the created process: " << pi.dwProcessId << endl;

        // Приостанавливаем первичный поток на 10 секунд
        Sleep(10000);

        ResumeThread(pi.hThread);

        // Получаем приоритет потока
        int priority = GetThreadPriority(pi.hThread);

        cout << "Flow priority: " << priority << endl;
        cout << "Priority value:\n";
        cout << "-2: THREAD_PRIORITY_LOWEST\n";
        cout << "-1: THREAD_PRIORITY_BELOW_NORMAL\n";
        cout << " 0: THREAD_PRIORITY_NORMAL\n";
        cout << " 1: THREAD_PRIORITY_ABOVE_NORMAL\n";
        cout << " 2: THREAD_PRIORITY_HIGHEST\n";

        // Закрываем дескрипторы
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

    } else {
        cerr << "Error during process creation: " << GetLastError() << endl;
    }

    return 0;
}