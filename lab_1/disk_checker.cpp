#include <windows.h>

#include <iostream>
#include <string>

using namespace std;

int main() {
    CHAR letter;
    CHAR VolumeNameBuffer[100];
    CHAR FileSystemNameBuffer[100];
    unsigned long VolumeSerialNumber;
    DWORD FreeBytesAvailable;
    DWORD TotalNumberOfBytes;
    DWORD TotalNumberOfFreeBytes;
    DWORD mask = GetLogicalDrives();

    cin >> letter;

    letter = toupper(letter);
    CHAR str[4] = "";
    str[0] = letter;
    str[1] = ':';
    str[2] = '\\';

    if ((mask >> (letter - 'A')) && 1) {
        if (GetDriveTypeA(str) == DRIVE_UNKNOWN) cout << "UNKNOWN" << endl;
        if (GetDriveTypeA(str) == DRIVE_NO_ROOT_DIR) cout << "DRIVE NO ROOT DIR" << endl;
        if (GetDriveTypeA(str) == DRIVE_REMOVABLE) cout << "REMOVABLE" << endl;
        if (GetDriveTypeA(str) == DRIVE_FIXED) cout << "FIXED" << endl;
        if (GetDriveTypeA(str) == DRIVE_REMOTE) cout << "REMOTE" << endl;
        if (GetDriveTypeA(str) == DRIVE_CDROM) cout << "CDROM" << endl;
        if (GetDriveTypeA(str) == DRIVE_RAMDISK) cout << "RAMDISK" << endl;

        GetVolumeInformationA(str, VolumeNameBuffer, 100, &VolumeSerialNumber, NULL, NULL,
                              FileSystemNameBuffer, 100);

        cout << "Volume name is " << VolumeNameBuffer << endl;
        cout << "Volume serial number is " << VolumeSerialNumber << endl;
        cout << "File system is " << FileSystemNameBuffer << endl;

        GetDiskFreeSpaceEx(str, (PULARGE_INTEGER)&FreeBytesAvailable, (PULARGE_INTEGER)&TotalNumberOfBytes,
                           (PULARGE_INTEGER)&TotalNumberOfFreeBytes);

        cout << "Number of free bytes = " << (unsigned long)TotalNumberOfFreeBytes << "( "
             << double((unsigned long)(TotalNumberOfFreeBytes)) / 1024 / 1000 << " Mb )" << endl;
        cout << "Number of bytes = " << (unsigned long)TotalNumberOfBytes << "( "
             << double((unsigned long)(TotalNumberOfBytes)) / 1024 / 1000 << " Mb )" << endl;
    } else
        cout << "n/a";
    return 0;
}
