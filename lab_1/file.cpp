#include <winbase.h>
#include <windows.h>

#include <iostream>
#include <string>

using namespace std;
int main() {
    CHAR file_name[100] = "";
    CHAR str[100] = "";
    LONG num;
    DWORD byteCount;
    cin >> file_name >> num;

    HANDLE file = CreateFile(file_name, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL, NULL);

    DWORD answ = SetFilePointer(file, num, NULL, FILE_BEGIN);

    if (INVALID_HANDLE_VALUE == file || answ == INVALID_SET_FILE_POINTER) {
        cout << "n/a" << endl;
    } else {
        BOOL i = ReadFile(file, str, sizeof(str), &byteCount, NULL);
        str[byteCount] = '\0';
        DeleteFileA(file_name);
        HANDLE file1 = CreateFile(file_name, GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL,
                                  CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        WriteFile(file1, str, sizeof(str), NULL, NULL);
        if (i) {
            cout << str << endl;
        }
    }
    CloseHandle(file);
    return 0;
}
