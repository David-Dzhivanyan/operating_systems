#include <windows.h>

#include <iostream>
using namespace std;

int main() {
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    DWORD page_size = sys_info.dwPageSize;  //получаю информацию о размере виртуальной страницы в моей системе

    INT num_pages;
    cout << "Enter the number of pages:";
    cin >> num_pages;  //ввожу количество страниц

    DWORD total_size = num_pages * page_size;  //считаю общее число бит

    LPVOID reserved_memory =
            VirtualAlloc(nullptr, total_size, MEM_RESERVE, PAGE_READWRITE);  //резервирую виртуальную память

    INT start_page;
    INT count_page;
    cout << "Enter the number of pages and from which to start that will be committed:";
    cin >> count_page >> start_page;  //ввожу уоличество страниц и с какой начать

    DWORD offset = start_page * page_size;
    DWORD offset_counted = page_size * count_page;
    LPVOID commit_ptr =
            &reserved_memory + offset;  //считаю отступ, размер в битах и указатель с какого начать комитить

    LPVOID committed_memory =
            VirtualAlloc(commit_ptr, offset_counted, MEM_COMMIT, PAGE_READWRITE);  //резервирую физ. память

    LPVOID add_ptr = &reserved_memory +
                     total_size;  //устанавливаю указатель на область сразу за выделенной виртуальной памятью
    LPVOID add_memory = VirtualAlloc(add_ptr, page_size, MEM_COMMIT,
                                     PAGE_READONLY);  //резервирую физ. память для новой страницы

    INT arr[] = {1, 2, 3, 4, 5};
    size_t size_arr = sizeof(arr);  //считаю размер массива в битах
    errno_t error =
            memcpy_s(committed_memory, size_arr, arr, size_arr);  // копирую массив в выделенную память

    if (reserved_memory != nullptr && committed_memory != nullptr && error == 0 && add_memory != nullptr) {
        MEMORY_BASIC_INFORMATION memory_info;
        VirtualQuery(committed_memory, &memory_info,
                     sizeof(memory_info));  //получаем информацию о выделенной памяти

        cout << "State commit: " << memory_info.State << endl;
        cout << "Protect commit: " << memory_info.Protect << endl;

        LPVOID nextMemory = &committed_memory + offset_counted;

        VirtualQuery(nextMemory, &memory_info, sizeof(memory_info));

        cout << "State after commit: " << memory_info.State << endl;
        cout << "Protect after commit: " << memory_info.Protect << endl;

        VirtualQuery(add_ptr, &memory_info, sizeof(memory_info));

        cout << "State after virtual: " << memory_info.State << endl;
        cout << "Protect after virtual: " << memory_info.Protect << endl;

        INT* copied_array =
                static_cast<int*>(committed_memory);  //преобразую указатель на void в указатель на массив
        INT count = sizeof(arr) / sizeof(int);
        cout << "Reserved address: " << reserved_memory << "\nCommitted address: " << committed_memory
             << "\nAdded address: " << add_memory << endl;
        for (int i = 0; i < count; i++) {
            cout << copied_array[i] << " ";
        }
        cout << endl;

        INT decommit_start_page;
        INT decommit_count_page;
        cout << "Enter the number of pages and from which to start that will be decommitted:";
        cin >> decommit_count_page >> decommit_start_page;  //ввожу количество страниц и с какой начать

        DWORD decommit_offset = decommit_start_page * page_size;
        DWORD decommit_offset_counted = page_size * decommit_count_page;
        LPVOID decommit_commit_ptr =
                &reserved_memory +
                decommit_offset;  //считаю отступ, размер в битах и указатель с какого начать комитить

        BOOL vf = VirtualFree(decommit_commit_ptr, decommit_offset_counted, MEM_DECOMMIT);


        if(vf){
            VirtualQuery(decommit_commit_ptr, &memory_info, sizeof(memory_info));
            cout << "State decommit: " << memory_info.State << endl;
            cout << "Protect decommit: " << memory_info.Protect << endl;
        } else {
            cout << "n/a" << endl;
        }


        VirtualFree(committed_memory, 0, MEM_RELEASE);  //отчищаю память
        VirtualFree(reserved_memory, 0, MEM_RELEASE);
    } else {
        cout << "n/a" << endl;
    }

    return 0;
}
