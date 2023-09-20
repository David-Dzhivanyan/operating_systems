#include <conio.h>
#include <windows.h>

#include <iostream>
using namespace std;

int main() {
    MEMORYSTATUSEX memory;
    memory.dwLength = sizeof(memory);

    while (!_kbhit() || _getch() != 'q') {
        GlobalMemoryStatusEx(&memory);

        cout << "Memory load: " << memory.dwMemoryLoad << "%" << endl;
        cout << "Total memory: " << memory.ullTotalPhys / 1024 / 1024 << " MB" << endl;
        cout << "Available memory: " << memory.ullAvailPhys / 1024 / 1024 << " MB" << endl;

        Sleep(1000);
    }

    return 0;
}
