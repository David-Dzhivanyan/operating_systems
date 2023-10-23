#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;

    // Создаем процесс
    if (CreateProcessA("C:\\Windows\\system32\\win32calc.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {

        cout << "ID of the created process: " << pi.dwProcessId << endl;

        bool flag = true;
        while (flag) {
            cout << "Action menu:\n";
            cout << "s - Suspend flow\n";
            cout << "r - Resume thread execution\n";
            cout << "t - Finalize the process\n";
            cout << "Select an action: ";

            char choice;
            cin >> choice;

            switch (choice) {
                case 's':
                    // Приостанавливаем поток
                    SuspendThread(pi.hThread);
                    cout << "Flow has been suspended" << endl;
                    break;
                case 'r':
                    // Возобновляем выполнение потока
                    ResumeThread(pi.hThread);
                    cout << "The flow has been restored" << endl;
                    break;
                case 't':
                    // Завершаем процесс
                    TerminateProcess(pi.hProcess, 0);
                    cout << "The process is complete" << endl;
                    flag = false;
                    break;
                default:
                    cout << "Incorrect input" << endl;
                    break;
            }
        }

        // Закрываем дескрипторы
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        cerr << "Error during process creation: " << GetLastError() << endl;
    }

    return 0;
}
