#include <iostream>
#include <windows.h>
using namespace std;

HANDLE hMutex;

DWORD WINAPI thread_func1(LPVOID lpParam) {
    cout << "Thread 1 started;" << endl;
    string str = "Thread 1;";
    for (int i = 0; i < 10; i++) {
        WaitForSingleObject(hMutex, INFINITE); // ожидание мьютекса
        for (int j = 0; j < str.size(); j++){
            cout << str[j];
            Sleep(100);
        }
        cout << endl;
        ReleaseMutex(hMutex);
        Sleep(1000);
    }

    cout << "Thread 1 ended;" << endl;
    return 0;
}

DWORD WINAPI thread_func2(LPVOID lpParam) {
    cout << "Thread 2 started;" << endl;
    string str = "Thread 2;";
    for (int i = 0; i < 13; i++) {
        WaitForSingleObject(hMutex, INFINITE); // ожидание мьютекса

        for (int j = 0; j < str.size(); j++){
            cout << str[j];
            Sleep(100);
        }
        cout << endl;
        ReleaseMutex(hMutex);
        Sleep(1000);
    }
    cout << "Thread 2 ended;" << endl;
    return 0;
}

int main() {
    HANDLE thread1, thread2;
    DWORD thread_id1, thread_id2;

    hMutex = CreateMutex(NULL, FALSE, NULL);
    if (hMutex == NULL) {
        cout << "Failed to create mutex" << endl;
        return 1;
    }

    // Создание первого потока
    thread1 = CreateThread(NULL, 0, thread_func1, NULL, 0, &thread_id1);
    if (thread1 == NULL) {
        cout << "Failed to create thread 1" << endl;
        return 1;
    }

    // Создание второго потока
    thread2 = CreateThread(NULL, 0, thread_func2, NULL, 0, &thread_id2);
    if (thread2 == NULL) {
        cout << "Failed to create thread 2" << endl;
        return 1;
    }

    // Ожидание окончания работы потоков
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Закрытие дескрипторов потоков
    CloseHandle(thread1);
    CloseHandle(thread2);

    CloseHandle(hMutex);
    return 0;
}
